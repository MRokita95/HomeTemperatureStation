/*
 * i2c_utils.h
 *
 *  Created on: Sep 3, 2022
 *      Author: micha
 */

#ifndef IMU_INC_I2C_UTILS_H_
#define IMU_INC_I2C_UTILS_H_

#include "stm32f4xx_hal.h"
#include "stdbool.h"

#define BLOCKING_MODE_ACTIVE 1

#if BLOCKING_MODE_ACTIVE
	typedef HAL_StatusTypeDef (*master_send_fnc)(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout);
	typedef HAL_StatusTypeDef (*master_recv_fnc)(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout);
	typedef HAL_StatusTypeDef (*slave_send_fnc)(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t Size, uint32_t Timeout);
	typedef HAL_StatusTypeDef (*slave_recv_fnc)(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t Size, uint32_t Timeout);
	typedef HAL_StatusTypeDef (*mem_write_fnc)(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout);
	typedef HAL_StatusTypeDef (*mem_read_fnc)(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout);

#else

#endif

/* default timeout */
#define I2CDEV_DEFAULT_READ_TIMEOUT     10u
#define I2CDEV_DEFAULT_WRITE_TIMEOUT    10u

/********************************************
 *			PRIVATE FUNCTIONS				*
 ********************************************/

/*
master_send_fnc I2C_Master_Send = HAL_I2C_Master_Transmit;
master_recv_fnc I2C_Master_Recv = HAL_I2C_Master_Receive;
slave_send_fnc I2C_Slave_Send = HAL_I2C_Slave_Transmit;
slave_recv_fnc I2C_Slave_Recv = HAL_I2C_Slave_Receive;
mem_write_fnc I2C_Mem_Write = HAL_I2C_Mem_Write;
mem_read_fnc I2C_Mem_Read = HAL_I2C_Mem_Read;
*/


#define I2C_readByte(I2C, address, regAddr, data) HAL_I2C_Mem_Read(I2C, address, regAddr, 1u, data, 1u, I2CDEV_DEFAULT_READ_TIMEOUT)
#define I2C_writeByte(I2C, address, regAddr, data) HAL_I2C_Mem_Write(I2C, address, regAddr, 1u, data, 1u, I2CDEV_DEFAULT_WRITE_TIMEOUT)

#define I2C_readBytes(I2C, address, regAddr, n, data) HAL_I2C_Mem_Read(I2C, address, regAddr, 1u, data, n, I2CDEV_DEFAULT_READ_TIMEOUT)
#define I2C_writeBytes(I2C, address, regAddr, n, data) HAL_I2C_Mem_Write(I2C, address, regAddr, 1u, data, n, I2CDEV_DEFAULT_WRITE_TIMEOUT)


#endif /* IMU_INC_I2C_UTILS_H_ */
