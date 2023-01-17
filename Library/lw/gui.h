//////////////////////////////////////////////////////////////
//
// 老王电子数码DIY，淘宝店 https://shop154838422.taobao.com/
// 未经许可勿商业使用，个人使用请勿删除此声明
//
//////////////////////////////////////////////////////////////
#ifndef _GUI_H_
#define _GUI_H_
// 实现绘图功能
#include <stdio.h>

typedef const char* PCSTR;
typedef const unsigned char* PCBYTE;



// 未定义颜色，默认单色
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

	// 黑白点阵
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
	// 4灰阶
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

	// 16色(1R2G1B)/16灰阶
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

	// 256色(2R3G2B)
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

	// 16位彩色(5R6G5B)
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


// 设置点阵字体,由用户代码注入，避免内建字体占用过多空间
typedef struct tagLCD_FONT
{
	BYTE byCharWidth; // 单字符字体宽
	BYTE byCharHeight; // 单字符字体高
	BYTE byIndexWChar; // 是否宽字符，汉字1 ascii 0
	BYTE byCanQuickSearch; // 索引已经从小到大排序，则允许快速查找，如果没排序就快速查找，有可能找不到
	BYTE byCharFontBytes; // 字体每字符内存大小 

	short shIndexSize; // 索引字符个数,注意不是字节数，汉字为pIndex字节数/2
	PCSTR pIndex; // 字符索引字符串，需要按字符顺序排序，便于快速查找字符
	PCBYTE pFontData; // 点阵屏格式，从左到右，从上到下，每1字节为8行1列
} LCD_FONT;

// 内部缓存数据
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
	LCD_RED & LCD_COLOR_MASK,	LCD_BLACK & LCD_COLOR_MASK,	// 默认字体颜色

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

