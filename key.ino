#include "def.h"
#include "key.h"
static unsigned int keyDownCount = 0;
static int IOCurState = HIGH;
static int IOHisState = HIGH;
static RBool beginFlag = RFalse;
static Key_Parms *keyPrms;

void key_init(Key_Parms *parms)
{
    DLOG_WRITE("KEY:init...");
    keyPrms = parms;
    pinMode(KEY_IO, INPUT);
    DLOG("finished");
}

void key_service(void)
{
    IOCurState = digitalRead(KEY_IO);
    if (IOCurState != IOHisState)
    {
        if (IOCurState == 0)
        {
            beginFlag = RTrue;
        }
        IOHisState = IOCurState;
    }
    if (beginFlag == RTrue && IOCurState == 0)
    {
        keyDownCount++;
        if(keyDownCount > 200)
        {
            keyDownCount = 0;
            beginFlag = RFalse;
            DLOG("KEY: long press.");
            keyPrms->onLongPress();
        }
    }
    else
    {
        if (beginFlag == RTrue)
        {
            if (keyDownCount > 3)
            {
                DLOG("KEY: short press.");
                keyPrms->onShortPress();
            }
            beginFlag = RFalse;
        }
        keyDownCount = 0;
    }
}