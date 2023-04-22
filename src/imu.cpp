#include "imu.h"

void init_mpu9250()
{
    Wire.setSDA(MPU9250_SDA);
    Wire.setSCL(MPU9250_SCL);
    Wire.begin();
    delay(50);

    if (!mpu.setup(0x68))
    { // change to your own address
        while (1)
        {
            Serial.println("MPU connection failed. Please check your connection with `connection_check` example.");
            delay(50);
        }
    }
}

void get_mpu9250()
{
    if (mpu.update())
    {
        static uint32_t prev_ms = millis();
        if (millis() > prev_ms + 25)
        {
            print_roll_pitch_yaw();
            prev_ms = millis();
        }
    }
}

void print_roll_pitch_yaw()
{
    Serial.print("Yaw, Pitch, Roll: ");
    Serial.print(mpu.getYaw(), 2);
    Serial.print(", ");
    Serial.print(mpu.getPitch(), 2);
    Serial.print(", ");
    Serial.print(mpu.getRoll(), 2);
    Serial.print("  |  Temp: ");
    Serial.println(mpu.getTemperature(), 2);
}