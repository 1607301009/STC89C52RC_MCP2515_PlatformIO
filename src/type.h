#ifndef __TYPE_H
#define __TYPE_H

typedef __bit bool;             // 位变量
typedef unsigned char uint8;    // 无符号8位整型变量
typedef unsigned int uint16;    // 无符号16位整型变量
typedef unsigned long uint32;   // 无符号32位整型变量


// p21 RTR 远程发送标志位
typedef struct      // reveive 结构体
{
    uint32 ID;      // 帧ID
    uint8 FILHIT:3;      // 验收滤波器命中位，
    uint8 RTR:1;      // 远程帧标志位 p21
    uint8 LEVEL:2;      // 发送优先级 p18
    uint8 TYPE:2;   // 帧类型: 数据帧， 远程帧， 错误帧， 过载帧
    uint8 IsSend:1; // 帧类型: 数据帧， 远程帧， 错误帧， 过载帧
    uint8 EXIDE:1;  // 帧格式: 标准帧， 扩展帧

    uint8  DLC:4;   // 数据长度码位 <3:0> 表明接收到的数据字节个数

    uint8  DATA[8]; // 接收缓冲器 n 数据字段字节 m, 这 8 个字节包含接收报文的数据信息
} MsgStruct;

// BFPCTRL——RXnBF 引脚控制寄存器和状态寄存器 （地址：0Ch） p29 未设置配置文件
// EFLG——错误标志寄存器 （地址：2Dh） p47 未设置配置文件
typedef struct        // reveive 结构体
{
    uint8 _5Kbps;           // 比特率数，单位: 5Kbps
    uint8 bitrate[5];       // 比特率数组

    uint32 RXM0ID;       // 屏蔽器默认完全屏蔽
    uint32 RXF0ID;       // 滤波器0H
    uint32 RXF1ID;       // 滤波器1H

    uint32 RXM1ID;       // 屏蔽器默认完全屏蔽
    uint32 RXF2ID;       // 滤波器2H
    uint32 RXF3ID;       // 滤波器3H
    uint32 RXF4ID;       // 滤波器4H
    uint32 RXF5ID;       // 滤波器5H

    uint8 CANINTE_enable;     // 中断使能位，p50
    uint8 CANINTF_enable;     // 中断标志位，p51

    uint8 RXB0RXM:2;        // 接收缓冲器0工作模式位 11 = 关闭屏蔽／滤波功能；接收所有报文
    //  p27              10 = 只接收符合滤波器条件的带有扩展标识符的有效报文
    //                   01 = 只接收符合滤波器条件的带有标准标识符的有效报文
    //                   00 = 接收符合滤波器条件的所有带扩展标识符或标准标识符的有效报文
    uint8 RXB1RXM:2;        // 接收缓冲器1工作模式位

    uint8 CAN_MODE:3;       // 工作模式： 1. 配置模式。
    //          2. 正常模式。
    //          3. 休眠模式。
    //          4. 仅监听模式。
    //          5. 环回模式。

    uint8 BUKT_enable:1;    // 接收缓冲器0滚存1 使能位

    uint8 RXF0IDE:1;     // 滤波器RXF0扩展帧标志位
    uint8 RXF1IDE:1;     // 滤波器RXF1扩展帧标志位
    uint8 RXF2IDE:1;     // 滤波器RXF2扩展帧标志位
    uint8 RXF3IDE:1;     // 滤波器RXF3扩展帧标志位
    uint8 RXF4IDE:1;     // 滤波器RXF4扩展帧标志位
    uint8 RXF5IDE:1;     // 滤波器RXF5扩展帧标志位
} CanCfgStruct;


#endif