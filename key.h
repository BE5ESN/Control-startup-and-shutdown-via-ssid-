#ifndef __KEY_H__
#define __KEY_H__

typedef struct 
{
    void (*onShortPress)(void);
    void (*onLongPress)(void);
}Key_Parms;

//放在setup
//传参请保证该parms为静态变量，避免
void key_init(Key_Parms *parms);
//按键函数放在10ms中循环运行
void key_service(void);

#endif