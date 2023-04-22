#include "main.h"

unsigned long int t, n;

void setup()
{
  Serial.begin(115200);
  while(!Serial)
    delay(100);

  pinMode(TX_LED, OUTPUT);

  init_mpu9250();
  init_motors();

  t = millis();
}

void loop()
{
  n = millis();

  parser(Serial.read());

  get_values();

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

  actuate_motors();
}