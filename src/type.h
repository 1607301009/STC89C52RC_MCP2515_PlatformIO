#ifndef __TYPE_H
#define __TYPE_H

typedef __bit bool;             // λ����
typedef unsigned char uint8;    // �޷���8λ���ͱ���
typedef unsigned int uint16;    // �޷���16λ���ͱ���
typedef unsigned long uint32;   // �޷���32λ���ͱ���


// p21 RTR Զ�̷��ͱ�־λ
typedef struct      // reveive �ṹ��
{
    uint32 ID;      // ֡ID
    uint8 FILHIT:3;      // �����˲�������λ��
    uint8 RTR:1;      // Զ��֡��־λ p21
    uint8 LEVEL:2;      // �������ȼ� p18
    uint8 TYPE:2;   // ֡����: ����֡�� Զ��֡�� ����֡�� ����֡
    uint8 IsSend:1; // ֡����: ����֡�� Զ��֡�� ����֡�� ����֡
    uint8 EXIDE:1;  // ֡��ʽ: ��׼֡�� ��չ֡

    uint8  DLC:4;   // ���ݳ�����λ <3:0> �������յ��������ֽڸ���

    uint8  DATA[8]; // ���ջ����� n �����ֶ��ֽ� m, �� 8 ���ֽڰ������ձ��ĵ�������Ϣ
} MsgStruct;

// BFPCTRL����RXnBF ���ſ��ƼĴ�����״̬�Ĵ��� ����ַ��0Ch�� p29 δ���������ļ�
// EFLG���������־�Ĵ��� ����ַ��2Dh�� p47 δ���������ļ�
typedef struct        // reveive �ṹ��
{
    uint8 _5Kbps;           // ������������λ: 5Kbps
    uint8 bitrate[5];       // ����������

    uint32 RXM0ID;       // ������Ĭ����ȫ����
    uint32 RXF0ID;       // �˲���0H
    uint32 RXF1ID;       // �˲���1H

    uint32 RXM1ID;       // ������Ĭ����ȫ����
    uint32 RXF2ID;       // �˲���2H
    uint32 RXF3ID;       // �˲���3H
    uint32 RXF4ID;       // �˲���4H
    uint32 RXF5ID;       // �˲���5H

    uint8 CANINTE_enable;     // �ж�ʹ��λ��p50
    uint8 CANINTF_enable;     // �жϱ�־λ��p51

    uint8 RXB0RXM:2;        // ���ջ�����0����ģʽλ 11 = �ر����Σ��˲����ܣ��������б���
    //  p27              10 = ֻ���շ����˲��������Ĵ�����չ��ʶ������Ч����
    //                   01 = ֻ���շ����˲��������Ĵ��б�׼��ʶ������Ч����
    //                   00 = ���շ����˲������������д���չ��ʶ�����׼��ʶ������Ч����
    uint8 RXB1RXM:2;        // ���ջ�����1����ģʽλ

    uint8 CAN_MODE:3;       // ����ģʽ�� 1. ����ģʽ��
    //          2. ����ģʽ��
    //          3. ����ģʽ��
    //          4. ������ģʽ��
    //          5. ����ģʽ��

    uint8 BUKT_enable:1;    // ���ջ�����0����1 ʹ��λ

    uint8 RXF0IDE:1;     // �˲���RXF0��չ֡��־λ
    uint8 RXF1IDE:1;     // �˲���RXF1��չ֡��־λ
    uint8 RXF2IDE:1;     // �˲���RXF2��չ֡��־λ
    uint8 RXF3IDE:1;     // �˲���RXF3��չ֡��־λ
    uint8 RXF4IDE:1;     // �˲���RXF4��չ֡��־λ
    uint8 RXF5IDE:1;     // �˲���RXF5��չ֡��־λ
} CanCfgStruct;


#endif