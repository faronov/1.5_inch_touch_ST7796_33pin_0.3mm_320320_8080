//////////////////////////////////////////////////////////////
//
// ������������DIY���Ա��� https://shop154838422.taobao.com/
// δ���������ҵʹ�ã�����ʹ������ɾ��������
//
//////////////////////////////////////////////////////////////
#ifndef _GUI_H_
#define _GUI_H_
// ʵ�ֻ�ͼ����
#include <stdio.h>

typedef const char* PCSTR;
typedef const unsigned char* PCBYTE;



// δ������ɫ��Ĭ�ϵ�ɫ
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

	// �ڰ׵���
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
	// 4�ҽ�
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

	// 16ɫ(1R2G1B)/16�ҽ�
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

	// 256ɫ(2R3G2B)
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

	// 16λ��ɫ(5R6G5B)
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


// ���õ�������,���û�����ע�룬�����ڽ�����ռ�ù���ռ�
typedef struct tagLCD_FONT
{
	BYTE byCharWidth; // ���ַ������
	BYTE byCharHeight; // ���ַ������
	BYTE byIndexWChar; // �Ƿ���ַ�������1 ascii 0
	BYTE byCanQuickSearch; // �����Ѿ���С����������������ٲ��ң����û����Ϳ��ٲ��ң��п����Ҳ���
	BYTE byCharFontBytes; // ����ÿ�ַ��ڴ��С 

	short shIndexSize; // �����ַ�����,ע�ⲻ���ֽ���������ΪpIndex�ֽ���/2
	PCSTR pIndex; // �ַ������ַ�������Ҫ���ַ�˳�����򣬱��ڿ��ٲ����ַ�
	PCBYTE pFontData; // ��������ʽ�������ң����ϵ��£�ÿ1�ֽ�Ϊ8��1��
} LCD_FONT;

// �ڲ���������
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
	LCD_RED & LCD_COLOR_MASK,	LCD_BLACK & LCD_COLOR_MASK,	// Ĭ��������ɫ

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

