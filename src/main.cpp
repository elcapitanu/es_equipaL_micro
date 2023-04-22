#include "main.h"

unsigned long int t, n;

void setup()
{
  Serial.begin(115200);
  while (!Serial)
    delay(100);

#if DEBUGF_LED
  pinMode(DEBUG_LED, OUTPUT);
#endif

#if USE_MPU9250
  init_mpu9250();
#endif

  init_motors();

  t = millis();
}

void loop()
{
  n = millis();

  parser(Serial.read());

  get_values();

  if ((n - t) >= 100)
  {
#if DEBUGF_LED
    digitalWrite(DEBUG_LED, HIGH);
#endif
    send_data();
#if DEBUGF_LED
    digitalWrite(DEBUG_LED, LOW);
#endif
    t = millis();
  }

  if (millis() - start <= 5000)
  {
    ASVmotors.pwmL = 7.5f;
    ASVmotors.pwmR = 7.5f;
  }

  actuate_motors();
}