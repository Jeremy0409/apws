// LCD Library - 4 bit mode only!
// Written By: Royce Ng
// Date: 9/1/2017

#ifndef LCD_H
#define	LCD_H

#include <xc.h>

#define _XTAL_FREQ 48000000

typedef struct
{
    volatile unsigned char*  PORT;  // Pointer to the LCD port e.g &PORTC
    unsigned RS :3;                 // The RS bit of the LCD PORT 
    unsigned WR :3;                 // The W/R bit of the LCD PORT
    unsigned EN :3;                 // The EN bit of the LCD PORT 
    unsigned D4 :3;                 // The D4 bit of the LCD PORT 
    unsigned D5 :3;                 // The D5 bit of the LCD PORT 
    unsigned D6 :3;                 // The D6 bit of the LCD PORT 
    unsigned D7 :3;                 // The D7 bit of the LCD PORT 
} LCD;

extern LCD *lcd;

void lcd_init(LCD lcd);
void lcd_write_cmd(unsigned char cmd);
void lcd_write_char(unsigned char data);
void lcd_write_line(unsigned char data[]);
void lcd_pos(int x, int y);
void lcd_clear();

#endif

