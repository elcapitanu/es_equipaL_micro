#ifndef IMU_H
#define IMU_H

#include <Arduino.h>

#include "MPU9250.h"

#include "asv.h"

#include "../config.h"

extern MPU9250 mpu;

void init_mpu9250();
void get_mpu9250();
void print_roll_pitch_yaw();

#endif