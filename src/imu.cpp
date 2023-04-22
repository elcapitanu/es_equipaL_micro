#include "imu.h"

MPU9250 mpu;

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
        m_asv_data.accelX = mpu.getAccX();
        m_asv_data.accelY = mpu.getAccY();
        m_asv_data.accelZ = mpu.getAccZ();
        
        m_asv_data.gyroX = mpu.getGyroX();
        m_asv_data.gyroY = mpu.getGyroY();
        m_asv_data.gyroZ = mpu.getGyroZ();

        m_asv_data.yaw = mpu.getYaw();
        m_asv_data.pitch = mpu.getPitch();
        m_asv_data.roll = mpu.getRoll();

        m_asv_data.temp = mpu.getTemperature();
    }
}