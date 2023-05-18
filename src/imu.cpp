#include "imu.h"

MPU9250 mpu;

#define mpu_filter 100

int mpu_iter = 0;

struct mpu_data
{
    float accelX_acc, accelY_acc, accelZ_acc;
    float gyroX_acc, gyroY_acc, gyroZ_acc;
    float magX_acc, magY_acc, magZ_acc;
    float yaw_acc, pitch_acc, roll_acc;
    float temp_acc;
};

struct mpu_data mpu_acc = {};

bool init_mpu9250()
{
    Wire.setSDA(MPU9250_SDA);
    Wire.setSCL(MPU9250_SCL);
    Wire.begin();
    delay(50);

    return mpu.setup(0x68);
}

void get_mpu9250()
{
    if (mpu.update())
    {
        mpu_iter++;

        mpu_acc.accelX_acc += mpu.getAccX();
        mpu_acc.accelY_acc += mpu.getAccY();
        mpu_acc.accelZ_acc += mpu.getAccZ();

        mpu_acc.gyroX_acc += mpu.getGyroX();
        mpu_acc.gyroY_acc += mpu.getGyroY();
        mpu_acc.gyroZ_acc += mpu.getGyroZ();

        mpu_acc.magX_acc += mpu.getMagX();
        mpu_acc.magY_acc += mpu.getMagY();
        mpu_acc.magZ_acc += mpu.getMagZ();

        mpu_acc.yaw_acc += mpu.getYaw();
        mpu_acc.pitch_acc += mpu.getPitch();
        mpu_acc.roll_acc += mpu.getRoll();

        mpu_acc.temp_acc += mpu.getTemperature();

        if (mpu_iter >= mpu_filter)
        {
            mpu_iter = 0;

            m_asv_data.accelX = mpu_acc.accelX_acc / mpu_filter;
            m_asv_data.accelY = mpu_acc.accelY_acc / mpu_filter;
            m_asv_data.accelZ = mpu_acc.accelZ_acc / mpu_filter;

            m_asv_data.gyroX = mpu_acc.gyroX_acc / mpu_filter;
            m_asv_data.gyroY = mpu_acc.gyroY_acc / mpu_filter;
            m_asv_data.gyroZ = mpu_acc.gyroZ_acc / mpu_filter;

            m_asv_data.magX = mpu_acc.magX_acc / mpu_filter;
            m_asv_data.magY = mpu_acc.magY_acc / mpu_filter;
            m_asv_data.magZ = mpu_acc.magZ_acc / mpu_filter;

            m_asv_data.yaw = mpu_acc.yaw_acc / mpu_filter;
            m_asv_data.pitch = mpu_acc.pitch_acc / mpu_filter;
            m_asv_data.roll = mpu_acc.roll_acc / mpu_filter;

            m_asv_data.temp = mpu_acc.temp_acc / mpu_filter;

            mpu_acc = {};
        }
    }
}