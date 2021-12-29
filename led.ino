#include "def.h"
#include "led.h"
int state = LED_OFF;
int prevState = LED_OFF;
int ledOnOff = LOW;
int ledBlinkCount = 0;
int ledBlinkCountTimes = 0;
static RBool isBusy = RFalse;
void led_init(void)
{
    pinMode(LED_IO, OUTPUT);
}
void led_set(int st)
{
    state = st;
}

RBool led_isBusy(void)
{
    return isBusy;
}
void led_service(void)
{
    if(state != prevState)
    {
        isBusy = RTrue;
        ledOnOff = LOW;
        prevState = state;
    }
    switch (state)
    {
    case LED_OFF:
        ledOnOff = LOW;
        ledBlinkCount = 0;
        isBusy = RFalse;
        break;
    case LED_ON:
        ledOnOff = HIGH;
        ledBlinkCount = 0;
        isBusy = RFalse;
        break;
    case LED_BLINK2:
        ledBlinkCount++;
        if (ledBlinkCount >= 20)
        {
            ledBlinkCount = 0;
            ledOnOff = !ledOnOff;
            if (ledOnOff == LOW)
            {
                ledBlinkCountTimes++;
                if (ledBlinkCountTimes >= 2)
                {
                    ledBlinkCountTimes = 0;
                    state = LED_OFF;
                    isBusy = RFalse;
                }
            }
        }
        break;
    case LED_BLINK3:
        ledBlinkCount++;
        if (ledBlinkCount >= 20)
        {
            ledBlinkCount = 0;
            ledOnOff = !ledOnOff;
            if (ledOnOff == LOW)
            {
                ledBlinkCountTimes++;
                if (ledBlinkCountTimes >= 3)
                {
                    ledBlinkCountTimes = 0;
                    state = LED_OFF;
                    isBusy = RFalse;
                }
            }
        }
        break;
    case LED_BLINK4:
        ledBlinkCount++;
        if (ledBlinkCount >= 20)
        {
            ledBlinkCount = 0;
            ledOnOff = !ledOnOff;
            if (ledOnOff == LOW)
            {
                ledBlinkCountTimes++;
                if (ledBlinkCountTimes >= 4)
                {
                    ledBlinkCountTimes = 0;
                    state = LED_OFF;
                    isBusy = RFalse;
                }
            }
        }
        break;
    case LED_BLINK_FOREVER:
        ledBlinkCount++;
        if (ledBlinkCount >= 20)
        {
            ledBlinkCount = 0;
            ledOnOff = !ledOnOff;
        }
        isBusy = RFalse;
        break;
    default:
        isBusy = RFalse;
        break;
    }
    digitalWrite(LED_IO,ledOnOff);
}