// Automated Plant Watering System
// Written By: Royce Ng, Ming Jing, Jeremy
// Date: 9/1/2017

#include <xc.h>


// Include Hardware Libraries
#include "DS1302.h"
#include "lcd.h"

// Temporarily use the school's LCD library.
// Pin defines for LCD library
//LCD display = {&PORTD, 6, 5, 4, 0, 1, 2, 3}; // PORT, RS, WR, EN and data pins

// Pin defines for RTC
#define CE PORTAbits.RA0 // Note: the CE pin used to be referred to as the /RST pin.
#define CLK PORTAbits.RA1
#define DAT PORTAbits.RA2 

// Pin defines for music module
#define MUSIC_PLAY PORTAbits.RA3 // Play/Stop button for music module
#define MUSIC_BUSY PORTAbits.RA4 // Busy input from music module

// Pin defines for keypad
#define KEYPAD_PORT PORTB
#define KEYPAD_DATA_AVAIL PORTBbits.RB5

// Pin define for pump control board
#define PUMP_CTL PORTCbits.RC0

// Function Prototypes
unsigned char mem_read(unsigned char addr); // Checks data EEPROM for existing data
void mem_write(unsigned char data, unsigned char addr); // Writes data to data EEPROM
char get_key(); // Gets key from keypad
void test_func(unsigned char *port, unsigned char pin);

// Variable/array declarations


void main()
{
   // Let us initialize all hardware to be used.
   // ds1302_init(CE, CLK, DAT); // Initialize DS1320 RTC.
   //lcd_init(display); // Initialize LCD
    ADCON1 = 0x0F; // Set analog pins to digital
    TRISB = 0xff;
    
    
    lcd_init();
    lcd_write_line("First line");
    lcd_pos(2,0);
    lcd_write_line("Second line");
    __delay_ms(1000);
    lcd_clear();
    
    mem_write(0x30,0x0F);
    
   // Let's check if there's any user configuration
   // data stored in the microcontroller
   if(mem_read(0x0F) == 0x30)
   {
       // No data. Let's ask the user to input data.
       //lcd_pos(0,1);
       //lcd_write_char('c');
       // No data. Let's ask the user to input data.
       lcd_write_line("Press C to continue.");
       while(get_key() != 'C');
       lcd_clear();
       lcd_pos(1,0);
       lcd_write_line("Test");
       
       
       
       
   }
   else
   {
       // Data exists. Load the data from memory.
       lcd_pos(1,0);
       lcd_write_line("Character is: ");
       lcd_pos(2,0);
       lcd_write_data(mem_read(0x0F)); 
       
       __delay_ms(2000);
       __delay_ms(2000);
   
   }
    
    while(1) 
   {
       // TODO: Do a polling check on the DS1302, and see if the time and date
       // is equal to the data on the DS1302. If so, then let's start the pump 
       // play music. 
       
       
       
   }
}

unsigned char mem_read(unsigned char addr)
{
    // Read from microcontroller Data EEPROM
    EEADR = addr;
    EEPGD = 0;
    CFGS = 0;
    RD = 1; // Set EEPROM read
    //while (RD==1); 
    return EEDATA;
}

void mem_write(char data, unsigned char addr)
{
    
    EECON1 = 0x04; // Allows write to EERPOM
    
    // According to the PIC18F4550 data sheet, the next 4 lines of are required. (Page 95/438)
    EECON2 = 0x55;
    __delay_ms(50);
    EECON2 = 0xaa;
    __delay_ms(50);
    
    // Write to microcontroller Data EEPROM
    EEPGD = 0;
    CFGS = 0;
    EEADR = addr;
    EEDATA = data;
    WREN = 1;
   // Wait for the byte to be written in EEPROM
    //while(EEIF == 0);
    EEIF = 0; // Clear EEIF Interrupt Flag
    //EECON1 = 0x00; // Disable write to EEPROM
    WREN =0;
}

char get_key()
{
    char key;
    const unsigned char lookup[] = "123F456E789DA0BC "; 
    
    while(PORTBbits.RB5 == 0); // Wait for key press
    key = PORTB & 0x0F;
    
    while(PORTBbits.RB5 == 1); // Key has been released
    return lookup[key];
    
}

// This test function tests the ability to pass
// ports and pins as arguments to a function
void test_func(unsigned char *port, unsigned char pin)
{
    char Mask[] = {1,2,4,8,16,32,64,128};
     *port |= Mask[pin]; // set pin# to 1 (turn on)
     __delay_ms(30);
    
     *port &= ~Mask[pin]; // set pin# to 0 (turn off)
     __delay_ms(30);
    
    
}