// 自动适配X增加，适应特殊屏幕对齐问题
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
		#else // 4灰阶，实际上就是多一列
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
		mask = 1 << (i & 7); // 每行对于此字节的不同位掩码
		LCD_SET_WINDOW(0, i, X_WIDTH - 1, i);
		for (j = 0; j < X_WIDTH; )
		{
		#if PT_PER_BYTE > 1
			tmp = 0;
			for (k = 0; k++ < PT_PER_BYTE; j++) // 将多点拼接为一个BYTE
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
// 带灰阶屏显示单色图，要转换
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

	// 窗口写入，要将点阵字体的每8行1列一字节，映射为每像素写一个颜色点
	for (i = 0; i < byHeight; i++) // 逐行显示
	{
		// 每行设置一次地址，避免长度与颜色位不对齐时出错
		tmp = lcd.wYPos + i;
	 	if (!LCD_SET_WINDOW(lcd.wXPos, tmp, lcd.wXPos + byWidth - 1, tmp))
		{
			break;
		}

		tmp = i >> 3; // 计算当前第几页
		mask = 1 << (i & 7); // 每行对于此字节的不同位掩码
		p = &pbyData[tmp * byWidth]; // 此行图像数据基址

		for (j = 0; j < byWidth; )
		{
		#if PT_PER_BYTE > 1
			tmp = 0;
			for (k = 0; k++ < PT_PER_BYTE; j++) // 将多点拼接为一个BYTE
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

// 像素像素匹配像素的图，无需转换
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
// 单色屏像素单色图，无需转换
void lcd_DrawMonoPicture(PCBYTE pbyData, BYTE byWidth, BYTE byHeight)
{
	BYTE i;
	BYTE j;
	PCBYTE p = pbyData;
	BYTE bRevert = (0 != lcd.wBackColor); // 背景非黑，反转颜色
#if LCD_COLOR_BITS==2 // 4灰阶，按页写2BYTE,第一BYTE对于颜色高位，第二BYTE对于颜色低位
	BYTE k;
	BYTE a;
	BYTE b;
	data BYTE aMaskText = (lcd.wTextColor & 0x02) ? 1 : 0;
	data BYTE bMaskText = (lcd.wTextColor & 0x01) ? 1 : 0;
	data BYTE aMaskBack = (lcd.wBackColor & 0x02) ? 1 : 0;
	data BYTE bMaskBack = (lcd.wBackColor & 0x01) ? 1 : 0;
#endif
	for (i = 0; i < byHeight; i += 8, p += byWidth) // 按页显示   
	{
	 	if (!LCD_SET_WINDOW(lcd.wXPos, lcd.wYPos + i, lcd.wXPos + byWidth, lcd.wYPos + i + 7))
		{
			break;
		}
		for (j = 0; j < byWidth; j++)
		{
		#if LCD_COLOR_BITS==2 // 4灰阶，0转换为背景色，1转换为文本色
			a = 0;
			b = 0;
			for (k = 8; k-- > 0;)
			{
				a <<= 1;
				b <<= 1;
				if (p[j] & (1 << k)) // 文本颜色
				{
					a |= aMaskText;
					b |= bMaskText;
				}
				else // 背景颜色
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
	// 快速折半查找, pIndex字符从小到大排列
	short shFrom;
 	short shTo;
	short shIndex;
	BYTE cA;
	BYTE cB = b; // 单字节字符不用比较b字节
	const char *p;
	if (NULL == f || NULL == (p = f->pIndex))
	{
		return;
	}
	shTo = f->shIndexSize;
	// 折半快速查找，索引字符必须严格从大到小排序
	// PCtoLCD2002取模工具的排序有bug，不能严格排序
	if (f->byCanQuickSearch)
	{
		shFrom = 0;
		for ( ; shFrom < shTo; )
		{
			shIndex = (shFrom + shTo) / 2; // 取中值字符 
			if (f->byIndexWChar) // 双字节字符
			{
				cA = p[shIndex << 1]; // 注意汉字字符串并非按WORD值排序，而是按char字节码排序
				cB = p[(shIndex << 1) + 1];
			}
			else // 单字节字符
			{
				cA = p[shIndex];
			}
			if (cA == a && cB == b) // 找到字符
			{
				// 一个字符的字体就是一个单色位图
				lcd_DrawMonoPicture(f->pFontData + (shIndex * f->byCharFontBytes), f->byCharWidth, f->byCharHeight);
				LCD_POS_X_ADD(f->byCharWidth);
				return;
			}
			else if (cA > a || (cA == a && cB > b)) // 中点比要找的字更大，回头找
			{
				shTo = shIndex;
			}
			else // 继续向前找
			{
				shFrom = shIndex + 1;
			}
		}
	}
	else // 顺序查找，较慢
	{
		for (shIndex = 0; shIndex < shTo; shIndex++)
		{
			if (f->byIndexWChar) //  // 双字节字符
			{
				cA = p[shIndex << 1];
				cB = p[(shIndex << 1) + 1];
			}
			else // 单字节字符
			{
				cA = p[shIndex];
			} 
			if (cA == a && cB == b) // 找到字符
			{
				// 一个字符的字体就是一个单色位图
				lcd_DrawMonoPicture(f->pFontData + (shIndex * f->byCharFontBytes), f->byCharWidth, f->byCharHeight);
				LCD_POS_X_ADD(f->byCharWidth);
				return;
			}
		}
	}

	// 未找到的字符，空半个位置
	LCD_POS_X_ADD(f->byCharWidth / 2);

	return;
}


// 显示字符串(支持中英文，支持\r回0\n换行)
void lcd_DrawText(PCSTR pcStr)
{
	BYTE c;
	BYTE h;
 	const LCD_FONT *f = lcd.pFontAscii ? lcd.pFontAscii : lcd.pFontGB;
	if (NULL == pcStr || NULL == f || 0 == (h = f->byCharHeight)) // 字符为空或者未设置字体，不处理
	{
		return;
	}

	while (0 != (c = *pcStr++))
	{
		if ('\r' == c)
		{
			lcd.wXPos = 0; // x复位
			continue;
		}
		else if ('\n' == c)
		{
			lcd.wXPos = 0; // x复位
			lcd.wYPos += h; // 下一行
			continue;
		}
		else if (c < 128) // ascii
		{
			if (c < ' ') // 控制字符显示为空格
			{
				c = ' ';
			}
			DRAW_CHAR(lcd.pFontAscii, c, 0);
		}
		else // 汉字
		{
			DRAW_CHAR(lcd.pFontGB, c, *pcStr++);
		}
	}

}

// 指定位置显示字符串
#define lcd_ShowText(color, x, y, str) lcd_SetTextColor(color); lcd_SetPos(x, y); lcd_DrawText(str);


// 显示与LCD颜色位数匹配的位图,避免转换格式导致过多时间开销
#if LCD_COLOR_BITS > 2
	// 非单色屏，此位图必须为点模式，每字节为1行（8/颜色位）列, 再从0到byWidth，从0到byHeight的顺序存储
	void lcd_DrawPicture(PCBYTE pbyData, WORD wWidth, WORD wHeight);
#else // 对于单色屏，两个函数等价
	#define lcd_DrawPicture lcd_DrawMonoPicture
#endif


// 指定位置显示位图
#define lcd_ShowMonoPicture(x, y, data, w, h) lcd_SetPos(x, y); lcd_DrawMonoPicture(data, w, h);
#define lcd_ShowPicture(x, y, data, w, h) lcd_SetPos(x, y); lcd_DrawPicture(data, w, h);

#endif // #ifndef _LCD_GUI_H_
