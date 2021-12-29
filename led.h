#ifndef __LED_H__
#define __LED_H__

#define LED_OFF 0
#define LED_ON 1
#define LED_BLINK2 2
#define LED_BLINK3 3
#define LED_BLINK4 4
#define LED_BLINK_FOREVER 5
#define LED_MAX 6

void led_init(void);
void led_set(int st);
void led_service(void);
#endif