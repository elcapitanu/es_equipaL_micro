#ifndef ASV_H
#define ASV_H

#include <Arduino.h>

#include "imu.h"

#include "../config.h"

struct ASV_data
{
    // MPU9250
    float accelX, accelY, accelZ;
    float gyroX, gyroY, gyroZ;
    float magX, magY, magZ;
    float yaw, pitch, roll;
    float temp;
    //other sensors...
};

extern struct ASV_data m_asv_data;

void get_values();

#endif