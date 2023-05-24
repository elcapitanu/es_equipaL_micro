#ifndef IMU_H
#define IMU_H

#include <Arduino.h>

#include "ICM_20948.h"

#include "main.h"
#include "asv.h"

#include "../config.h"

extern ICM_20948_I2C myICM;

bool init_imu();
void get_imu();

#endif