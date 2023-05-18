#ifndef IMU_H
#define IMU_H

#include <Arduino.h>

#include "MPU9250.h"

#include "main.h"
#include "asv.h"

#include "../config.h"

extern MPU9250 mpu;

bool init_mpu9250();
void get_mpu9250();

#endif