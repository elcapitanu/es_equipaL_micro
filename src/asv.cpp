#include "asv.h"

struct ASV_data m_asv_data = {0};

void get_values()
{
#if USE_IMU
    if (isIMUconnected())
        get_imu();
#endif
}