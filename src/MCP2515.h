#ifndef __MCP2515_H
#define __MCP2515_H

void Delay_Nms(uint16 x);
void Exint_Init(void);
uint8 SPI_ReadByte(void);
void SPI_SendByte(uint8 dt);
void MCP2515_WriteByte(uint8 addr,uint8 dat);
uint8 MCP2515_ReadByte(uint8 addr);
void MCP2515_Reset(void);
uint32 Get_ID_For_Array(uint8 *array, uint8 offset);
void Set_Array_For_ID(uint8 *array, uint8 offset, uint32 ID, uint8 EXIDE);
uint32 Get_ID_For_Buf(uint8 buf_addr);
void Set_Buf_For_ID(uint8 buf_addr, uint32 ID, uint8 EXIDE);
void Set_Bitrate_Array(uint8 _5Kbps, uint8 *bitrate);
void Can_Init(CanCfgStruct *CanCfg);
void CAN_Send_Msg(MsgStruct *SendMsg);
void CAN_Receive_Msg(MsgStruct *SendMsg);
void Set_Cfg_From_E2(CanCfgStruct *CanCfg);
void Send_Cfg(void) ;


#endif
