//////////////////////////////////////////////////////////////
//
// 老王电子数码DIY，淘宝店 https://shop154838422.taobao.com/
// 未经许可勿商业使用，个人使用请勿删除此声明
//
//////////////////////////////////////////////////////////////
#ifndef _ST7789_H_
#define _ST7789_H_

//设置横屏或者竖屏显示 0或1为竖屏 2或3为横屏
#ifndef USE_HORIZONTAL
#define USE_HORIZONTAL 0
#endif

// 彩屏，16位色
#define LCD_COLOR_BITS 16

// LCD宽
#ifndef X_WIDTH
#define X_WIDTH 240
#endif

// LCD高
#ifndef Y_WIDTH
#define Y_WIDTH 240
#endif

// x方向显示偏移
#ifndef COL_OFFSET
#define COL_OFFSET 0
#endif

// y方向显示偏移
#ifndef ROW_OFFSET
#define ROW_OFFSET 0
#endif


// 初始化芯片
void LCD_IC_INIT(void)
{
#ifdef LCD_RST
	// 控制rst，确保ic复位
	MCU_SET_LCD_RST(1);
	MCU_DELAY_MS(100);
	MCU_SET_LCD_RST(0);
	MCU_DELAY_MS(100);
	MCU_SET_LCD_RST(1);
	MCU_DELAY_MS(100);
#endif
	MCU_WRITE_LCD_CMD(0x11);     //Sleep out
	MCU_DELAY_MS(120);                //Delay 120ms


	MCU_WRITE_LCD_CMD(0x36);
#ifdef LCD_REVERT_RGB
	#define RGB_REVERT_MASK 0x08
#else
	#define RGB_REVERT_MASK 0
#endif

#if defined(LCD_REVERT_X) // 镜像反转
	if(USE_HORIZONTAL==0)MCU_WRITE_LCD_DAT8(0x40 | RGB_REVERT_MASK);
	else if(USE_HORIZONTAL==1)MCU_WRITE_LCD_DAT8(0x80 | RGB_REVERT_MASK);
	else if(USE_HORIZONTAL==2)MCU_WRITE_LCD_DAT8(0xF0 | RGB_REVERT_MASK);
	else MCU_WRITE_LCD_DAT8(0x20 | RGB_REVERT_MASK);
#else 
	if(USE_HORIZONTAL==0)MCU_WRITE_LCD_DAT8(RGB_REVERT_MASK);
	else if(USE_HORIZONTAL==1)MCU_WRITE_LCD_DAT8(0xC0 | RGB_REVERT_MASK);
	else if(USE_HORIZONTAL==2)MCU_WRITE_LCD_DAT8(0x70 | RGB_REVERT_MASK);
	else MCU_WRITE_LCD_DAT8(0xA0 | RGB_REVERT_MASK);
#endif
		
	MCU_WRITE_LCD_CMD(0x3A);     
	MCU_WRITE_LCD_DAT8(0x05); // 5-6-5 16bit模式，0x06-->6-6-6 18bit模式   

	MCU_WRITE_LCD_CMD(0xB2);     
	MCU_WRITE_LCD_DAT8(0x1F);   
	MCU_WRITE_LCD_DAT8(0x1F);   
	MCU_WRITE_LCD_DAT8(0x00);   
	MCU_WRITE_LCD_DAT8(0x33);   
	MCU_WRITE_LCD_DAT8(0x33);   

	MCU_WRITE_LCD_CMD(0xB7);     
	MCU_WRITE_LCD_DAT8(0x35);   

	MCU_WRITE_LCD_CMD(0xBB);     
	MCU_WRITE_LCD_DAT8(0x2B);   //2b

	MCU_WRITE_LCD_CMD(0xC0);     
	MCU_WRITE_LCD_DAT8(0x2C);   

	MCU_WRITE_LCD_CMD(0xC2);     
	MCU_WRITE_LCD_DAT8(0x01);   

	MCU_WRITE_LCD_CMD(0xC3);     
	MCU_WRITE_LCD_DAT8(0x0F);   

	MCU_WRITE_LCD_CMD(0xC4);     
	MCU_WRITE_LCD_DAT8(0x20);   //VDV, 0x20:0v

	MCU_WRITE_LCD_CMD(0xC6);     
	MCU_WRITE_LCD_DAT8(0x13);   //0x13:60Hz   

	MCU_WRITE_LCD_CMD(0xD0);     
	MCU_WRITE_LCD_DAT8(0xA4);   
	MCU_WRITE_LCD_DAT8(0xA1);   

	MCU_WRITE_LCD_CMD(0xD6);     
	MCU_WRITE_LCD_DAT8(0xA1);   //sleep in后，gate输出为GND

	MCU_WRITE_LCD_CMD(0xE0);     
	MCU_WRITE_LCD_DAT8(0xF0);   
	MCU_WRITE_LCD_DAT8(0x04);   
	MCU_WRITE_LCD_DAT8(0x07);   
	MCU_WRITE_LCD_DAT8(0x04);   
	MCU_WRITE_LCD_DAT8(0x04);   
	MCU_WRITE_LCD_DAT8(0x04);   
	MCU_WRITE_LCD_DAT8(0x25);   
	MCU_WRITE_LCD_DAT8(0x33);   
	MCU_WRITE_LCD_DAT8(0x3C);   
	MCU_WRITE_LCD_DAT8(0x36);   
	MCU_WRITE_LCD_DAT8(0x14);   
	MCU_WRITE_LCD_DAT8(0x12);   
	MCU_WRITE_LCD_DAT8(0x29);   
	MCU_WRITE_LCD_DAT8(0x30);   

	MCU_WRITE_LCD_CMD(0xE1);     
	MCU_WRITE_LCD_DAT8(0xF0);   
	MCU_WRITE_LCD_DAT8(0x02);   
	MCU_WRITE_LCD_DAT8(0x04);   
	MCU_WRITE_LCD_DAT8(0x05);   
	MCU_WRITE_LCD_DAT8(0x05);   
	MCU_WRITE_LCD_DAT8(0x21);   
	MCU_WRITE_LCD_DAT8(0x25);   
	MCU_WRITE_LCD_DAT8(0x32);   
	MCU_WRITE_LCD_DAT8(0x3B);   
	MCU_WRITE_LCD_DAT8(0x38);   
	MCU_WRITE_LCD_DAT8(0x12);   
	MCU_WRITE_LCD_DAT8(0x14);   
	MCU_WRITE_LCD_DAT8(0x27);   
	MCU_WRITE_LCD_DAT8(0x31);   
 

#ifdef LCD_DISPLAY_INVERSION   
	MCU_WRITE_LCD_CMD(0x21);     //Display inversion
#else
	MCU_WRITE_LCD_CMD(0x20);
#endif
	MCU_WRITE_LCD_CMD(0x29);     //Display on
}
            