// �Զ�����X���ӣ���Ӧ������Ļ��������
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
		#else // 4�ҽף�ʵ���Ͼ��Ƕ�һ��
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
		mask = 1 << (i & 7); // ÿ�ж��ڴ��ֽڵĲ�ͬλ����
		LCD_SET_WINDOW(0, i, X_WIDTH - 1, i);
		for (j = 0; j < X_WIDTH; )
		{
		#if PT_PER_BYTE > 1
			tmp = 0;
			for (k = 0; k++ < PT_PER_BYTE; j++) // �����ƴ��Ϊһ��BYTE
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
// ���ҽ�����ʾ��ɫͼ��Ҫת��
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

	// ����д�룬Ҫ�����������ÿ8��1��һ�ֽڣ�ӳ��Ϊÿ����дһ����ɫ��
	for (i = 0; i < byHeight; i++) // ������ʾ
	{
		// ÿ������һ�ε�ַ�����ⳤ������ɫλ������ʱ����
		tmp = lcd.wYPos + i;
	 	if (!LCD_SET_WINDOW(lcd.wXPos, tmp, lcd.wXPos + byWidth - 1, tmp))
		{
			break;
		}

		tmp = i >> 3; // ���㵱ǰ�ڼ�ҳ
		mask = 1 << (i & 7); // ÿ�ж��ڴ��ֽڵĲ�ͬλ����
		p = &pbyData[tmp * byWidth]; // ����ͼ�����ݻ�ַ

		for (j = 0; j < byWidth; )
		{
		#if PT_PER_BYTE > 1
			tmp = 0;
			for (k = 0; k++ < PT_PER_BYTE; j++) // �����ƴ��Ϊһ��BYTE
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

// ��������ƥ�����ص�ͼ������ת��
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
// ��ɫ�����ص�ɫͼ������ת��
void lcd_DrawMonoPicture(PCBYTE pbyData, BYTE byWidth, BYTE byHeight)
{
	BYTE i;
	BYTE j;
	PCBYTE p = pbyData;
	BYTE bRevert = (0 != lcd.wBackColor); // �����Ǻڣ���ת��ɫ
#if LCD_COLOR_BITS==2 // 4�ҽף���ҳд2BYTE,��һBYTE������ɫ��λ���ڶ�BYTE������ɫ��λ
	BYTE k;
	BYTE a;
	BYTE b;
	data BYTE aMaskText = (lcd.wTextColor & 0x02) ? 1 : 0;
	data BYTE bMaskText = (lcd.wTextColor & 0x01) ? 1 : 0;
	data BYTE aMaskBack = (lcd.wBackColor & 0x02) ? 1 : 0;
	data BYTE bMaskBack = (lcd.wBackColor & 0x01) ? 1 : 0;
#endif
	for (i = 0; i < byHeight; i += 8, p += byWidth) // ��ҳ��ʾ   
	{
	 	if (!LCD_SET_WINDOW(lcd.wXPos, lcd.wYPos + i, lcd.wXPos + byWidth, lcd.wYPos + i + 7))
		{
			break;
		}
		for (j = 0; j < byWidth; j++)
		{
		#if LCD_COLOR_BITS==2 // 4�ҽף�0ת��Ϊ����ɫ��1ת��Ϊ�ı�ɫ
			a = 0;
			b = 0;
			for (k = 8; k-- > 0;)
			{
				a <<= 1;
				b <<= 1;
				if (p[j] & (1 << k)) // �ı���ɫ
				{
					a |= aMaskText;
					b |= bMaskText;
				}
				else // ������ɫ
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
	// �����۰����, pIndex�ַ���С��������
	short shFrom;
 	short shTo;
	short shIndex;
	BYTE cA;
	BYTE cB = b; // ���ֽ��ַ����ñȽ�b�ֽ�
	const char *p;
	if (NULL == f || NULL == (p = f->pIndex))
	{
		return;
	}
	shTo = f->shIndexSize;
	// �۰���ٲ��ң������ַ������ϸ�Ӵ�С����
	// PCtoLCD2002ȡģ���ߵ�������bug�������ϸ�����
	if (f->byCanQuickSearch)
	{
		shFrom = 0;
		for ( ; shFrom < shTo; )
		{
			shIndex = (shFrom + shTo) / 2; // ȡ��ֵ�ַ� 
			if (f->byIndexWChar) // ˫�ֽ��ַ�
			{
				cA = p[shIndex << 1]; // ע�⺺���ַ������ǰ�WORDֵ���򣬶��ǰ�char�ֽ�������
				cB = p[(shIndex << 1) + 1];
			}
			else // ���ֽ��ַ�
			{
				cA = p[shIndex];
			}
			if (cA == a && cB == b) // �ҵ��ַ�
			{
				// һ���ַ����������һ����ɫλͼ
				lcd_DrawMonoPicture(f->pFontData + (shIndex * f->byCharFontBytes), f->byCharWidth, f->byCharHeight);
				LCD_POS_X_ADD(f->byCharWidth);
				return;
			}
			else if (cA > a || (cA == a && cB > b)) // �е��Ҫ�ҵ��ָ��󣬻�ͷ��
			{
				shTo = shIndex;
			}
			else // ������ǰ��
			{
				shFrom = shIndex + 1;
			}
		}
	}
	else // ˳����ң�����
	{
		for (shIndex = 0; shIndex < shTo; shIndex++)
		{
			if (f->byIndexWChar) //  // ˫�ֽ��ַ�
			{
				cA = p[shIndex << 1];
				cB = p[(shIndex << 1) + 1];
			}
			else // ���ֽ��ַ�
			{
				cA = p[shIndex];
			} 
			if (cA == a && cB == b) // �ҵ��ַ�
			{
				// һ���ַ����������һ����ɫλͼ
				lcd_DrawMonoPicture(f->pFontData + (shIndex * f->byCharFontBytes), f->byCharWidth, f->byCharHeight);
				LCD_POS_X_ADD(f->byCharWidth);
				return;
			}
		}
	}

	// δ�ҵ����ַ����հ��λ��
	LCD_POS_X_ADD(f->byCharWidth / 2);

	return;
}


// ��ʾ�ַ���(֧����Ӣ�ģ�֧��\r��0\n����)
void lcd_DrawText(PCSTR pcStr)
{
	BYTE c;
	BYTE h;
 	const LCD_FONT *f = lcd.pFontAscii ? lcd.pFontAscii : lcd.pFontGB;
	if (NULL == pcStr || NULL == f || 0 == (h = f->byCharHeight)) // �ַ�Ϊ�ջ���δ�������壬������
	{
		return;
	}

	while (0 != (c = *pcStr++))
	{
		if ('\r' == c)
		{
			lcd.wXPos = 0; // x��λ
			continue;
		}
		else if ('\n' == c)
		{
			lcd.wXPos = 0; // x��λ
			lcd.wYPos += h; // ��һ��
			continue;
		}
		else if (c < 128) // ascii
		{
			if (c < ' ') // �����ַ���ʾΪ�ո�
			{
				c = ' ';
			}
			DRAW_CHAR(lcd.pFontAscii, c, 0);
		}
		else // ����
		{
			DRAW_CHAR(lcd.pFontGB, c, *pcStr++);
		}
	}

}

// ָ��λ����ʾ�ַ���
#define lcd_ShowText(color, x, y, str) lcd_SetTextColor(color); lcd_SetPos(x, y); lcd_DrawText(str);


// ��ʾ��LCD��ɫλ��ƥ���λͼ,����ת����ʽ���¹���ʱ�俪��
#if LCD_COLOR_BITS > 2
	// �ǵ�ɫ������λͼ����Ϊ��ģʽ��ÿ�ֽ�Ϊ1�У�8/��ɫλ����, �ٴ�0��byWidth����0��byHeight��˳��洢
	void lcd_DrawPicture(PCBYTE pbyData, WORD wWidth, WORD wHeight);
#else // ���ڵ�ɫ�������������ȼ�
	#define lcd_DrawPicture lcd_DrawMonoPicture
#endif


// ָ��λ����ʾλͼ
#define lcd_ShowMonoPicture(x, y, data, w, h) lcd_SetPos(x, y); lcd_DrawMonoPicture(data, w, h);
#define lcd_ShowPicture(x, y, data, w, h) lcd_SetPos(x, y); lcd_DrawPicture(data, w, h);

#endif // #ifndef _LCD_GUI_H_
