#ifndef __WIFIUSE_H__
#define __WIFIUSE_H__
#include "def.h"
#include "WiFi.h"
typedef struct
{
    void (*onHAMSSIDFound)(char*);
    void (*onHAMSSIDLost)();
    void (*onStaticHAMSSIDFound)(void);
    void (*onStaticHAMSSIDLost)(void);
    void (*onMatchingFinished)(void);
}WIFIUSE_Parms;

/*初始化wifi使用*/
void wifiuse_init(WIFIUSE_Parms *cfg);
/*开始匹配静态的SSID，需要注意的是它匹配会根据最强的信号来。
最强的那个优先被匹配。*/
void wifiuse_matchingStaticSSID_Begin(void);
/*查询是否匹配成功*/
void wifiuse_matchingStaticSSID_End(void);
RBool wifiuse_matchingStaticSSID_isFinished(void);
void wifiuse_service(void);

#endif

