
Mainly used in cars(FOR HAM).

Some cars have onboard WIFI. Some of our equipment is connected to the car battery. In order to solve the power-off and power-on problems of the battery equipment, a power-off and power-on module based on the ESP chip is designed here. When the WIFI SSID in the car is detected, the device will be powered on. If the SSID disappears, the device is powered off. (Note that the SSID should end with _HAM)

    There are two modes
    1. Normally open normally closed mode
    2. Detect WIFI mode
    (Detecting WIFI only detects SSID and does not need to be connected)

    The mode of operation is to switch between different modes with a single short press of the button.
    Press the key to cycle mode.
    Mode 1. The light is always on, which means it is turned on.
    Mode 2. The light is off, which means it is off.
    Mode 3. The light flashes twice, which means it enters the WIFI detection mode. When the specified WIFI is scanned, the power will be turned on.

    Mode 4. The light flashes 3 times, which means it enters the WIFI detection mode. This mode is the same as the above mode. The difference is that any WIFI ending with "_HAM" will turn on the power.

    After a long press, the device will detect WIFI and record the SSID ending with "_HAM". At this time, the device will start flashing until it is detected and stored in the record, and it will automatically exit after detection.

    Long press again to exit the detection mode.

    This project is completely open source, and the APRS function is not currently implemented. If you have the ability, you can integrate the APRS function on this module. All the pins have been drawn on the PCBA.
    More interesting functions look forward to your development.
    In order to avoid frequent network detection, the detection interval is set to 15 seconds, and the detection itself will take about 5 seconds.

    PCBA view
    https://oshwhub.com/xifengzui/self-product-qi-ju-duan-dian-jian-ce 

主要用在汽车上(给业余无线电的朋友们)。

一些汽车带有车载WIFI。我们有些设备接在汽车电瓶上，为了解决电瓶设备的断电与上电问题，这里设计了一个基于ESP芯片的断电与上电模块。当检测到车子里的WIFI SSID的时候，设备将被上电。SSID消失，则设备断电。(注意SSID要以_HAM结尾)

    共有两种模式
    0.常开常关模式
    1.检测WIFI模式
    (检测WIFI仅检测SSID，并不需要连接)

    操作方式为，按键单次短按，在不同模式下切换。
    按键将循环模式。
    模式1.灯常亮，代表开启。
    模式2.灯熄灭，代表关闭。
    模式3.灯闪烁2次，代表进入WIFI检测模式，当扫描到指定WIFI后，将打开电源。

    模式4.灯闪烁3次，代表进入WIFI检测模式，该模式和上面模式相同，不同的是他发现任何带"_HAM"结尾的WIFI都会打开电源。

    长按后设备将检测WIFI并记录带有"_HAM"结尾的SSID,此时设备开始闪烁，直至检测到并存储在记录中，检测到后自动退出。

    再次长按退出检测模式。

    本项目完全开源，目前没有实现APRS功能，如果您有能力，完全可以在该模块上集成APRS功能，在PCBA上已经引出了所有引脚。
    更多有意思的功能期待您的开发。
    为了避免频繁网络检测，检测间隔设置为15秒，而检测本身会需要5秒左右。

    PCBA查看 
    https://oshwhub.com/xifengzui/self-product-qi-ju-duan-dian-jian-ce
