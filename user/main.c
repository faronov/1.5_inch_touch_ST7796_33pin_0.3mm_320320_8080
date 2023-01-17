//////////////////////////////////////////////////// ////////////
//
// Laowang Electronics Digital DIY, Taobao store https://shop154838422.taobao.com/
// Do not use commercially without permission, please do not delete this statement for personal use
//
//////////////////////////////////////////////////// ////////////
// 1.5-inch square color screen with touch screen, 51 sample codes
//
// Cable screen printing: FPC1543301E Touch screen printing: GVS-C789-FCP_V4
// Cable definition: 1, 2, 19, 21, 23-GND (connected internally, just connect one) 9-TE 11~18-D0~D8
// 20-RD 22-DC 24-WR 25-CS 26-RST 27,28-VDD(3V3) 30-BL- 32-BL+(3S,8V) 33-?
//
//////////////////////////////////////////////////// ////////////

// 1, the referenced system library
#if defined(MS51) // Using Xintang MS51 chip 16KB
#include "MS51_32K.h"
#else // Traditional 51, such as STC8 and other chips above 16KB,
#include <reg52.h>
#endif

// Unify common data type definitions
typedef unsigned char BYTE;
typedef unsigned short WORD;


// 2, referenced driver library
// 2.1, software IO, support 4-wire SPI/3-wire SPI/IIC/8-bit 8080/8-bit 6800
// User needs macro definition to select IO mode and pin
#define P8_8080

// The following is to define the specific pins of the software IO, which can be changed by yourself
#ifdef MS51

// LCD has suggested definition of reset pin.
// If not defined, the LCD can only be initialized once after the LCD is powered on, and the hardware initialization cannot be repeated (reliability is reduced)
// If your circuit uses MCU pins to control the LCD power supply, you can use the power supply to hard reset, no need to define this pin
#define LCD_RST P13

// P8080 parallel port, the data port needs the entire P port
#define LCD_DATA P0

#define LCD_WR P10

// This module only writes and does not read
#define LCD_RD P11 // If this pin is defined, the code is automatically set to 1

// data/command signal selection, aliases are A0, DC, R_S
#define LCD_RS P12

// Chip Select
#define LCD_CS P14

#else // General 51 such as stc, different chips have different IO layouts. define separately
// stc8h3k tssop20 test
// Define pin variables that are unified with MS51
sbit P31=P3^1; //serial clock
sbit P30=P3^0; //serial data
sbit P32=P3^2;
sbit P33=P3^3;
sbit P34=P3^4;
sbit P35=P3^5;
sbit P36=P3^6;
sbit P37=P3^7;

#define LCD_CS P37
#define LCD_RST P36
#define LCD_RS P35
#define LCD_WR P31
#define LCD_RD P30

// P8080 parallel port, the data port needs the entire P port
#define LCD_DATA P1

#endif

#include "softio.h"

// 2.2, ST7789 display chip driver library, you can define some macros to adapt to such screens with different parameters
#define LCD_REVERT_RGB // The RGB pixel order of this screen is BGR
#define LCD_REVERT_X // x reverse reverse
#define LCD_DISPLAY_INVERSION // default inversion
#define X_WIDTH 320
#define Y_WIDTH 320
// st7796, ST7789 codes are fully compatible
#include "st7789.h" //

// 2.3, simple graphics function library
#include "gui.h"

// 3, users need to customize resources
// 3.1 Monochrome images, fonts, etc., use PCtoLCD2002 to generate the data
#include "res.h"
 
// 3.2 16-bit color map, use Image2Lcd to generate the data
#include "res_color_pic.h"

// Next, write different chip initialization functions according to different chips
// Because some chips need special initialization codes such as clearing the watchdog and setting the clock
#ifdef MS51

void init_MCU()
{
}

// IO push-pull output, no need to connect pull-up resistor
void init_IO()
{
// SPI&IIC
P10_PUSHPULL_MODE;
P11_PUSHPULL_MODE;
P12_PUSHPULL_MODE;
P13_PUSHPULL_MODE;
P14_PUSHPULL_MODE;

#if defined(P8_6800) || defined(P8_8080)
P00_PUSHPULL_MODE;
P01_PUSHPULL_MODE;
P02_PUSHPULL_MODE;
P03_PUSHPULL_MODE;
P04_PUSHPULL_MODE;
P05_PUSHPULL_MODE;
P06_PUSHPULL_MODE;
P07_PUSHPULL_MODE;
#endif

}

#else // STC 51 chip

// STC
sfr P1M1 = 0x91; //PxM1.n,PxM0.n =00--->Standard, 01--->push-pull
sfr P1M0 = 0x92; // =10--->pure input, 11--->open drain
sfr P0M1 = 0x93;
sfr P0M0 = 0x94;
sfr P2M1 = 0x95;
sfr P2M0 = 0x96;
sfr P3M1 = 0xB1;
sfr P3M0 = 0xB2;


void init_MCU()
{
}

void init_IO()
{
P1M0=0xFF; // P1 push-pull output
P1M1=0x00;
P3M0=0xFF; // P3 push-pull output
P3M1=0x00;
}

#endif




// Display test cases, without distinguishing between MCU and display IC
void test_lcd()
{
// Set the foreground and background colors of the default font and monochrome image
lcd_SetTextColor(LCD_BLUE);
lcd_SetBackColor(LCD_WHITE);

// set the default font
lcd_SetAsciiFont(&ASC_8x16); // English font
lcd_SetGBFont(&GB_16x16); // Chinese font

lcd_Clear(); // After the LCD is powered on, the memory data is a random value, you need to use the background color to brush the full screen

// Color screen displays color pictures
lcd_ShowPicture(X_WIDTH / 2 - 28 - 32, Y_WIDTH / 2 - 28 - 30, gImage, 56, 56);

// 1bit bitmap, the color screen is automatically converted to the current text color
lcd_ShowMonoPicture(X_WIDTH / 2 - 32 + 32, Y_WIDTH / 2 - 32 - 30, MonoBmp64x64, 64, 64);

// keil bug directly uses the Chinese character "number" to be garbled, and replace it with hex \xca\xfd
lcd_ShowText(LCD_RED, 56, Y_WIDTH / 2 + 36 - 30, "Lawang Electronics\xca\xfd code DIY");
  lcd_ShowText(LCD_BLACK, 56, Y_WIDTH / 2 + 56 - 30, "Mobile phone Taobao scan");
  lcd_ShowText(LCD_BROWN, 36, Y_WIDTH / 2 + 76 - 30, "Display parameters\xca\xfd: 320*320 16 bits");

MCU_DELAY_MS(20000);

}

// main function
int main()
{
init_MCU();
init_IO();
LCD_IC_INIT();

for (;;)
{
test_lcd();
LCD_IC_INIT(); //Increase reliability, the poor contact of the pins during the test leads to initialization failure, no need to re-power
}
return 0;
}
