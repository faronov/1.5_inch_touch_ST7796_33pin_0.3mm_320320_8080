//////////////////////////////////////////////////// ////////////
//
// Laowang Electronics Digital DIY, Taobao store https://shop154838422.taobao.com/
// Do not use commercially without permission, please do not delete this statement for personal use
//
//////////////////////////////////////////////////// ////////////
#ifndef _GUI_H_
#define _GUI_H_
// implement the drawing function
#include <stdio.h>

typedef const char* PCSTR;
typedef const unsigned char* PCBYTE;



// undefined color, default monochrome
#if !defined(LCD_COLOR_BITS) || LCD_COLOR_BITS==0
	#define LCD_COLOR_BITS 1
#endif

#if LCD_COLOR_BITS < 1
	#undef LCD_COLOR_BITS
	#define LCD_COLOR_BITS 1
#endif

#if LCD_COLOR_BITS <= 1
	#define PT_PER_BYTE 8
	#define LCD_COLOR_MASK 0x1

	// black and white dot matrix
	#define LCD_WHITE         	 0x1
	#define LCD_BLACK         	 0x0	  
	#define LCD_GRAY  			 0x1
	#define LCD_BROWN 			 0x1
	
	#define LCD_RED           	 0x1
	#define LCD_ORANGE           	 0x1
	#define LCD_YELLOW        	 0x1
	#define LCD_GREEN         	 0x1
	#define LCD_CYAN          	 0x1
	#define LCD_BLUE           	 0x1
	#define LCD_PURPLE             0x1

#elif LCD_COLOR_BITS <= 2
	#define PT_PER_BYTE 4
	#define LCD_COLOR_MASK 0x3
	// 4 gray levels
	#define LCD_WHITE         	 0x3
	#define LCD_BLACK         	 0x0	  
	#define LCD_GRAY  			 0x1
	#define LCD_BROWN 			 0x1
	
	#define LCD_RED           	 0x1
	#define LCD_ORANGE           	 0x2
	#define LCD_YELLOW        	 0x2
	#define LCD_GREEN         	 0x2
	#define LCD_CYAN          	 0x2
	#define LCD_BLUE           	 0x1
	#define LCD_PURPLE             0x2

#elif LCD_COLOR_BITS <= 4
	#define PT_PER_BYTE 2
	#define LCD_COLOR_MASK 0xF

	// 16 colors (1R2G1B)/16 grayscale
	#if defined(LCD_COLOR_GRAY) || defined(LCD_RGB_2_GRAY)
		#define LCD_WHITE         	 0xF
		#define LCD_BLACK         	 0x0	  
		#define LCD_GRAY  			 0x7
		#define LCD_BROWN 			 0x2
		
		#define LCD_RED           	 0x1
		#define LCD_ORANGE           	 0xA
		#define LCD_YELLOW        	 0xD
		#define LCD_GREEN         	 0x4
		#define LCD_CYAN          	 0x5
		#define LCD_BLUE           	 0x3
		#define LCD_PURPLE             0x8
	#else
		#define LCD_WHITE         	 0xF
		#define LCD_BLACK         	 0x0	  
		#define LCD_GRAY  			 0x7
		#define LCD_BROWN 			 0x7
		
		#define LCD_RED           	 0x8
		#define LCD_ORANGE           	 0xA
		#define LCD_YELLOW        	 0xE
		#define LCD_GREEN         	 0x6
		#define LCD_CYAN          	 0x5
		#define LCD_BLUE           	 0x1
		#define LCD_PURPLE             0x9
	#endif

#elif LCD_COLOR_BITS <= 8
	#define PT_PER_BYTE 1
	#define LCD_COLOR_MASK 0xFF

	// 256 colors (2R3G2B)
	#define LCD_WHITE         	 0xFF
	#define LCD_BLACK         	 0x00	  
	#define LCD_GRAY  			 0x4A
	#define LCD_BROWN 			 0x50
	
	#define LCD_RED           	 0x60
	#define LCD_ORANGE           	 0x68
	#define LCD_YELLOW        	 0x7C
	#define LCD_GREEN         	 0x1C
	#define LCD_CYAN          	 0x3F
	#define LCD_BLUE           	 0x03
	#define LCD_PURPLE             0x22

#else
	#define PT_PER_BYTE 1
	#define LCD_COLOR_MASK 0xFFFF

	// 16-bit color (5R6G5B)
	#define LCD_WHITE         	 0xFFFF
	#define LCD_BLACK         	 0x0000	  
	#define LCD_GRAY  			 0X8430
	#define LCD_BROWN 			 0XBC40
	
	#define LCD_RED           	 0xF800
	#define LCD_ORANGE           	 0xFA20
	#define LCD_YELLOW        	 0xFFE0
	#define LCD_GREEN         	 0x07E0
	#define LCD_CYAN          	 0x7FFF
	#define LCD_BLUE           	 0x001F
	#define LCD_PURPLE             0X8010

