//////////////////////////////////////////////////// ////////////
//
// Laowang Electronics Digital DIY, Taobao store https://shop154838422.taobao.com/
// Do not use commercially without permission, please do not delete this statement for personal use
//
//////////////////////////////////////////////////// ////////////
#ifndef _SOFTIO_H_
#define _SOFTIO_H_


#if defined(STM32)
#define MCU_SET_IO(pin, v) GPIO_WriteBit(pin, v);
#elif defined(C51)
#include <intrins.h>
#define MCU_SET_IO(pin, v) pin=v;
#else
#define MCU_SET_IO(pin, v) pin=v;
#endif

// LCD reset
#ifdef LCD_RST
void MCU_SET_LCD_RST(BYTE b)
{
	if (b)
	{
		MCU_SET_IO(LCD_RST, 1);
	}
	else
	{
		MCU_SET_IO(LCD_RST, 0);
	}
}
#endif


// The initial value of the delay function, if the default value is inaccurate, you need to define MCU_DELAY_MS_INIT by yourself
#ifndef MCU_DELAY_MS_INIT
	#ifndef MAIN_Fosc
		#define MAIN_Fosc 16059200UL //Macro defines main clock HZ, default 16M
	#endif
	#define MCU_DELAY_MS_INIT MAIN_Fosc / (960000 / 48)
#endif

// Built-in ms delay
void MCU_DELAY_MS(WORD wMS)
{
	WORD i;
	do
	{
#if defined(STM32)
	CLK_SysTickDelay(1000);
#else
		i = MCU_DELAY_MS_INIT;
		while (--i); //96T per loop
#endif
	}
	while (wMS--);
}


// Built-in ms delay, if the mcu frequency
void MCU_DELAY_US(WORD wUs)
{
#if defined(STM32)
	CLK_SysTickDelay(wUs);
#else
	unsigned long i = wUs * MCU_DELAY_MS_INIT / 1000;
	while (i--);
#endif
}


// Pure software IO driver IIC, SPI, P8_6800

#ifdef IIC

void IIC_DELAY()
{
#if defined(C51)
	_nop_();
	_nop_();
#else
	CLK_SysTickDelay(1);
#endif
}

void IIC_START()
{
	MCU_SET_IO(IIC_SCL, 1);		
	IIC_DELAY();
	MCU_SET_IO(IIC_SDA, 1);
	IIC_DELAY();
	MCU_SET_IO(IIC_SDA, 0);
	IIC_DELAY();
	MCU_SET_IO(IIC_SCL, 0);
	IIC_DELAY();
}

void IIC_STOP()
{
	MCU_SET_IO(IIC_SCL, 0);
	IIC_DELAY();
	MCU_SET_IO(IIC_SDA, 0);
	IIC_DELAY();
	MCU_SET_IO(IIC_SCL, 1);
	IIC_DELAY();
	MCU_SET_IO(IIC_SDA, 1);
}

void IIC_WRITE_BYTE(BYTE byDat)
{
	BYTE i;
	for(i = 0; i < 8; i++)
	{
		MCU_SET_IO(IIC_SDA, (byDat & 0x80));
		IIC_DELAY();
		MCU_SET_IO(IIC_SCL, 1);
		IIC_DELAY();
		MCU_SET_IO(IIC_SCL, 0);
		IIC_DELAY();
		byDat <<= 1;
	}
	MCU_SET_IO(IIC_SDA, 1);
	IIC_DELAY();
	MCU_SET_IO(IIC_SCL, 1);
	IIC_DELAY();
	MCU_SET_IO(IIC_SCL, 0);
	IIC_DELAY();
}


#endif

#if defined(P8_6800) || defined(P8_8080)
void P8_DELAY(unsigned char byTick)
{
	while (byTick-- > 0);
}
#endif

#ifndef LCD_IIC_ADDR 
#define LCD_IIC_ADDR 0x78
#endif

