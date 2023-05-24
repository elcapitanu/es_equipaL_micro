#include "motor.h"

struct motors ASVmotors = {0};

RP2040_PWM *PWM_motorL;
RP2040_PWM *PWM_motorR;

void init_motors()
{
    PWM_motorL = new RP2040_PWM(PIN_motorL, 50, 0);
    PWM_motorR = new RP2040_PWM(PIN_motorR, 50, 0);

    ASVmotors.pwmL = 7.5f;
    ASVmotors.pwmR = 7.5f;
}

void actuate_motors()
{
#if PWM_DEBUG
    Serial.print("PWM L: ");
    Serial.print(ASVmotors.pwmL);
    Serial.print("| PWM R: ");
    Serial.println(ASVmotors.pwmR);
#endif

    PWM_motorL->setPWM(PIN_motorL, 50, ASVmotors.pwmL);
    PWM_motorR->setPWM(PIN_motorR, 50, ASVmotors.pwmR);
}