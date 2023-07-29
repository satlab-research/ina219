#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

#include "INA219.h"



INA219::INA219(/*i2c_inst_t* inst, int sda, int scl*/)
{
    // this->inst = inst;
    // this->sda = sda;
    // this->scl = scl;

    // I2C Initialisation. Using it at 400 Khz.
    i2c_init(this->inst, 400*1000);
    // I2C Operating frequency for MPU6050: 400 KHz(All registers, Fast-mode), 100 KHz(All registers, Standard-mode)
    
    gpio_set_function(this->sda, GPIO_FUNC_I2C);
    gpio_set_function(this->scl, GPIO_FUNC_I2C);
    gpio_pull_up(this->sda); // To keep line HIGH when no data is online.
    gpio_pull_up(this->scl); // To keep line HIGH when no data is online.
}

INA219::~INA219()
{
}


bool INA219::ina_config()
{
    uint8_t payload[3] = { CALIBRATION_REG, 0x10, 0x00 };
    uint8_t write_status;

    write_status = i2c_write_blocking(this->inst, INA_ADDR, payload, 3, false);

    // if (verbose)
    // {
    //     printf("[OPERATION] I2C WRITE\n");
    //     printf("[DATA] DEVICE ADDERESS = 0x%x\n", INA_ADDR);
    //     printf("[DATA] REGISTER ADDERESS = 0x%x\n", CALIBRATION_REG);
    //     printf("[DATA] PAYLOD =");
    //     for (int i = 0; i < (len + 1); i++)
    //     {
    //         printf(" 0x%x,", payload[i]);
    //     }
    //     printf("\n");
    //     printf("[STATUS] i2c_write = %d\n", write_status);
    //     if (write_status == (len + 1))
    //     {
    //         printf("[SUCCESS] %d bytes written at 0x%x\n", len, CALIBRATION_REG);
    //     }
    //     else
    //     {
    //         printf("[FAIL] ERROR OCCURED\n");
    //     }
    // }

    if (write_status != 3 )
    {
        return false;
    }

    return true;
}

bool INA219::read_current(float *current)
{
    uint8_t write_status;
    uint8_t read_status;
    
    uint8_t buf[] = { CURRENT_REG };
    uint8_t rec[2];

    write_status = i2c_write_blocking(this->inst, INA_ADDR, buf, 1, true);
    sleep_us(10);
    read_status = i2c_read_blocking(this->inst, INA_ADDR, rec, 2, false);

    *current = (rec[0] << 8 | rec[1]) * CURRENT_LSB;

    // printf("%d",write_status);
    // printf("%d",read_status);

    // if (verbose)
    // {
        // printf("[OPERATION] I2C READ\n");
        // printf("[DATA] DEVICE ADDERESS = 0x%x\n", INA_ADDR);
        // printf("[DATA] REGISTER ADDERESS = 0x%x\n", CURRENT_REG);
        // printf("[STATUS] i2c_write = %d\n", write_status);
        // printf("[STATUS] i2c_read = %d\n", read_status);

        // if (write_status != 1)
        // {
        //     printf("[FAIL] Unable to set pointer to address 0x%x\n", CALIBRATION_REG);
        // }
        // else
        // {
        //     printf("[SUCCESS] Pointer set to address 0x%x\n", CALIBRATION_REG);
        // }

        // if (read_status != len)
        // {
        //     printf("[FAIL] Unable to read bytes from address 0x%x\n", CALIBRATION_REG);
        // }
        // else
        // {
        //     printf("[SUCCESS] %d bytes read from address 0x%x\n", len, CALIBRATION_REG);
        // }

    //     printf("[DATA] BUFFER =");
    //     for (int i = 0; i < len; i++)
    //     {
    //         printf(" 0x%x,", buffer[i]);
    //     }
    //     printf("\n");
    // }

    if (write_status != 1)
    {
        return false;
    }

    if (read_status != 2)
    {
        return false;
    }

    return true;
}

