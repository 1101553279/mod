#ifndef __I2C_H__
#define __I2C_H__
#include <STC12C5A60S2.H>
#include <intrins.h>



// external function declaration 
void I2C_Init();
bit I2C_Puts(unsigned char SlaveAddr, unsigned char SubAddr, char *dat, unsigned char Size);
bit I2C_Put(unsigned char SlaveAddr, unsigned char SubAddr, char dat);
bit I2C_Gets(unsigned char SlaveAddr, unsigned char SubAddr, unsigned char *dat, unsigned char Size );
bit I2C_Get(unsigned char SlaveAddr, unsigned char SubAddr, unsigned char *dat);


#endif