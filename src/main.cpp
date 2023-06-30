#include "main.h"

unsigned long int t, n;

int state = ERROR;

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

#if DEBUG_LED
  pinMode(DEBUG_LED, OUTPUT);
#endif

#if USE_IMU
  connectedIMU = init_imu();
#endif

  init_motors();

  t = millis();

  m_asv_data = {0};

  state = READY;
}

void loop()
{
  if (state != ERROR)
  {
    n = millis();

    parser(Serial.read());

    get_values();

    if ((n - t) >= 500)
    {
#if DEBUG_LED
      digitalWrite(DEBUG_LED, HIGH);
#endif

      send_data();

#if DEBUG_LED
      digitalWrite(DEBUG_LED, LOW);
#endif

      t = millis();
    }

    if (millis() - start <= 5000)
    {
      ASVmotors.pwmL = 7.5f;
      ASVmotors.pwmR = 7.5f;
    }
  }
  else
    Serial.println("ERROR!!!");

  actuate_motors();
}