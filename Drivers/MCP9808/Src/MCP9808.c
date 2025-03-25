#include "MCP9808.h"

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include "stm32f4xx_hal.h"
#include "i2c_utils.h"


static uint8_t _i2c_addr = DEFAULT_IIC_ADDR;
static I2C_HandleTypeDef * _i2c_dev;
static uint16_t _resolution = RESOLUTION_0_0625_DEGREE;
static float _res_factor_n = 2.f;
static float _res_factor_1_per_n = 0.5f;

static void set_iic_addr(uint8_t IIC_ADDR);


HAL_StatusTypeDef MPC_set_config(uint16_t cfg)
{
    return I2C_writeBytes(_i2c_dev, _i2c_addr, SET_CONFIG_ADDR, 2, cfg);
}


HAL_StatusTypeDef MPC_set_upper_limit(uint16_t cfg)
{
    return I2C_writeBytes(_i2c_dev, _i2c_addr, SET_UPPER_LIMIT_ADDR, 2, cfg);
}

HAL_StatusTypeDef MPC_set_lower_limit(uint16_t cfg)
{
    return I2C_writeBytes(_i2c_dev, _i2c_addr, SET_LOWER_LIMIT_ADDR, 2, cfg);
}


HAL_StatusTypeDef MPC_set_critical_limit(uint16_t cfg)
{
    return I2C_writeBytes(_i2c_dev, _i2c_addr, SET_CRITICAL_LIMIT_ADDR, 2, cfg);
}

HAL_StatusTypeDef MPC_set_resolution(uint8_t resolution)
{
    _resolution = resolution;
    if (_resolution == RESOLUTION_0_0625_DEGREE){
        _res_factor_n = 16;
        _res_factor_1_per_n = 0.0625;
    } else if (_resolution == RESOLUTION_0_125_DEGREE){
        _res_factor_n = 8;
        _res_factor_1_per_n = 0.125;
    } else if (_resolution == RESOLUTION_0_25_DEGREE){
        _res_factor_n = 4;
        _res_factor_1_per_n = 0.25;
    }

    return I2C_writeByte(_i2c_dev, _i2c_addr, SET_RESOLUTION_ADDR, _resolution);
}

HAL_StatusTypeDef MPC_read_temp_reg(uint16_t *temp)
{
	uint8_t buffer[2];
	HAL_StatusTypeDef status = I2C_readBytes(_i2c_dev, _i2c_addr, AMBIENT_TEMPERATURE_ADDR, 2, buffer);
    *temp = (buffer[0] << 8) + buffer[1];
    return status;
}

static float caculate_temp(uint16_t temp_value)
{
    float temp=0;
    uint8_t temp_upper=0,temp_lower=0;
    temp_upper=(uint8_t)(temp_value>>8);
    temp_lower=(uint8_t)temp_value;

    temp_upper&=0x1f;	//cut off crit bits
    if((temp_upper&SIGN_BIT))
    {
        temp_upper&=0x0f;
        temp=256-(temp_upper*_res_factor_n+temp_lower*_res_factor_1_per_n);
        temp*=-1;
    } else {
    	temp=temp_upper*_res_factor_n+temp_lower*_res_factor_1_per_n;
    }
    return temp;
}


void MPC_get_temp(float *temp)
{
    uint16_t temp_value=0;
    HAL_StatusTypeDef sts = MPC_read_temp_reg(&temp_value);
    if (sts != HAL_OK){
    	*temp=0;
    	return;
    }
    *temp=caculate_temp(temp_value);
}

void MPC_get_alarms(bool *crit, bool* upper, bool* lower)
{
    static const uint16_t crit_mask = 0x8000;
    static const uint16_t upper_mask = 0x4000;
    static const uint16_t lower_mask = 0x2000;

    uint16_t reg_value=0;
    HAL_StatusTypeDef sts = MPC_read_temp_reg(&reg_value);
    if (sts != HAL_OK){
    	reg_value=0;
    }
    *crit=(reg_value & crit_mask) != 0u;
    *upper=(reg_value & upper_mask) != 0u;
    *lower=(reg_value & lower_mask) != 0u;
}




HAL_StatusTypeDef MPC_init(uint8_t IIC_ADDR, I2C_HandleTypeDef * i2c_dev)
{
    _i2c_dev = i2c_dev;
    set_iic_addr(_i2c_addr);
    return MPC_set_resolution(_resolution);
}

static void set_iic_addr(uint8_t addr)
{
	_i2c_addr=addr<<1;
}
