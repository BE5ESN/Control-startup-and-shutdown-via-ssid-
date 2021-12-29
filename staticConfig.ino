#include "staticConfig.h"
#include "FlashMemory.h"
#define ADDRESS_SCFG_WIFI 0

void scfg_init(void)
{
    FlashMemory.read(); // 8K字节
}

void scfg_write(SCFG_wifiUse *wifi)
{
    unsigned char *ptr = (unsigned char *)wifi;
    for (unsigned int ii = 0; ii < sizeof(SCFG_wifiUse); ii++)
    {
        FlashMemory.buf[ii + ADDRESS_SCFG_WIFI] = ptr[ii];
    }
    FlashMemory.update();
}

void scfg_read(SCFG_wifiUse *wifi)
{
    FlashMemory.read();
    unsigned char *ptr = (unsigned char *)wifi;
    for (unsigned int ii = 0; ii < sizeof(SCFG_wifiUse); ii++)
    {
        ptr[ii] = FlashMemory.buf[ii + ADDRESS_SCFG_WIFI];
    }
}