#endif


// Set bitmap fonts, injected by user code, to avoid built-in fonts taking up too much space
typedef struct tagLCD_FONT
{
	BYTE byCharWidth; // Single character font width
	BYTE byCharHeight; // Single character font height
	BYTE byIndexWChar; // Wide character or not, Chinese character 1 ascii 0
	BYTE byCanQuickSearch; // The index has been sorted from small to large, allowing quick search, if it is not sorted, it may not be found
	BYTE byCharFontBytes; // The memory size of each character of the font

	short shIndexSize; // The number of index characters, note that it is not the number of bytes, Chinese characters are pIndex bytes/2
	PCSTR pIndex; // Character index string, which needs to be sorted in alphabetical order, so that it is easy to find characters quickly
	PCBYTE pFontData; // Dot matrix screen format, from left to right, from top to bottom, each 1 byte is 8 rows and 1 column
} LCD_FONT;

// Internal cache data
typedef struct tagLCD_CURRENT
{
	WORD wTextColor;
	WORD wBackColor;

	WORD wXPos;
	WORD wYPos;

	const LCD_FONT *pFontAscii;
	const LCD_FONT *pFontGB;
} LCD_CURRENT;


LCD_CURRENT lcd = 
{
	LCD_RED & LCD_COLOR_MASK,	LCD_BLACK & LCD_COLOR_MASK,	// default font color

	0, 0
};

void lcd_SetAsciiFont(const LCD_FONT *pFont)
{
	lcd.pFontAscii = pFont;
}

void lcd_SetGBFont(const LCD_FONT *pFont)
{
	lcd.pFontGB = pFont;
}

void lcd_SetTextColor(WORD wTextColor)
{
	lcd.wTextColor = wTextColor & LCD_COLOR_MASK;
}

void lcd_SetBackColor(WORD wBackColor)
{
	lcd.wBackColor = wBackColor & LCD_COLOR_MASK;
}

void lcd_SetPos(WORD wX, WORD wY)
{
	lcd.wXPos = wX;
	lcd.wYPos = wY;
}

// Automatically adapt to X increase to adapt to special screen
void LCD_POS_X_ADD(BYTE b)
{
	lcd.wXPos += b;
}

  

void lcd_Pattern(BYTE byD1, BYTE byD2)
{
#if LCD_COLOR_BITS==1 || LCD_COLOR_BITS==2
	BYTE i, j;
	for (i = 0; i < (Y_WIDTH / 8); i++)   
	{
		LCD_SET_WINDOW(0, i << 3, X_WIDTH, (i << 3) + 7);
		for (j = 0; j < (X_WIDTH / 2);j++)
		{
		#if LCD_COLOR_BITS==1
			MCU_WRITE_LCD_DAT8(byD1);
			MCU_WRITE_LCD_DAT8(byD2);
		#else // 4 gray scales, actually one more column
			MCU_WRITE_LCD_DAT8(byD1);
			MCU_WRITE_LCD_DAT8(byD1);
			MCU_WRITE_LCD_DAT8(byD2);
			MCU_WRITE_LCD_DAT8(byD2);
		#endif
		}
	}
#else
	WORD i, j;
	BYTE b, mask;
	#if PT_PER_BYTE > 1
	BYTE k;
	#endif
	WORD tmp;
	for (i = 0; i < Y_WIDTH; i++)
	{
		mask = 1 << (i & 7); // different bitmask for this byte per line
		LCD_SET_WINDOW(0, i, X_WIDTH - 1, i);
		for (j = 0; j < X_WIDTH; )
		{
		#if PT_PER_BYTE > 1
			tmp = 0;
			for (k = 0; k++ < PT_PER_BYTE; j++) // concatenate multiple points into one BYTE
			{ 
				b = (j & 1) ? byD2 : byD1;
				tmp <<= LCD_COLOR_BITS;
				tmp += (b & mask) ? lcd.wTextColor : lcd.wBackColor;
			}
			MCU_WRITE_LCD_DAT8(tmp);
		#elif  LCD_COLOR_BITS==8 // 8bits
			b = (j++ & 1) ? byD2 : byD1;
			tmp = (b & mask) ? lcd.wTextColor : lcd.wBackColor;
			MCU_WRITE_LCD_DAT8(tmp);
		#else // 16bits
			b = (j++ & 1) ? byD2 : byD1;
			tmp = (b & mask) ? lcd.wTextColor : lcd.wBackColor;
			MCU_WRITE_LCD_DAT16(tmp);
		#endif


		}
	} 	
#endif

}


