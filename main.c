/*
 * GccApplication5.c
 *
 * Created: 2025/5/30 21:58:07
 * Author : ucirv
 */ 

#include <avr/io.h>
#include "avr.h"
#include "lcd.h"
#include "music.h"
#include <stdio.h>
#include "game.h"
void
avr_init(void)
{
	WDTCR = 15;
}

void
avr_wait(unsigned short msec)
{
	TCCR0 = 3;
	while (msec--) {
		TCNT0 = (unsigned char)(256 - (XTAL_FRQ / 64) * 0.001);
		SET_BIT(TIFR, TOV0);
		WDR();
		while (!GET_BIT(TIFR, TOV0));
	}
	TCCR0 = 0;
}
void waitmus(unsigned short musec)
{
	TCCR0 = 2;
	while (musec--) {
		TCNT0 = 246;
		SET_BIT(TIFR, TOV0);
		WDR();
		while (!GET_BIT(TIFR, TOV0));
	}
	TCCR0 = 0;
}


int get_key(void) {
	for (int row = 0; row < 4; ++row) {
		
		DDRC = (1 << row);      
		PORTC = 0xF0;          

		avr_wait(1); 
		uint8_t col_state = PINC >> 4; 
		for (int col = 0; col < 4; ++col) {
			if (!(col_state & (1 << col))) {
				
				return row * 4 + col + 1; 
			}
		}
	}
	return 0; 
}



unsigned int read_adc_noise() {
	ADMUX = (1 << REFS0);           
	ADCSRA = (1 << ADEN)             
	| (1 << ADSC)             
	| (1 << ADPS1);           

	while (ADCSRA & (1 << ADSC));    
	return ADC;                      
}

void seed_rand() {
	unsigned int seed = read_adc_noise();
	srand(seed);
}

void menu_setup(data *dt){
	char buff[17];
	sprintf(buff, "keeping up: mode");
	lcd_clr();
	lcd_pos(0,0);
	lcd_puts2(buff);
		sprintf(buff, "<    medium    >");
		lcd_pos(1,0);
		lcd_puts2(buff);
	while (get_key() !=15){
		int input = 0;
		while (! (input = get_key()));
		if (input == 15) break;
		switch(input){
			case 5:
			dt->difficulty = (dt->difficulty + 2) % 3;
			break;
			case 7:
			dt->difficulty = (dt->difficulty + 1) % 3;
			break;
			default:
			break;
		}
		lcd_pos(1,0);
		switch(dt ->difficulty){
			case 0:
			sprintf(buff, "<     easy     >");
			lcd_puts2(buff);
			break;
			case 1:
			sprintf(buff, "<    medium    >");
			lcd_puts2(buff);
			break;
			case 2:
			sprintf(buff, "<     hard     >");
			lcd_puts2(buff);
			break;
			default:
			sprintf(buff, "unexpected!!!");
			lcd_puts2(buff);
			
		}
		avr_wait(200);
	}
	
}
int main(void) {
	DDRB |= (1 << 3);
	
	avr_init();
	lcd_init();
	lcd_init_custom_chars();
	data dt;
	data_initialize(&dt, 1);
	avr_wait(100);
	seed_rand();
	menu_setup(&dt);

	game_body(&dt);
	while (1)
	{
		if (MCUCSR & (1 << WDRF)) {
			lcd_puts2("Watchdog Reset!");//debug
			MCUCSR &= ~(1 << WDRF); 
		}
		int input = 0;
		while (! (input = get_key()));
		if (input == 13){
			data_initialize(&dt, 1);
			menu_setup(&dt);
			game_body(&dt);
		}
	}

	return 0;
}


