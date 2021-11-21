#ifndef __I2C_ROM_H
#define __I2C_ROM_H

void I2CStart();
void I2CStop();
bool I2CWrite(uint8 dat);
uint8 I2CReadNAK();
uint8 I2CReadACK();
void E2Read(uint8 *buf, uint8 addr, uint8 len);
void E2Write(uint8 *buf, uint8 addr, uint8 len);

#endif