void MCU_WRITE_LCD_BYTE(BYTE byDat, BYTE bIsDat)
{
#if defined(SPI) || defined(SPI3)
	BYTE i;
#endif
#if defined(C51)
	MCU_SET_IO(EA, 0); // disable interrupt
#endif
#ifdef IIC
	IIC_START();
	IIC_WRITE_BYTE(LCD_IIC_ADDR);            //Slave address,SA0=0
	IIC_WRITE_BYTE(bIsDat ? 0x40 : 0);
	IIC_WRITE_BYTE(byDat);
	IIC_STOP();

#elif defined(P8_6800) // If RW is not defined, the actual RW should be grounded
#ifdef LCD_RW
	MCU_SET_IO(LCD_RW, 0);
#endif
	MCU_SET_IO(LCD_RS, bIsDat);
	MCU_SET_IO(LCD_CS, 0);
 	MCU_SET_IO(LCD_E, 1);
	MCU_SET_IO(LCD_DATA, byDat);
   	P8_DELAY(2);
 	MCU_SET_IO(LCD_E, 0);
	MCU_SET_IO(LCD_CS, 1);
#elif defined(P8_8080) // If RD is not defined, the actual RD should be connected to VDD
#ifdef LCD_RD
	MCU_SET_IO(LCD_RD, 1);
#endif
	MCU_SET_IO(LCD_RS, bIsDat);
	MCU_SET_IO(LCD_CS, 0);
 	MCU_SET_IO(LCD_WR, 0);
	MCU_SET_IO(LCD_DATA, byDat);
   	//P8_DELAY(2);
 	MCU_SET_IO(LCD_WR, 1);
	MCU_SET_IO(LCD_CS, 1);
#elif defined(SPI3)
	MCU_SET_IO(LCD_CS, 0);
	MCU_SET_IO(SPI_SCK, 0);
	MCU_SET_IO(SPI_SDA, bIsDat);
	MCU_SET_IO(SPI_SCK, 1);  
	for (i = 0; i < 8; i++)
	{
		MCU_SET_IO(SPI_SCK, 0);
		MCU_SET_IO(SPI_SDA, byDat & 0x80);
		MCU_SET_IO(SPI_SCK, 1);            
		byDat <<= 1;
	}
	MCU_SET_IO(LCD_CS, 1);
#elif defined(SPI)
	MCU_SET_IO(SPI_DC, bIsDat);  
	MCU_SET_IO(LCD_CS, 0);
	MCU_SET_IO(SPI_SCK, 1);
	for (i = 0; i < 8; i++)
	{
		MCU_SET_IO(SPI_SCK, 0);
		MCU_SET_IO(SPI_SDA, byDat & 0x80);
		MCU_SET_IO(SPI_SCK, 1);            
		byDat <<= 1;
	}
	MCU_SET_IO(LCD_CS, 1);
#endif
#if defined(C51)
	MCU_SET_IO(EA, 1); // resume interrupt
#endif
}


void MCU_WRITE_LCD_CMD(BYTE cmd)
{
	MCU_WRITE_LCD_BYTE(cmd, 0);
}

void MCU_WRITE_LCD_CMD_A(BYTE cmd, BYTE arg)
{
	MCU_WRITE_LCD_BYTE(cmd, 0);
	MCU_WRITE_LCD_BYTE(arg, 0);
}

void MCU_WRITE_LCD_CMD_AA(BYTE cmd, BYTE arg1, BYTE arg2)
{
	MCU_WRITE_LCD_BYTE(cmd, 0);
	MCU_WRITE_LCD_BYTE(arg1, 0);
	MCU_WRITE_LCD_BYTE(arg2, 0);
}
void MCU_WRITE_LCD_CMD_D(BYTE cmd, BYTE arg)
{
	MCU_WRITE_LCD_BYTE(cmd, 0);
	MCU_WRITE_LCD_BYTE(arg, 1);
}

void MCU_WRITE_LCD_CMD_DD(BYTE cmd, BYTE arg1, BYTE arg2)
{
	MCU_WRITE_LCD_BYTE(cmd, 0);
	MCU_WRITE_LCD_BYTE(arg1, 1);
	MCU_WRITE_LCD_BYTE(arg2, 1);
}

void MCU_WRITE_LCD_DAT8(BYTE dat)        
{
	MCU_WRITE_LCD_BYTE(dat, 1);
}

void MCU_WRITE_LCD_DAT16(WORD dat)
{
	MCU_WRITE_LCD_BYTE(dat >> 8, 1);
	MCU_WRITE_LCD_BYTE(dat, 1);
}


#endif // #ifndef _SOFTIO_H_

