/***************************************************************************//**
 * @file
 * @brief Relative humidity and temperature sensor demo for SLSTK3400A_EFM32HG
 * @version 5.2.2
 *******************************************************************************
 * # License
 * <b>Copyright 2015 Silicon Labs, Inc. http://www.silabs.com</b>
 *******************************************************************************
 *
 * This file is licensed under the Silabs License Agreement. See the file
 * "Silabs_License_Agreement.txt" for details. Before using this software for
 * any purpose, you must agree to the terms of that agreement.
 *
 ******************************************************************************/

#include "em_device.h"
#include "em_chip.h"
#include "em_cmu.h"
#include "em_emu.h"
#include "em_gpio.h"
#include "i2cspm.h"
#include "si7013.h"
#include "rtcdriver.h"
#include "displaygraphics.h"
#include "em_adc.h"
#include "bspconfig.h"
#include "lsm_9DS1.h"
#include "bsp.h"

/***************************************************************************//**
 * Local defines
 ******************************************************************************/
#define C_RESET_PORT gpioPortD
#define C_RESET_PIN  4
#define OPAMP_ENABLE_PORT gpioPortE
#define OPAMP_ENABLE_PIN 13
/** Time (in ms) between periodic updates of the measurements. */
#define PERIODIC_UPDATE_MS      30000
#define MEASURE_TIME 2000

/***************************************************************************//**
 * Local variables
 ******************************************************************************/
/* RTC callback parameters. */
static void (*rtcCallback)(void*) = NULL;
static void * rtcCallbackArg = 0;

/** This flag tracks if we need to update the display
 *  (animations or measurements). */
static volatile bool updateDisplay = true;
/** This flag tracks if we need to perform a new
 *  measurement. */
static volatile bool updateMeasurement = true;
/** Flag used to indicate ADC is finished */
static volatile bool adcConversionComplete = false;

/** Timer used for periodic update of the measurements. */
RTCDRV_TimerID_t periodicUpdateTimerId;

/** counts 1ms timeTicks */
static volatile uint32_t msTicks;

/***************************************************************************//**
 * Local prototypes
 ******************************************************************************/
static void gpioSetup(void);
static void periodicUpdateCallback(RTCDRV_TimerID_t id, void *user);
static void memLcdCallback(RTCDRV_TimerID_t id, void *user);
static uint32_t checkFence(void);
static void adcInit(void);
static void FenceInit(void);

/***************************************************************************//**
 * @brief  Helper function to perform data measurements.
 ******************************************************************************/
static int performMeasurements(I2C_TypeDef *i2c, uint32_t *rhData, int32_t *tData, uint32_t *vFence)
{
  *vFence = checkFence();
  Si7013_MeasureRHAndTemp(i2c, SI7021_ADDR, rhData, tData);
  return 0;
}

/***************************************************************************//**
 * @brief  Main function
 ******************************************************************************/
int main(void)
{
  bool RTC_short = true;
  I2CSPM_Init_TypeDef i2cInit = I2CSPM_INIT_DEFAULT;
  uint32_t         rhData;
  //bool             si7013_status;
  int32_t          tempData;
  uint32_t         vFence = 0;

  /* Chip errata */
  CHIP_Init();

  /* Initalize hardware */
  gpioSetup();
  adcInit();
  usart0_Master_Setup ();
  FenceInit();
  LSM9DS1_init (); // enable the sensor
  LSM9DS1_int_init();
  GRAPHICS_Init();
  RTCDRV_Init();
  I2CSPM_Init(&i2cInit);
  NVIC_EnableIRQ(GPIO_ODD_IRQn);
  BSP_LedsInit(); // enable the warining led



  /* Get initial sensor status */
  //si7013_status = Si7013_Detect(i2cInit.port, SI7021_ADDR, NULL);

  /* Set up periodic update of the display. */
  RTCDRV_AllocateTimer(&periodicUpdateTimerId);
  RTCDRV_StartTimer(periodicUpdateTimerId, rtcdrvTimerTypePeriodic,
                    2000, periodicUpdateCallback, NULL);

  GRAPHICS_Startup();
  EMU_EnterEM2(false);

  updateDisplay = true;

  while (true) {

    if (updateMeasurement) {

      performMeasurements(i2cInit.port, &rhData, &tempData, &vFence);
      updateMeasurement = false;
    }

    if (updateDisplay) {
      updateDisplay = false;
      GRAPHICS_Draw(tempData, rhData, vFence);
    }
    if (RTC_short){ // set to 5min update
    	RTC_short = false;
    	RTCDRV_StartTimer(periodicUpdateTimerId, rtcdrvTimerTypePeriodic,
    			PERIODIC_UPDATE_MS, periodicUpdateCallback, NULL);

    }
    EMU_EnterEM2(false);

  }
}


