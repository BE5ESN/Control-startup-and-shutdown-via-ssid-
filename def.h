#ifndef __DEF_H__
#define __DEF_H__

#define RTrue 1
#define RFalse 0
typedef char RBool;


#define MOS_SW 2
#define KEY_IO 8
#define LED_IO 9

#define SERIAL_LOG 1


/*打印宏*/
#if SERIAL_LOG 
#define DLOG_INIT() Serial1.begin(115200)
#define DLOG(v) Serial1.println(v)
#define DLOG_WRITE(v) Serial1.write(v)
#define DLOG_PRINT(v) Serial1.print(v)
#else
#define DLOG_INIT() 
#define DLOG(v) 
#define DLOG_WRITE(v)
#define DLOG_PRINT(v)
#endif

/*简单宏函数定义在这里*/
#define MOS_INIT() pinMode(MOS_SW, OUTPUT)
#define MOS_ON() digitalWrite(MOS_SW,HIGH)
#define MOS_OFF() digitalWrite(MOS_SW,LOW)
#endif