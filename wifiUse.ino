#include "WiFi.h"
#include "wifiUse.h"
#include "helper.h"
#include "staticConfig.h"
WIFIUSE_Parms *wifiParms;
SCFG_wifiUse sWifiContext;
RBool isScanFinished = RFalse;
unsigned int scanGapCnt = 0;
/*目前共两种功能
 *1.findThenTrigger FTT
 *2.machingStaticSSID MSS
 */
#define FTT 0
#define MSS 1
unsigned int mode = FTT;

void wifiuse_init(WIFIUSE_Parms *parms)
{
    wifiParms = parms;
    DLOG_WRITE("WiFi:initlized...");
    if (WiFi.status() == WL_NO_SHIELD)
    {
        DLOG("WiFi shield not present.");
        while (true)
            ;
    }
    DLOG_WRITE("Get WiFi Staitc Parms");
    scfg_read(&sWifiContext);
    DLOG("Finished");
}
/*开始匹配静态的SSID，需要注意的是它匹配会根据最强的信号来。
最强的那个优先被匹配，一旦开始，只有调用End才会停止，匹配成功后，也得调用end才能退出。*/
void wifiuse_matchingStaticSSID_Begin(void)
{
    scanGapCnt = 0;
    mode = MSS;
    isScanFinished = RFalse;
    DLOG("Begin matching static SSID");
}
/*查询是否匹配成功*/
RBool wifiuse_matchingStaticSSID_isFinished(void)
{
    return isScanFinished;
}
/*退出匹配模式*/
void wifiuse_matchingStaticSSID_End(void)
{
    DLOG("End matching");
    isScanFinished = RFalse;
    scanGapCnt = 0;
    mode = FTT;
}

RBool isStaticHamFound = RFalse;
unsigned int staticHamLostCnt = 0;
RBool isOtherHamFound = RFalse;
unsigned int otherHamLostCnt = 0;
int numSsid = 0;
char *endWith = "_HAM";
char ssid[33];
#define HAM_LOST_CNT 3
int32_t rssi = -1000;

void wifiuse_service(void)
{
    switch (mode)
    {
    case FTT:
        scanGapCnt++;
        if (scanGapCnt >= 1500)
        {
            scanGapCnt = 0;
            numSsid = WiFi.scanNetworks();
            if (numSsid > 0)
            {
                isStaticHamFound = RFalse;
                isOtherHamFound = RFalse;
                for (int ii = 0; ii < numSsid; ii++)
                {
                    if (isEndWith(WiFi.SSID(ii), endWith) == 0)
                    {
                        DLOG_WRITE("FOUND ");
                        if (sWifiContext.isSaved == RTrue)
                        {
                            if (strcmp(sWifiContext.SSID, WiFi.SSID(ii)) == 0)
                            {
                                DLOG_WRITE("STATIC ");
                                wifiParms->onStaticHAMSSIDFound();
                                isStaticHamFound = RTrue;
                                staticHamLostCnt = 0;
                            }
                        }
                        DLOG_WRITE("HAM.");
                        wifiParms->onHAMSSIDFound(WiFi.SSID(ii));
                        isOtherHamFound = RTrue;
                        otherHamLostCnt = 0;
                    }
                }

                if (isStaticHamFound == RFalse && sWifiContext.isSaved == RTrue)
                {
                    if (staticHamLostCnt == HAM_LOST_CNT)
                    {
                        staticHamLostCnt++;
                        DLOG_WRITE("LOST STATIC HAM.");
                        wifiParms->onStaticHAMSSIDLost();
                    }
                    else
                    {
                        staticHamLostCnt++;
                    }
                }

                if (isOtherHamFound == RFalse)
                {
                    if (otherHamLostCnt == HAM_LOST_CNT)
                    {
                        otherHamLostCnt++;
                        DLOG_WRITE("LOST HAM.");
                        wifiParms->onHAMSSIDLost();
                    }
                    else
                    {
                        otherHamLostCnt++;
                    }
                }
            }
        }
        break;
    case MSS:
        scanGapCnt++;
        if (scanGapCnt >= 100) // 1秒扫描一次
        {
            DLOG("matching...");
            rssi = -1000;
            scanGapCnt = 0;
            numSsid = WiFi.scanNetworks();
            if (numSsid > 0)
            {

                for (int ii = 0; ii < numSsid; ii++)
                {
                    if (isEndWith(WiFi.SSID(ii), endWith) == 0 && rssi < WiFi.RSSI(ii))
                    {
                        rssi = WiFi.RSSI(ii);
                        strcpy(ssid, WiFi.SSID(ii));
                        isScanFinished = RTrue;
                    }
                }

                if (isScanFinished == RTrue)
                {
                    isScanFinished = RFalse;
                    DLOG("FOUND, FINISH MATCHING...");
                    sWifiContext.isSaved = RTrue;
                    strcpy(sWifiContext.SSID, ssid);
                    scfg_write(&sWifiContext);
                    wifiParms->onMatchingFinished();
                    mode = FTT;
                }
            }
        }

        break;
    default:
        break;
    }
}