static void FenceInit(void)
{
	 SysTick_Config(CMU_ClockFreqGet(cmuClock_CORE) / 1000);
	 GPIO_PinModeSet(C_RESET_PORT, C_RESET_PIN, gpioModeWiredOr, 1);
	 GPIO_PinModeSet(OPAMP_ENABLE_PORT, OPAMP_ENABLE_PIN, gpioModeWiredOr, 1);
}
/***************************************************************************//**
 * @brief This function is called whenever we want to measure the supply v.
 *        It is reponsible for starting the ADC and reading the result.
 ******************************************************************************/
static uint32_t checkFence(void)
{
  uint32_t vData = 0;
  uint32_t curTicks;
  curTicks = msTicks;

  GPIO_PinOutSet(OPAMP_ENABLE_PORT,OPAMP_ENABLE_PIN);

  GPIO_PinOutSet(C_RESET_PORT,C_RESET_PIN);
  while ((msTicks - curTicks) <  10); // wait for 10ms
  GPIO_PinOutClear(C_RESET_PORT,C_RESET_PIN);


  curTicks = msTicks;
  while ((msTicks - curTicks) <  MEASURE_TIME)
  {
	  /* Sample ADC */
	    adcConversionComplete = false;
	    ADC_Start(ADC0, adcStartSingle);
	    while (!adcConversionComplete) EMU_EnterEM1();
	    if (ADC_DataSingleGet(ADC0) > vData) vData = ADC_DataSingleGet(ADC0);
  }
  //disable opamp
  GPIO_PinOutClear(OPAMP_ENABLE_PORT,OPAMP_ENABLE_PIN);
  return vData;
}
/***************************************************************************//**
 * @brief SysTick_Handler
 * Interrupt Service Routine for system tick counter
 ******************************************************************************/
void SysTick_Handler(void)
{
  msTicks++;       /* increment counter necessary in Delay()*/
}

/***************************************************************************//**
 * @brief ADC Interrupt handler (ADC0)
 ******************************************************************************/
void ADC0_IRQHandler(void)
{
  uint32_t flags;

  /* Clear interrupt flags */
  flags = ADC_IntGet(ADC0);
  ADC_IntClear(ADC0, flags);

  adcConversionComplete = true;
}
/***************************************************************************//**
 * @brief lsm_9DS1 Interrupt handler
 ******************************************************************************/
void GPIO_ODD_IRQHandler(void)
	{
	  uint32_t interruptMask = GPIO_IntGet();
	  GPIO_IntClear(interruptMask);

	  if (interruptMask & (1 << BSP_GPIO_PB0_PIN)) {
	      /* PB0 */
		  BSP_LedClear(0);
	    }

	  if (interruptMask & (1 << CHIP_INT_PIN)) {
	      /* PB1 */
	    	BSP_LedSet(0);
	  }

	}

/***************************************************************************//**
 * @brief ADC Initialization
 ******************************************************************************/
