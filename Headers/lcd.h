// LCD Library - 4 bit mode only!
// Written By: Royce Ng
// Date: 9/1/2017

#ifndef LCD_H
#define	LCD_H

#include <xc.h>

void lcd_write_cmd(unsigned char cmd);
void lcd_write_data(unsigned char data);
void lcd_strobe(void);
void lcd_init(void);
void lcd_write_line(unsigned char data[]);
void lcd_clear();
void lcd_pos(int x, int y);


#endif

