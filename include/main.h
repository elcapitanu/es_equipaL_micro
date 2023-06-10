#ifndef MAIN_H
#define MAIN_H

#include <Arduino.h>

#include "../config.h"

#include "usart.h"
#include "parser.h"
#include "motor.h"
#include "imu.h"
#include "asv.h"

typedef enum
{
    ERROR = 0,
    READY = 1,
    SERVICE = 2
} m_state;

extern int state;

extern bool connectedIMU;

bool isIMUconnected();
void lostIMU();

#endif