static void adcInit(void)
{
  ADC_Init_TypeDef       init       = ADC_INIT_DEFAULT;
  ADC_InitSingle_TypeDef initSingle = ADC_INITSINGLE_DEFAULT;

  /* Enable ADC clock */
  CMU_ClockEnable(cmuClock_ADC0, true);

  /* Initiate ADC peripheral */
  ADC_Init(ADC0, &init);

  /* Setup single conversions for internal VDD/3 */
  initSingle.acqTime = adcAcqTime1;
  initSingle.input   = adcSingleInputCh5;
  initSingle.reference = adcRef2V5;
  ADC_InitSingle(ADC0, &initSingle);

  /* Manually set some calibration values */
  ADC0->CAL = (0x7C << _ADC_CAL_SINGLEOFFSET_SHIFT) | (0x1F << _ADC_CAL_SINGLEGAIN_SHIFT);

  /* Enable interrupt on completed conversion */
  ADC_IntEnable(ADC0, ADC_IEN_SINGLE);
  NVIC_ClearPendingIRQ(ADC0_IRQn);
  NVIC_EnableIRQ(ADC0_IRQn);

}

/***************************************************************************//**
 * @brief Setup GPIO interrupt for pushbuttons.
 *****************************************************************************/
static void gpioSetup(void)
{
  /* Enable GPIO clock */
  CMU_ClockEnable(cmuClock_GPIO, true);

  /* Enable si7021 sensor isolation switch */
  GPIO_PinModeSet(gpioPortC, 8, gpioModePushPull, 1);

	/* Setup USART0 as the master */
  GPIO_PinModeSet (gpioPortE, 10, gpioModePushPull, 0);	  /* MOSI */
  GPIO_PinModeSet (gpioPortE, 11, gpioModeInputPull, 1);	/* MISO */
  GPIO_PinModeSet (gpioPortE, 12, gpioModePushPull, 0);	  /* CLK */
  GPIO_PinModeSet (CHIP_EN_PORT, CHIP_EN_PIN ,gpioModePushPull , 0 ); //PB11 chip select onboar Pin 11

  GPIO_PinModeSet (CHIP_INT_PORT, CHIP_INT_PIN ,gpioModeInputPull , 0); //PA1 chip select onboard Pin13
  GPIO_ExtIntConfig(CHIP_INT_PORT , CHIP_INT_PIN , CHIP_INT_PIN , true, false, true);

  GPIO_PinModeSet(BSP_GPIO_PB0_PORT, BSP_GPIO_PB0_PIN, gpioModeInputPull, 1);
  GPIO_IntConfig(BSP_GPIO_PB0_PORT, BSP_GPIO_PB0_PIN, false, true, true);

  GPIO_IntClear(1<<CHIP_INT_PIN);
  GPIO_IntClear(1<<BSP_GPIO_PB0_PIN);

  GPIO_PortOutClear(CHIP_EN_PORT, CHIP_EN_PIN);
}

/***************************************************************************//**
 * @brief   The actual callback for Memory LCD toggling
 * @param[in] id
 *   The id of the RTC timer (not used)
 ******************************************************************************/
static void memLcdCallback(RTCDRV_TimerID_t id, void *user)
{
  (void) id;
  (void) user;
  rtcCallback(rtcCallbackArg);
}

/***************************************************************************//**
 * @brief   Register a callback function at the given frequency.
 *
 * @param[in] pFunction  Pointer to function that should be called at the
 *                       given frequency.
 * @param[in] argument   Argument to be given to the function.
 * @param[in] frequency  Frequency at which to call function at.
 *
 * @return  0 for successful or
 *         -1 if the requested frequency does not match the RTC frequency.
 ******************************************************************************/
int rtcIntCallbackRegister(void (*pFunction)(void*),
                           void* argument,
                           unsigned int frequency)
{
  RTCDRV_TimerID_t timerId;
  rtcCallback    = pFunction;
  rtcCallbackArg = argument;

  RTCDRV_AllocateTimer(&timerId);

  RTCDRV_StartTimer(timerId, rtcdrvTimerTypePeriodic, 1000 / frequency,
                    memLcdCallback, NULL);

  return 0;
}

/***************************************************************************//**
 * @brief Callback used to count between measurement updates
 ******************************************************************************/
static void periodicUpdateCallback(RTCDRV_TimerID_t id, void *user)
{
  (void) id;
  (void) user;
  updateDisplay = true;
  updateMeasurement = true;
}