#if LCD_COLOR_BITS > 2
// display a monochrome image with a grayscale screen, to be converted
void lcd_DrawMonoPicture(PCBYTE pbyData, BYTE byWidth, BYTE byHeight)
{
	BYTE i;
	BYTE j;
#if PT_PER_BYTE > 1
	BYTE k;
#endif
	BYTE mask;
	WORD tmp;
	BYTE *p;

	// Window writing, to map every 8 rows and 1 column of a dot matrix font to write a color point per pixel
	for (i = 0; i < byHeight; i++) // display line by line
	{
		// Set the address once per line to avoid errors when the length and color bits are not aligned
		tmp = lcd.wYPos + i;
	 	if (!LCD_SET_WINDOW(lcd.wXPos, tmp, lcd.wXPos + byWidth - 1, tmp))
		{
			break;
		}

		tmp = i >> 3; // Calculate the current page number
		mask = 1 << (i & 7); // different bitmask for this byte per line
		p = &pbyData[tmp * byWidth]; // base address of image data in this row

		for (j = 0; j < byWidth; )
		{
		#if PT_PER_BYTE > 1
			tmp = 0;
			for (k = 0; k++ < PT_PER_BYTE; j++) // concatenate multiple points into one BYTE
			{ 
				tmp <<= LCD_COLOR_BITS;
				tmp += (p[j] & mask) ? lcd.wTextColor : lcd.wBackColor;
			} 
			MCU_WRITE_LCD_DAT8(tmp);
		#elif LCD_COLOR_BITS==8 // 8bits
			tmp = (p[j++] & mask) ? lcd.wTextColor : lcd.wBackColor;
			MCU_WRITE_LCD_DAT8(tmp);
		#else // 16bits
			tmp = (p[j++] & mask) ? lcd.wTextColor : lcd.wBackColor;
			MCU_WRITE_LCD_DAT16(tmp);
		#endif

		}
	}

}     

// map of pixel-by-pixel to pixel-by-pixel, no conversion required
void lcd_DrawPicture(PCBYTE pbyData, WORD wWidth, WORD wHeight)
{
	WORD i;
	WORD j;
	PCBYTE p = pbyData;
	WORD wBytesPerLine = wWidth * LCD_COLOR_BITS / 8;
	LCD_SET_WINDOW(lcd.wXPos, lcd.wYPos, lcd.wXPos + wWidth - 1, lcd.wYPos + wHeight - 1);
	for (i = 0; i < wHeight; i++)   
	{
//	 	if (!LCD_SET_WINDOW(lcd.wXPos, lcd.wYPos + i, lcd.wXPos + wWidth, lcd.wYPos + i))
//		{
//			break;
//		}
		for (j = 0; j < wBytesPerLine; j++)
		{
			MCU_WRITE_LCD_DAT8(*p++);
		}
	}
}

#else
// monochrome screen pixel monochrome image, no need to convert
void lcd_DrawMonoPicture(PCBYTE pbyData, BYTE byWidth, BYTE byHeight)
{
	BYTE i;
	BYTE j;
	PCBYTE p = pbyData;
	BYTE bRevert = (0 != lcd.wBackColor); // background is not black, reverse color
#if LCD_COLOR_BITS==2 // 4 gray levels, write 2BYTE per page, the first BYTE is for the high bit of the color, and the second BYTE is for the low bit of the color
	BYTE k;
	BYTE a;
	BYTE b;
	data BYTE aMaskText = (lcd.wTextColor & 0x02) ? 1 : 0;
	data BYTE bMaskText = (lcd.wTextColor & 0x01) ? 1 : 0;
	data BYTE aMaskBack = (lcd.wBackColor & 0x02) ? 1 : 0;
	data BYTE bMaskBack = (lcd.wBackColor & 0x01) ? 1 : 0;
#endif
	for (i = 0; i < byHeight; i += 8, p += byWidth) // display by page
	{
	 	if (!LCD_SET_WINDOW(lcd.wXPos, lcd.wYPos + i, lcd.wXPos + byWidth, lcd.wYPos + i + 7))
		{
			break;
		}
		for (j = 0; j < byWidth; j++)
		{
		#if LCD_COLOR_BITS==2 // 4 gray levels, 0 is converted to background color, 1 is converted to text color
			a = 0;
			b = 0;
			for (k = 8; k-- > 0;)
			{
				a <<= 1;
				b <<= 1;
				if (p[j] & (1 << k)) // text color
				{
					a |= aMaskText;
					b |= bMaskText;
				}
				else // background color
				{
					a |= aMaskBack;
					b |= bMaskBack;
				}
			}
			MCU_WRITE_LCD_DAT8(a);
			MCU_WRITE_LCD_DAT8(b);
		#else
			if (bRevert)
			{
				MCU_WRITE_LCD_DAT8(~(p[j]));
			}
			else
			{
				MCU_WRITE_LCD_DAT8(p[j]);
			}
		#endif //	#if LCD_COLOR_BITS==2 
		}
	}

}     
#endif  // #if LCD_COLOR_BITS > 2

