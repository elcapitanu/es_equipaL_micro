#include "main.h"

unsigned long int t, n;

RP2040_PWM *PWM_motorL;
RP2040_PWM *PWM_motorR;

float a = 7.5f;

void setup()
{
  Serial.begin(115200);

  pinMode(TX_LED, OUTPUT);

  PWM_motorL = new RP2040_PWM(PIN_motorL, 50, 0);
  PWM_motorR = new RP2040_PWM(PIN_motorR, 50, 0);

  ASVmotors.pwmL = 7.5f;
  ASVmotors.pwmR = 7.5f;

  t = millis();
}

void loop()
{
  n = millis();

  parser(Serial.read());

  if ((n - t) >= 200)
  {
    digitalWrite(TX_LED, HIGH);
    send_data();
    digitalWrite(TX_LED, LOW);
    t = millis();
  }

  if (millis() - start <= 5000)
  {
    ASVmotors.pwmL = 7.5f;
    ASVmotors.pwmR = 7.5f;
  }

  PWM_motorL->setPWM(PIN_motorL, 50, ASVmotors.pwmL);
  PWM_motorR->setPWM(PIN_motorR, 50, ASVmotors.pwmR);
}