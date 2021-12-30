#include <WiFi.h>
#include "WDT.h"
#include <GTimer.h>
#include "def.h"
#include "string.h"
#include "key.h"
#include "led.h"
#include "staticConfig.h"
#include "wifiUse.h"

/*功能说明:
    共有两种模式
    0.常开常关模式
    1.检测WIFI模式
    (检测WIFI仅检测SSID，并不需要连接)

    操作方式为，按键单次短按，在不同模式下切换。
    按键将循环模式。
    模式1.灯常亮，代表开启。
    模式2.灯熄灭，代表关闭。
    模式3.灯闪烁2次，代表进入WIFI检测模式，当扫描到指定WIFI后，将打开电源，如果没有进行长按，该模式可能一直无法工作。
    模式4.灯闪烁3次，代表进入WIFI检测模式，该模式和上面模式相同，不同的是他发现任何带HAM结尾的WIFI都会打开电源。

    长按后,设备开始闪烁，设备将检测WIFI并记录带有HAM结尾的SSID，存储在记录中，检测到后自动退出。
    再次长按主动退出检测模式。

    本项目完全开源，目前没有实现APRS功能，如果您有能力，完全可以在该模块上集成APRS功能，在PCBA上已经引出了所有引脚。
    更多有意思的功能期待您的开发。
    为了避免频繁网络检测，检测间隔设置为15秒，而检测本身会需要5秒左右。
*/

/*基本简单的代码框架为事件驱动模型，在写函数的时候，注意不要写阻塞性的代码，如delay*/
SCFG_wifiUse sWifiUseCfg;
SCFG_mode sMode;
Key_Parms key;
WIFIUSE_Parms wifiuse;
RBool isDeviceOn = RFalse;
#define OFF 0
#define ON 1
#define MODE1 2
#define MODE2 3
#define MODE_MAX 4

void modeset(void)
{
    switch (sMode.curMode)
    {
    case OFF:
        led_set(LED_OFF);
        isDeviceOn = RFalse;
        MOS_OFF();
        break;
    case ON:
        led_set(LED_ON);
        isDeviceOn = RTrue;
        MOS_OFF();
        break;
    case MODE1:
        led_set(LED_BLINK2);
        isDeviceOn = RFalse;
        MOS_OFF();
        break;
    case MODE2:
        led_set(LED_BLINK3);
        isDeviceOn = RFalse;
        MOS_OFF();
        break;
    default:
        break;
    }
}

/*当按键短按时*/
void onShortPress()
{
    sMode.curMode++;
    if (sMode.curMode >= MODE_MAX)
    {
        sMode.curMode = OFF;
    }
    scfg_write(&sMode);
    modeset();
}
/*当按键长按时发生*/
void onLongPress()
{
    if (wifiuse_matchingStaticSSID_isFinished() == RFalse)
    {
        wifiuse_matchingStaticSSID_Begin();
        led_set(LED_BLINK_FOREVER);
    }
    else
    {
        wifiuse_matchingStaticSSID_End();
        led_set(LED_OFF);
    }
}

void onHamFound(char *ssid)
{
    if (sMode.curMode == MODE2)
    {
        led_set(LED_ON);
        isDeviceOn = RTrue;
        MOS_ON();
    }
}
void onHamLost()
{
    if (sMode.curMode == MODE2)
    {
        led_set(LED_OFF);
        isDeviceOn = RFalse;
        MOS_ON();
    }
}

void onLocalHamFound()
{
    if (sMode.curMode == MODE1)
    {
        led_set(LED_ON);
        isDeviceOn = RTrue;
        MOS_ON();
    }
}
void onLocalHamLost()
{
    if (sMode.curMode == MODE1)
    {
        led_set(LED_OFF);
        isDeviceOn = RFalse;
        MOS_OFF();
    }
}

void onMatchingFinished()
{
    DLOG("matching finished.");
    wifiuse_matchingStaticSSID_End();
    led_set(LED_OFF);
}

unsigned int timer10MsCnt = 0;
unsigned int timer10MsCntHis = 0;
void timerHandler(uint32_t data)
{
    timer10MsCnt++;
    key_service();
    led_service();
}
WDT wdt;
void setup()
{
    wdt.InitWatchdog(10000);
    scfg_init();
    DLOG_INIT();
    key.onShortPress = onShortPress;
    key.onLongPress = onLongPress;
    key_init(&key);
    led_init();
    MOS_INIT();
    MOS_OFF();
    wifiuse.onHAMSSIDFound = onHamFound;
    wifiuse.onHAMSSIDLost = onHamLost;
    wifiuse.onStaticHAMSSIDFound = onLocalHamFound;
    wifiuse.onStaticHAMSSIDLost = onLocalHamLost;
    wifiuse.onMatchingFinished = onMatchingFinished;
    wifiuse_init(&wifiuse);
    GTimer.begin(0, (1 * 1000 * 10), timerHandler);
    scfg_read(&sMode);
    modeset();
}

void loop()
{
    if (timer10MsCnt != timer10MsCntHis)
    {
        timer10MsCntHis = timer10MsCnt;
        wifiuse_service();
        wdt.RefreshWatchdog();
    }
}
