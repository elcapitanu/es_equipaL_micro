#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

#include <RP2040_PWM.h>

#include "../config.h"

struct motors
{
    float pwmL;
    float pwmR;
};

extern struct motors ASVmotors;

extern RP2040_PWM *PWM_motorL;
extern RP2040_PWM *PWM_motorR;

void init_motors();
void actuate_motors();

#endif