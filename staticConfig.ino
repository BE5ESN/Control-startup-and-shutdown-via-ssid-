#include "staticConfig.h"
#include "FlashMemory.h"
#define ADDRESS_SCFG_WIFI 0
#define ADDRESS_MODE (ADDRESS_SCFG_WIFI+sizeof(SCFG_wifiUse))
void scfg_init(void)
{
    FlashMemory.read(); // 8K字节
}

void scfg_write(unsigned int address, unsigned char *buf, unsigned int len)
{
    FlashMemory.read();
    for (unsigned int ii = 0; ii < len; ii++)
    {
        FlashMemory.buf[ii + address] = buf[ii];
    }
    FlashMemory.update();
}

void scfg_read(unsigned int address, unsigned char *buf, unsigned int len)
{
    FlashMemory.read();
    for (unsigned int ii = 0; ii < len; ii++)
    {
        buf[ii] = FlashMemory.buf[ii + address];
    }
}


void scfg_write(SCFG_wifiUse *wifi)
{
    scfg_write(ADDRESS_SCFG_WIFI,(unsigned char *)wifi,sizeof(SCFG_wifiUse));
}


void scfg_read(SCFG_wifiUse *wifi)
{
    scfg_read(ADDRESS_SCFG_WIFI,(unsigned char *)wifi,sizeof(SCFG_wifiUse));
}

void scfg_write(SCFG_mode *mode)
{
    scfg_write(ADDRESS_MODE,(unsigned char *)mode,sizeof(SCFG_mode));
}

void scfg_read(SCFG_mode *mode)
{
    scfg_read(ADDRESS_MODE,(unsigned char *)mode,sizeof(SCFG_mode));
}