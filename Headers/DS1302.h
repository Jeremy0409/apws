// DS1302 Real Time Clock Library
// Written By: Royce Ng
// Date: 9/1/2017

#ifndef DS1302_H
#define DS1302_H

#include <xc.h>

#define _XTAL_FREQ 48000000

void ds1302_init(unsigned char ce, unsigned char dat, unsigned char clk);
void ds1302_read();
void ds1302_write();
void ds1302_set_time();
void ds1302_get_time();


#endif

