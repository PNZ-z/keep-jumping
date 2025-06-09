/*
 * CFile1.c
 *
 * Created: 2025/4/27 15:37:52
 *  Author: ucirv
 */ 
#ifndef _AVR_H
#define _AVR_H

#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/io.h>

#define XTAL_FRQ 8000000lu

#define SET_BIT(p,i) ((p) |=  (1 << (i)))
#define CLR_BIT(p,i) ((p) &= ~(1 << (i)))
#define GET_BIT(p,i) ((p) &   (1 << (i)))

#define WDR() asm volatile("wdr"::)
#define NOP() asm volatile("nop"::)
#define RST() for(;;);

void avr_init(void);

void avr_wait(unsigned short msec);

void waitmus(unsigned short musec);

int get_key(void);

int is_pressed(int r, int c);

int convert(int o);
typedef struct {
	int year;
	unsigned char month;
	unsigned char day;
	unsigned char hour;
	unsigned char minute;
	unsigned char second;
	unsigned char stm;
	unsigned char apm; //0:am, 1:pm
	} DateTime;

void advance_dt(DateTime *dt);

void init_dt(DateTime *dt);

void print_dt(const DateTime *dt);

void change_dt(DateTime *dt);

int check_valid(DateTime *dt);
void change_time(DateTime *dt);

#endif /* _AVR_H */