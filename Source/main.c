// Automated Plant Watering System
// Written By: Royce Ng, Ming Jing, Jeremy
// Date: 9/1/2017

#include <xc.h>


// Include Hardware Libraries
#include "DS1302.h"
#include "lcd.h"

// Pin define for LCD library
LCD display = {&PORTD, 6, 5, 4, 0, 1, 2, 3}; // PORT, RS, WR, EN and data pins

// Pin defines for RTC
#define CE PORTAbits.RA0 // Note: the CE pin used to be referred to as the /RST pin.
#define CLK PORTAbits.RA1
#define DAT PORTAbits.RA2 

// Pin defines for music module
#define MUSIC_PLAY PORTAbits.RA3 // Play/Stop button for music module
#define MUSIC_BUSY PORTAbits.RA4 // Busy input from music module

// Pin define for pump control board
#define PUMP_CTL PORTEbits.RE0

// Function Prototypes
unsigned char mem_read(unsigned char addr); // Checks data EEPROM for existing data
void mem_write(unsigned char data, unsigned char addr); // Writes data to data EEPROM


void main()
{
   // Let us initialize all hardware to be used.
   ds1302_init(CE, CLK, DAT); // Initialize DS1320 RTC.
   lcd_init(display); // Initialize LCD
   
   // Let's check if there's any user configuration
   // data stored in the microcontroller
   if(sizeof(mem_read(0x00)) == 0)
   {
       // No data. Let's ask the user to input data.
       lcd_pos(0,1);
       lcd_writeline("Press C to continue.");
       
       lcd_clear();
       
       
   }
   else
   {
       // Data exists. Load the data from memory.
       mem_read(0x00); 
   }
   
   while(1) 
   {
       
       
   }
}

unsigned char mem_read(unsigned char addr)
{
    // Read from microcontroller Data EEPROM
    EEADR = addr;
    RD = 1; // Set EEPROM read
    while (RD==1); 
    return EEDATA;
}

void mem_write(unsigned char data, unsigned char addr)
{
    
    EECON1 = 0x04; // Allows write to EERPOM
    
    // According to the PIC18F4550 data sheet, the next 4 lines of are required. (Page 95/438)
    EECON2 = 0x55;
    __delay_ms(50);
    EECON2 = 0xaa;
    __delay_ms(50);
    
    // Write to microcontroller Data EEPROM
    EEADR = addr;
    EEDATA = data;
    WR = 1;
   // Wait for the byte to be written in EEPROM
    while(EEIF == 0);
    EEIF = 0; // Clear EEIF Interrupt Flag
    
    EECON1 = 0x00; // Disable write to EEPROM
}
