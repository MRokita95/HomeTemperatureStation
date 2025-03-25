/*
 * Seeed_MCP9808.h
 * Driver for DIGITAL I2C HUMIDITY AND TEMPERATURE SENSOR
 *  
 * Copyright (c) 2018 Seeed Technology Co., Ltd.
 * Website    : www.seeed.cc
 * Author     : downey
 * Create Time: May 2018
 * Change Log :
 *
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#ifndef _SEEED_MCP9808_H
#define _SEEED_MCP9808_H

#define SET_CONFIG_ADDR           0X01
#define SET_UPPER_LIMIT_ADDR      0X02
#define SET_LOWER_LIMIT_ADDR      0X03
#define SET_CRITICAL_LIMIT_ADDR   0X04

#define AMBIENT_TEMPERATURE_ADDR  0X05
#define SET_RESOLUTION_ADDR       0X08


#define DEFAULT_IIC_ADDR  0x18


#define RESOLUTION_0_5_DEGREE               0
#define RESOLUTION_0_25_DEGREE              0X01
#define RESOLUTION_0_125_DEGREE             0X02
#define RESOLUTION_0_0625_DEGREE            0X03
#define SIGN_BIT                            0X10

#include "stm32f4xx_hal.h"
#include <stdbool.h>


HAL_StatusTypeDef MPC_init(uint8_t addr, I2C_HandleTypeDef * i2c_dev);
HAL_StatusTypeDef MPC_set_config(uint16_t cfg);
HAL_StatusTypeDef MPC_set_upper_limit(uint16_t cfg);
HAL_StatusTypeDef MPC_set_lower_limit(uint16_t cfg);
HAL_StatusTypeDef MPC_set_critical_limit(uint16_t cfg);
HAL_StatusTypeDef MPC_read_temp_reg(uint16_t *temp);
void MPC_get_temp(float *temp);
HAL_StatusTypeDef MPC_set_resolution(uint8_t resolution);
void MPC_get_alarms(bool *crit, bool* upper, bool* lower);





#endif
