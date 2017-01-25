// LCD Library
// Written By: Royce Ng
// Date: 9/1/2017

#include "lcd.h" 

LCD lcd_var; // Internal variable so that functions can work with the LCD.

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
    
    
    __delay_ms(30); // Let the display supply voltage settle.

    lcd_write_cmd(0x28); // Function Set instruction				 
    lcd_write_cmd(0x0e); // Display On/Off Control instruction
    lcd_write_cmd(0x06); // Entry Mode Set instruction
    lcd_write_cmd(0x01); // Clear Display instruction
    __delay_ms(10);	
}

// This function writes a command to the LCD device.
void lcd_write_cmd(unsigned char cmd)
{
    unsigned char cmd_var;
    
    lcd_var.RS = 0;
    __delay_us(40); // Let LCD settle down 
    
    cmd_var = cmd;
    cmd_var = cmd_var >> 4;	// Output upper 4 bits, by shifting out lower 4 bits
    lcd_var.PORT = cmd_var & 0x0f; // Output to port
    __delay_us(1000); 
    lcd_strobe();
    __delay_us(1000);			

    // Note: The code provided by the school repeats the above chunk of
    // code again. Re-implement if necessary. 
    
}

void lcd_write_char(unsigned char data)
{
    unsigned char data_var;

    lcd_var.RS = 1;	// Select data mode			
    __delay_us(40);	// Let LCD settle down		

    data_var = data;
    data_var = data_var >> 4;
    lcd_var.PORT = data_var & 0x0f;
    __delay_us(1000);

    lcd_var.RS = 1;
    __delay_us(1000);			

    lcd_strobe();
    __delay_us(1000);

    data_var = data;
    lcd_var.PORT = data_var & 0x0f;
    __delay_us(1000);

    lcd_var.RS = 1;
    __delay_us(1000); 			

    lcd_strobe();
    __delay_us(1000);
}


void lcd_write_line(unsigned char data[])
{
    int msg_cnt;
    for(msg_cnt = 0; data[msg_cnt] != '\0'; msg_cnt++)
    {
        // char print_var = data[msg_cnt]; is this necessary?
        lcd_write_char(data[msg_cnt]);
    }
}


// This function sets the position of the cursor
// for a two line LCD.
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