void lcd_Clear()
{
	lcd_Pattern(0, 0);
}

void DRAW_CHAR(const LCD_FONT *f, BYTE a, BYTE b)
{
	// fast half search, pIndex characters are arranged from small to large
	short shFrom;
 	short shTo;
	short shIndex;
	BYTE cA;
	BYTE cB = b; // single-byte characters do not need to compare b bytes
	const char *p;
	if (NULL == f || NULL == (p = f->pIndex))
	{
		return;
	}
	shTo = f->shIndexSize;
	// Fast search in half, the index characters must be sorted strictly from big to small
	// There is a bug in the sorting of the PCtoLCD2002 modulo tool, which cannot be strictly sorted
	if (f->byCanQuickSearch)
	{
		shFrom = 0;
		for ( ; shFrom < shTo; )
		{
			shIndex = (shFrom + shTo) / 2; // Take the median character
			if (f->byIndexWChar) // double-byte character
			{
				cA = p[shIndex << 1]; // Note that Chinese character strings are not sorted by WORD value, but sorted by char bytecode
				cB = p[(shIndex << 1) + 1];
			}
			else // single-byte character
			{
				cA = p[shIndex];
			}
			if (cA == a && cB == b) // character found
			{
				// The font of a character is a monochrome bitmap
				lcd_DrawMonoPicture(f->pFontData + (shIndex * f->byCharFontBytes), f->byCharWidth, f->byCharHeight);
				LCD_POS_X_ADD(f->byCharWidth);
				return;
			}
			else if (cA > a || (cA == a && cB > b)) // the midpoint is bigger than the character you are looking for, look back
			{
				shTo = shIndex;
			}
			else // continue to look forward
			{
				shFrom = shIndex + 1;
			}
		}
	}
	else // sequential search, slower
	{
		for (shIndex = 0; shIndex < shTo; shIndex++)
		{
			if (f->byIndexWChar) // double-byte character
			{
				cA = p[shIndex << 1];
				cB = p[(shIndex << 1) + 1];
			}
			else // single-byte character
			{
				cA = p[shIndex];
			} 
			if (cA == a && cB == b) // character found
			{
				// The font of a character is a monochrome bitmap
				lcd_DrawMonoPicture(f->pFontData + (shIndex * f->byCharFontBytes), f->byCharWidth, f->byCharHeight);
				LCD_POS_X_ADD(f->byCharWidth);
				return;
			}
		}
	}

	// not found character, empty half position
	LCD_POS_X_ADD(f->byCharWidth / 2);

	return;
}


// Display string (support Chinese and English, support \r back to 0\n newline)
void lcd_DrawText(PCSTR pcStr)
{
	BYTE c;
	BYTE h;
 	const LCD_FONT *f = lcd.pFontAscii ? lcd.pFontAscii : lcd.pFontGB;
	if (NULL == pcStr || NULL == f || 0 == (h = f->byCharHeight)) // If the character is empty or the font is not set, it will not be processed
	{
		return;
	}

	while (0 != (c = *pcStr++))
	{
		if ('\r' == c)
		{
			lcd.wXPos = 0; // reset x
			continue;
		}
		else if ('\n' == c)
		{
			lcd.wXPos = 0; // reset x
			lcd.wYPos += h; // next line
			continue;
		}
		else if (c < 128) // ascii
		{
			if (c < ' ') // control characters are displayed as spaces
			{
				c = ' ';
			}
			DRAW_CHAR(lcd.pFontAscii, c, 0);
		}
		else // Chinese characters
		{
			DRAW_CHAR(lcd.pFontGB, c, *pcStr++);
		}
	}

}

// Display the string at the specified position
#define lcd_ShowText(color, x, y, str) lcd_SetTextColor(color); lcd_SetPos(x, y); lcd_DrawText(str);


// Display a bitmap that matches the number of LCD color bits, avoiding excessive time overhead caused by format conversion
#if LCD_COLOR_BITS > 2
	// Non-monochrome screen, this bitmap must be in dot mode, each byte is 1 row (8/color bit) column, and then stored in order from 0 to byWidth, from 0 to byHeight
	void lcd_DrawPicture(PCBYTE pbyData, WORD wWidth, WORD wHeight);
#else // For monochrome screen, the two functions are equivalent
	#define lcd_DrawPicture lcd_DrawMonoPicture
#endif


// Specify the location to display the bitmap
#define lcd_ShowMonoPicture(x, y, data, w, h) lcd_SetPos(x, y); lcd_DrawMonoPicture(data, w, h);
#define lcd_ShowPicture(x, y, data, w, h) lcd_SetPos(x, y); lcd_DrawPicture(data, w, h);

#endif // #ifndef _LCD_GUI_H_
