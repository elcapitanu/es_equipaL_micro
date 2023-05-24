#include "main.h"

unsigned long int t, n;

bool connectedIMU = false;

bool isIMUconnected()
{
  return connectedIMU;
}

void lostIMU()
{
  connectedIMU = !connectedIMU;
  return;
}

void setup()
{
  Serial.begin(115200);
  while (!Serial)
    delay(100);

#if DEBUGF_LED
  pinMode(DEBUG_LED, OUTPUT);
#endif

#if USE_IMU
  connectedIMU = init_imu();
#endif

  init_motors();

  t = millis();
}

void loop()
{
  n = millis();

  parser(Serial.read());

  get_values();

  if ((n - t) >= 1000)
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