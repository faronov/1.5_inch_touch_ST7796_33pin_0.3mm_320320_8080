//////////////////////////////////////////////////// ////////////
//
// Laowang Electronics Digital DIY, Taobao store https://shop154838422.taobao.com/
// Do not use commercially without permission, please do not delete this statement for personal use
//
//////////////////////////////////////////////////// ////////////
#ifndef _ST7789_H_
#define _ST7789_H_

//Set horizontal screen or vertical screen display, 0 or 1 is vertical screen, 2 or 3 is horizontal screen
#ifndef USE_HORIZONTAL
#define USE_HORIZONTAL 0
#endif

// Color screen, 16-bit color
#define LCD_COLOR_BITS 16

// LCD width
#ifndef X_WIDTH
#define X_WIDTH 240
#endif

// LCD high
#ifndef Y_WIDTH
#define Y_WIDTH 240
#endif

// display offset in x direction
#ifndef COL_OFFSET
#define COL_OFFSET 0
#endif

// display offset in y direction
#ifndef ROW_OFFSET
#define ROW_OFFSET 0
#endif


// Initialize the chip
void LCD_IC_INIT(void)
{
#ifdef LCD_RST
	// Control rst to ensure ic is reset
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

#if defined(LCD_REVERT_X) // mirror reverse
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
	MCU_WRITE_LCD_DAT8(0x05); // 5-6-5 16bit mode, 0x06-->6-6-6 18bit mode 

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
	MCU_WRITE_LCD_DAT8(0xA1);   //After sleep in, the gate output is GND

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
            

// Window mode address, accurate to each point
BYTE LCD_SET_WINDOW(WORD x1, WORD y1, WORD x2, WORD y2)
{
    if ((x1 >= X_WIDTH) || (y1 >= Y_WIDTH)) // beyond the display area, do not draw
	{
        return 0;
	}
	if (x2 > X_WIDTH) // part exceeds the display area, do not draw the excess part
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

	if(USE_HORIZONTAL <= 1) // vertical screen
	{
		MCU_WRITE_LCD_CMD(0x2a);//column address setting
		MCU_WRITE_LCD_DAT16(x1);
		MCU_WRITE_LCD_DAT16(x2);
		MCU_WRITE_LCD_CMD(0x2b);//row address setting
		MCU_WRITE_LCD_DAT16(y1);
		MCU_WRITE_LCD_DAT16(y2);
	}
	else // horizontal screen
	{
		MCU_WRITE_LCD_CMD(0x2a);//column address setting
		MCU_WRITE_LCD_DAT16(x1);
		MCU_WRITE_LCD_DAT16(x2);
		MCU_WRITE_LCD_CMD(0x2b);//row address setting
		MCU_WRITE_LCD_DAT16(y1);
		MCU_WRITE_LCD_DAT16(y2);
	}
	MCU_WRITE_LCD_CMD(0x2c); //Memory write (and set xy to windows start position)
// 0x3c Continue to write based on the current xy position, beyond the end position of windows is ignored

	return 1;
}



#endif // #ifndef _ST7789_H_


