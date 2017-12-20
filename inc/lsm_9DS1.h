#include "em_device.h"
#include <stdint.h>

#define 	 LSM9DS1_REGISTER_WHO_AM_I_XG 	      0x0F
#define      LSM9DS1_REGISTER_STATUS_REG          0x17
#define      LSM9DS1_REGISTER_CTRL_REG4           0x1E
#define      LSM9DS1_REGISTER_CTRL_REG5_XL        0x1F
#define      LSM9DS1_REGISTER_CTRL_REG6_XL        0x20
#define      LSM9DS1_REGISTER_CTRL_REG7_XL        0x21
#define      LSM9DS1_REGISTER_CTRL_REG8           0x22
#define      LSM9DS1_REGISTER_CTRL_REG9           0x23
#define      LSM9DS1_REGISTER_CTRL_REG10          0x24


#define		 LSM9DS1_REGISTER_INT_GEN_THS_X_XL	  0x07
#define		 LSM9DS1_REGISTER_INT_GEN_THS_Y_XL	  0x08
#define		 LSM9DS1_REGISTER_INT_GEN_THS_Z_XL	  0x09
#define 	 LSM9DS1_REGISTER_INT_GEN_CFG_XL	  0x06
#define 	 LSM9DS1_REGISTER_INT1_CTRL			  0x0C

#define      LSM9DS1_REGISTER_OUT_X_L_XL          0x28
#define      LSM9DS1_REGISTER_OUT_X_H_XL          0x29
#define      LSM9DS1_REGISTER_OUT_Y_L_XL          0x2A
#define      LSM9DS1_REGISTER_OUT_Y_H_XL          0x2B
#define      LSM9DS1_REGISTER_OUT_Z_L_XL          0x2C
#define      LSM9DS1_REGISTER_OUT_Z_H_XL          0x2D

#define 	 LSM9DS1_INT_THRES					  0x14

#define		 CHIP_EN_PIN						  11// Pin 11
#define		 CHIP_INT_PIN						  1 //pin 1
#define		 CHIP_EN_PORT						  1 //Port B
#define		 CHIP_INT_PORT						  0 //Port A


void usart0_Master_Setup (void);
void Chip_write_8_bit_data (uint8_t adr , uint8_t data);
uint8_t Chip_read_8_bit_data (uint8_t adr);
void LSM9DS1_init();
void LSM9DS1_int_init();
