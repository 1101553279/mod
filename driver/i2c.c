#include "i2c.h"
#include <intrins.h>
#include <STC12C5A60S2.H>


// private function declaration 
static void I2C_Start();
static void I2C_Stop();
static void I2C_Write(unsigned char dat);
static unsigned char I2C_Read();
static bit I2C_GetAck();
static void I2C_PutAck(bit ack);

static unsigned char data I2C_Delay_t;

#define I2C_SCL  P27
#define I2C_SDA  P26

#define I2C_DELAY_VALUE  20
#define I2C_STOP_WAIT_VALUE 20

#define I2C_Delay()\
									{\
										I2C_Delay_t = (I2C_DELAY_VALUE);\
										while ( --I2C_Delay_t != 0 );\
									}
									
/* you must call the function */
void I2C_Init()
{
	P2M1 = 0xc0;
	P2M0 = 0xc0;
	
	I2C_SCL = 1;
	I2C_Delay();
	
	I2C_SDA = 1;
	I2C_Delay();
}

/* write size bytes in dat */
bit I2C_Puts(unsigned char SlaveAddr, unsigned char SubAddr, char *dat, unsigned char Size)
{
	if ( Size == 0 ) return 0;
	
	SlaveAddr &= 0xFE;
	
	I2C_Start();
	
	I2C_Write( SlaveAddr );
	if ( I2C_GetAck() )
	{
		I2C_Stop();
		return 1;
	}
	
	I2C_Write( SubAddr );
	if ( I2C_GetAck() )
	{
		I2C_Stop();
		return 1;
	}
	
	do
	{
		I2C_Write( *dat++ );
		if ( I2C_GetAck() )
		{
			I2C_Stop();
			return 1;
		}
	} while ( --Size != 0 );
	
	I2C_Stop();
 
 return 0;
}

/* put one byte to slave */
bit I2C_Put( unsigned char SlaveAddr, unsigned char SubAddr, char dat )
{
	return I2C_Puts( SlaveAddr,SubAddr, &dat, 1 );
}


/* get size data from slave */
bit I2C_Gets(unsigned char SlaveAddr, unsigned char SubAddr, unsigned char *dat, unsigned char Size )
{
	if ( Size == 0 ) 
			return 0;
	
	SlaveAddr &= 0xFE; 
	
	I2C_Start();
	
	I2C_Write(SlaveAddr);
	if ( I2C_GetAck() )
	{
		I2C_Stop();
		return 1;
	}
	
	I2C_Write(SubAddr);
	if ( I2C_GetAck() )
	{
		I2C_Stop();
		return 1;
	}
	
	I2C_Start();
	
	SlaveAddr |= 0x01;
	I2C_Write( SlaveAddr );
	
	if ( I2C_GetAck() )
	{
		I2C_Stop();
		return 1;
	}
	
	for (;;)
	{
		*dat++ = I2C_Read();
		
		if ( --Size == 0 )
		{
			I2C_PutAck( 1 );							// send noack
			break;
		}
	
		I2C_PutAck( 0 );								// send ack
	}

	I2C_Stop();
	
	return 0;
}

/* read one byte from slave */
bit I2C_Get( unsigned char SlaveAddr, unsigned char SubAddr, unsigned char *dat )
{
	return I2C_Gets( SlaveAddr, SubAddr, dat, 1 );
}





/*****************************  private function *********************/
/* 
	start 
	1. scl == 1,  sda = fall edge
	2. scl & sda == 0
*/
static void I2C_Start()
{
	EA=0;
//	I2C_SCL = 1;
//	I2C_Delay();
		
	I2C_SDA = 1;
	I2C_Delay(); 
	
	I2C_SCL = 1;					// scl put here 
	I2C_Delay();
		
	I2C_SDA = 0;  
	I2C_Delay();
		
	I2C_SCL = 0; 
	I2C_Delay();
		
	I2C_Delay();
	I2C_Delay();
}

static void I2C_Stop()
{
	unsigned int t = I2C_STOP_WAIT_VALUE;
	
	I2C_SDA = 0;  				// scl == 0,  scl must be low  when change sda value 
	I2C_Delay();
	
	I2C_SCL = 1;  
	I2C_Delay();
	
	I2C_SDA = 1; 
	I2C_Delay();
	
	EA=1;
	
	while ( --t != 0 );  
	
	return;
}

/*
	1. sda = data.bit
	2. scl pulse
*/
static void I2C_Write( unsigned char dat )
{
	unsigned char t = 0;
	
	for(t=0;t<8;t++)
	{
		I2C_SDA = (bit)(dat & 0x80);
		I2C_Delay();
		
		I2C_SCL = 1; 
		I2C_Delay();
		
		I2C_SCL = 0;   
		I2C_Delay();
		
		dat <<= 1;
	}
																	// >> scl == 0
	return;
}

static unsigned char I2C_Read()
{
	unsigned char dat = 0;
	unsigned char t = 0;
	bit temp = 0;
		
	I2C_Delay();
	I2C_Delay();
	
	I2C_SDA = 1;							// scl == 0
	I2C_Delay();
	
	for( t=0; t < 8; t++)
	{
		I2C_SCL = 0; 
		I2C_Delay();
		
		I2C_SCL = 1;
		I2C_Delay();
		
		temp = I2C_SDA;
		dat <<= 1;
		
		if (temp == 1) 
				dat |= 0x01;   
	} 
		
	I2C_SCL = 0; 
	I2C_Delay();
	
	return dat;
}	


/* 
	
*/
static bit I2C_GetAck()
{
	bit ack = 0;
	unsigned char Error_time = 255;
	
	I2C_Delay();   
	
	I2C_SDA = 1; 							// scl == 0 when sda change it's value
//		I2C_SDA = 0; 
	I2C_Delay();
	
	I2C_SCL = 1;
	I2C_Delay();
	
	do
	{  
		ack = I2C_SDA;
		Error_time--;
		
		if( Error_time == 0 )
		{
			I2C_SCL = 0;
			I2C_Delay(); 
			
			return 1;
		}
	}while( ack );  
	
	I2C_SCL = 0;  
	I2C_Delay( ); 
	
	I2C_Delay( );
	I2C_Delay( );
	
	return 0;
}


// ack = 1; noack,   ack = 0; ack
static void I2C_PutAck(bit ack)
{
	I2C_SDA = ack; 					//scl == 0
	I2C_Delay();
	
	I2C_SCL = 1;  
	I2C_Delay(); 
	
	I2C_SCL = 0; 
	I2C_Delay(); 
	
	I2C_Delay();
	I2C_Delay();
	I2C_Delay();
	
	return;
}
 













