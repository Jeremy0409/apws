/*
 * File:   lcd utilities.c
 *
 * Created on 13 January, 2016, 10:28 AM
 */

#include "lcd.h"	// Include file is located in the project directory

#include <xc.h>
#define _XTAL_FREQ 48000000
#define LCD_RS PORTDbits.RD6    //  Register Select on LCD
#define LCD_EN PORTDbits.RD4    //  Enable on LCD controller
#define LCD_WR PORTDbits.RD5    //  Write on LCD controller
void lcd_strobe(void);

<<<<<<< HEAD
//--- Function for writing a command byte to the LCD in 4 bit mode -------------
=======
// This function initializes the LCD screen
void lcd_init(LCD lcd)
{
    
    // Let's check which port is being used for the LCD
    // display, and we will set that port as an output.
    if(lcd.PORT == &PORTA) 
    {
        TRISA = 0x00;
        PORTA = 0x00;
    }
    else if(lcd.PORT == &PORTB) 
    {
        TRISB = 0x00;
        PORTB = 0x00;
    }
    else if(lcd.PORT == &PORTC) 
    {
        TRISC = 0x00;
        PORTC = 0x00;
    }
    else if(lcd.PORT == &PORTD) 
    {
        TRISD = 0x00;
        PORTD = 0x00;
    }
    else if(lcd.PORT == &PORTE) 
    {
        TRISE = 0x00;
        PORTE = 0x00;
    }
    
    lcd.EN = 0;
    lcd.WR = 0; // Set LCD in write mode
    lcd.RS = 0; // Set LCD in command mode
    
    lcd_var = lcd; // Set lcd_var so that other functions can work 
    
    // Apparently, these 2 lines are needed to ensure proper operation
    // of the LCD display. I have not found out why yet though.
    lcd_write_cmd(0x33);
    lcd_write_cmd(0x32);
>>>>>>> origin/master

void lcd_write_cmd(unsigned char cmd)
{
    unsigned char temp2;

    LCD_RS = 0;				// Select LCD for command mode
    __delay_us(4);			// (40us) delay for LCD to settle down

    temp2 = cmd;
    temp2 = temp2 >> 4;			// Output upper 4 bits, by shifting out lower 4 bits
    PORTD = temp2 & 0x0F;		// Output to PORTD which is connected to LCD
    __delay_us(830);			// (10ms) -Delay at least 1 ms before strobing

    lcd_strobe();
    __delay_us(830);			// (10ms) - Delay at least 1 ms after strobing

    temp2 = cmd;			// Re-initialise temp2
    PORTD = temp2 & 0x0F;		// Mask out upper 4 bits
    __delay_us(830);			// (10ms) - Delay at least 1 ms before strobing

    lcd_strobe();
    __delay_us(830);			// (10ms) - Delay at least 1 ms before strobing
}

//---- Function to write a character data to the LCD ---------------------------

void lcd_write_data(unsigned char data)
{
    unsigned char temp1;

    LCD_RS = 1;				// Select LCD for data mode
    __delay_us(4);			// (40us) delay for LCD to settle down

    temp1 = data;
    temp1 = temp1 >> 4;
    PORTD = temp1 & 0x0F;
    __delay_us(830);

    LCD_RS = 1;
    __delay_us(830);			//_-_ strobe data in

    lcd_strobe();
    __delay_us(830);

    temp1 = data;
    PORTD = temp1 & 0x0F;
    __delay_us(830);

    LCD_RS = 1;
    __delay_us(830); 			//_-_ strobe data in

    lcd_strobe();
    __delay_us(830);
}

//-- Function to generate the strobe signal for command and character----------

void lcd_strobe(void)			// Generate the E pulse
{
    LCD_EN = 1;				// E = 0
    __delay_us(83);			// (1ms) delay for LCD_EN to settle
    LCD_EN = 0;				// E = 1
    __delay_us(83);			// (1ms) delay for LCD_EN to settle
}

//---- Function to initialise LCD module ----------------------------------------
void lcd_init(void)
{
    int i;
    
    TRISD = 0x00;
    PORTD = 0x00;			// PORTD is connected to LCD data pin
    LCD_EN = 0;
    LCD_RS = 0;				// Select LCD for command mode
    LCD_WR = 0;				// Select LCD for write mode

    for(i=0;i<100;i++)
    __delay_ms(10);			// Delay a total of 1 s for LCD module to
                            // finish its own internal initialisation


    /* The data sheets warn that the LCD module may fail to initialise properly when
       power is first applied. This is particularly likely if the Vdd
       supply does not rise to its correct operating voltage quickly enough.

       It is recommended that after power is applied, a command sequence of
       3 bytes of 3xh be sent to the module. This will ensure that the module is in
       8-bit mode and is properly initialised. Following this, the LCD module can be
       switched to 4-bit mode.
    */
    
    lcd_write_cmd(0x33);
    lcd_write_cmd(0x32);
    
     __delay_ms(30); // Let the display supply voltage settle.

    lcd_write_cmd(0x28); // Function Set instruction				 
    lcd_write_cmd(0x0e); // Display On/Off Control instruction
    lcd_write_cmd(0x06); // Entry Mode Set instruction
    lcd_write_cmd(0x01); // Clear Display instruction
    __delay_ms(10); 
}

void lcd_write_line(unsigned char data[])
{
    int msg_cnt;
    for(msg_cnt = 0; data[msg_cnt] != '\0'; msg_cnt++)
    {
        // char print_var = data[msg_cnt]; is this necessary?
        lcd_write_data(data[msg_cnt]);
    }
}

void lcd_clear()
{
    lcd_write_cmd(0x01);
}

void lcd_pos(int x, int y)
{
    if(x == 1)
    {
        lcd_write_cmd(0x80 + y);
    }
    else if(x == 2)
    {
        lcd_write_cmd(0xC0 + y);
    }
}
<<<<<<< HEAD
=======

// This function strobes the LCD's EN pin.
void lcd_strobe()
{
    lcd_var.EN = 0; 
    __delay_us(100);
    lcd_var.EN = 1;
    __delay_us(100);
}

// This function clears the LCD display
void lcd_clear()
{
    lcd_write_cmd(0x01); // Clear instruction
}
>>>>>>> origin/master
