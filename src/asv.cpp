#include "asv.h"

struct ASV_data m_asv_data = {0};

void get_values()
{
#if USE_MPU9250
    if (isMPUconnected())
        get_mpu9250();
#endif
}