// 窗口模式地址，可以精确到每个点
BYTE LCD_SET_WINDOW(WORD x1, WORD y1, WORD x2, WORD y2)
{
    if ((x1 >= X_WIDTH) || (y1 >= Y_WIDTH)) // 超出显示区域，不画
	{
        return 0;
	}
	if (x2 > X_WIDTH) // 部分超出显示区域，	 不画超出部分
	{
		x2 = X_WIDTH;
	}
	if (y2 > Y_WIDTH)
	{
		y2 = Y_WIDTH;
	}
	x1 += COL_OFFSET;
	x2 += COL_OFFSET;
	y1 += ROW_OFFSET;
	y2 += ROW_OFFSET;

	if(USE_HORIZONTAL <= 1) // 竖屏
	{
		MCU_WRITE_LCD_CMD(0x2a);//列地址设置
		MCU_WRITE_LCD_DAT16(x1);
		MCU_WRITE_LCD_DAT16(x2);
		MCU_WRITE_LCD_CMD(0x2b);//行地址设置
		MCU_WRITE_LCD_DAT16(y1);
		MCU_WRITE_LCD_DAT16(y2);
	}
	else // 横屏
	{
		MCU_WRITE_LCD_CMD(0x2a);//列地址设置
		MCU_WRITE_LCD_DAT16(x1);
		MCU_WRITE_LCD_DAT16(x2);
		MCU_WRITE_LCD_CMD(0x2b);//行地址设置
		MCU_WRITE_LCD_DAT16(y1);
		MCU_WRITE_LCD_DAT16(y2);
	}
	MCU_WRITE_LCD_CMD(0x2c);//储存器写(并设置xy到windows起始位置)
	// 0x3c 继续写基于当前xy位置，超出windows结束位置忽略

	return 1;
}



#endif // #ifndef _ST7789_H_


