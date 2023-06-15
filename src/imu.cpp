#include "imu.h"

ICM_20948_I2C myICM;

bool init_imu()
{
    Wire.setSDA(IMU_SDA);
    Wire.setSCL(IMU_SCL);
    Wire.begin();
    Wire.setClock(400000);
    delay(50);

#if IMU_DEBUG
    myICM.enableDebugging();
#endif

    bool initialized = false;
    while (!initialized)
    {
        myICM.begin(Wire, 1);

        if (myICM.status != ICM_20948_Stat_Ok)
            delay(500);
        else
            initialized = true;
    }

    bool success = true;
    success &= (myICM.initializeDMP() == ICM_20948_Stat_Ok);
    success &= (myICM.enableDMPSensor(INV_ICM20948_SENSOR_GAME_ROTATION_VECTOR) == ICM_20948_Stat_Ok);
    success &= (myICM.setDMPODRrate(DMP_ODR_Reg_Quat6, 0) == ICM_20948_Stat_Ok); // Set to the maximum
    success &= (myICM.enableFIFO() == ICM_20948_Stat_Ok);
    success &= (myICM.enableDMP() == ICM_20948_Stat_Ok);
    success &= (myICM.resetDMP() == ICM_20948_Stat_Ok);
    success &= (myICM.resetFIFO() == ICM_20948_Stat_Ok);

    if (success)
        connectedIMU = true;

    return connectedIMU;
}

void get_imu()
{
    icm_20948_DMP_data_t data;
    myICM.readDMPdataFromFIFO(&data);

    if ((myICM.status == ICM_20948_Stat_Ok) || (myICM.status == ICM_20948_Stat_FIFOMoreDataAvail))
    {
        if ((data.header & DMP_header_bitmap_Quat6) > 0)
        {
            double q1 = ((double)data.Quat6.Data.Q1) / 1073741824.0;
            double q2 = ((double)data.Quat6.Data.Q2) / 1073741824.0;
            double q3 = ((double)data.Quat6.Data.Q3) / 1073741824.0;

            double q0 = sqrt(1.0 - ((q1 * q1) + (q2 * q2) + (q3 * q3)));

            double q2sqr = q2 * q2;

            // roll (x-axis rotation)
            double t0 = +2.0 * (q0 * q1 + q2 * q3);
            double t1 = +1.0 - 2.0 * (q1 * q1 + q2sqr);
            double roll = atan2(t0, t1) * 180.0 / PI;

            // pitch (y-axis rotation)
            double t2 = +2.0 * (q0 * q2 - q3 * q1);
            t2 = t2 > 1.0 ? 1.0 : t2;
            t2 = t2 < -1.0 ? -1.0 : t2;
            double pitch = asin(t2) * 180.0 / PI;

            // yaw (z-axis rotation)
            double t3 = +2.0 * (q0 * q3 + q1 * q2);
            double t4 = +1.0 - 2.0 * (q2sqr + q3 * q3);
            double yaw = atan2(t3, t4) * 180.0 / PI;

            m_asv_data.yaw = yaw;
            m_asv_data.pitch = pitch;
            m_asv_data.roll = roll;

            // myICM.getAGMT();

            // m_asv_data.accelX = myICM.accX();
            // m_asv_data.accelY = myICM.accY();
            // m_asv_data.accelZ = myICM.accZ();

            // m_asv_data.gyroX = myICM.gyrX();
            // m_asv_data.gyroY = myICM.gyrY();
            // m_asv_data.gyroZ = myICM.gyrZ();

            // m_asv_data.magX = myICM.magX();
            // m_asv_data.magY = myICM.magY();
            // m_asv_data.magZ = myICM.magZ();

            // m_asv_data.temp = myICM.temp();
        }
    }

    if (myICM.status != ICM_20948_Stat_FIFOMoreDataAvail)
    {
        delay(10);
    }
}