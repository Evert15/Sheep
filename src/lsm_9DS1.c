#include "../inc/lsm_9DS1.h"
#include "em_device.h"
#include <stdint.h>
#include "em_chip.h"
#include "em_cmu.h"
#include "bsp.h"


void usart0_Master_Setup (void)
{
	CMU_ClockEnable (cmuClock_USART0, true);

	/*
	 * Use default configuration and specify clock and frame size.
	 */
	USART_InitSync_TypeDef init = USART_INITSYNC_DEFAULT;

	init.databits = usartDatabits8;
	init.baudrate = 1000000;
	init.msbf = true;
	USART_InitSync (USART0, &init);

	/* Turn on automatic Chip Select control */
	USART0->CTRL |= USART_CTRL_AUTOCS;

	/* Enable SPI transmit and receive */
	USART_Enable (USART0, usartEnable);

	/* Route USART0 pins to port A locations and enable */
	USART0->ROUTE = USART_ROUTE_LOCATION_LOC0 |
	                USART_ROUTE_CLKPEN |
	                USART_ROUTE_CSPEN |
	                USART_ROUTE_TXPEN |
	                USART_ROUTE_RXPEN;

}


void Chip_write_8_bit_data (uint8_t adr , uint8_t data){
	 USART0->CTRL |= USART_CTRL_MSBF;
	GPIO_PinOutClear(CHIP_EN_PORT, CHIP_EN_PIN);
	uint8_t adres;
	adres = (0x00 << 7) | adr;
	USART_SpiTransfer(USART0 , adres); // send the 8 adress bits
	USART_SpiTransfer(USART0 , data); // sent the 8 data bits
	GPIO_PinOutSet(CHIP_EN_PORT, CHIP_EN_PIN);
	}

uint8_t Chip_read_8_bit_data (uint8_t adr){
	 USART0->CTRL |= USART_CTRL_MSBF;
	GPIO_PinOutClear(CHIP_EN_PORT, CHIP_EN_PIN);
	uint8_t adres;
	adres = (0x01 << 7) | adr;
	USART_SpiTransfer(USART0 , adres);
	uint8_t data = USART_SpiTransfer(USART0 , 0x00); // dummy bit to send
	GPIO_PinOutSet(CHIP_EN_PORT, CHIP_EN_PIN);
	return  data;


}

void LSM9DS1_init(){
	Chip_write_8_bit_data(LSM9DS1_REGISTER_CTRL_REG5_XL, 0x38);
	Chip_write_8_bit_data(LSM9DS1_REGISTER_CTRL_REG6_XL, 0x48);// here you can set the amount of G you can input
	Chip_write_8_bit_data(LSM9DS1_REGISTER_CTRL_REG9,0x44);
	Chip_write_8_bit_data(LSM9DS1_REGISTER_INT1_CTRL,0x40);


}

void LSM9DS1_int_init(){
	Chip_write_8_bit_data(LSM9DS1_REGISTER_INT_GEN_CFG_XL,0x7F);
	Chip_write_8_bit_data(LSM9DS1_REGISTER_INT_GEN_THS_X_XL,LSM9DS1_INT_THRES);
	Chip_write_8_bit_data(LSM9DS1_REGISTER_INT_GEN_THS_Y_XL,LSM9DS1_INT_THRES);
	Chip_write_8_bit_data(LSM9DS1_REGISTER_INT_GEN_THS_Z_XL,LSM9DS1_INT_THRES);

}
