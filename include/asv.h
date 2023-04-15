#ifndef ASV_H
#define ASV_H

#include <Arduino.h>

#include "../config.h"

struct ASV_data
{
    // MPU9250
    float accelX, accelY, accelZ;
    float gyroX, gyroY, gyroZ;
    float magX, magY, magZ;
    float temp;
    //other sensors...
};

extern struct ASV_data m_asv_data;

void init_mpu9250();
void get_mpu9250();

void get_values();

#endif