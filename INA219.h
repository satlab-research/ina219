#ifndef INA219_H
#define INA219_H

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"


#define INA_ADDR     _u(0x40)
#define R_SHUNT      0.1
#define CURRENT_LSB  0.0001   // ohm

// INA219 Register Map
#define CONFIG_REG           _u(0x00)
#define SHUNT_VOLTAGE_REG    _u(0X01)
#define BUS_VOLTAGE_REG      _u(0x02)
#define POWER_REG            _u(0x03)
#define CURRENT_REG          _u(0x04)
#define CALIBRATION_REG      _u(0X05)


class INA219
{
    private:
        i2c_inst_t* inst;
        int sda;
        int scl;
    
    public:
        
        bool ina_config();

        bool read_current(float *current);

        INA219(i2c_inst_t* inst, int sda, int scl);
        ~INA219();
};


#endif



