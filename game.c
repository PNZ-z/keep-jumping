/*
 * game.c
 *
 * Created: 2025/5/31 16:07:13
 *  Author: ucirv
 */ 
#include "game.h"
#include "lcd.h"
#include "music.h"
#include "avr.h"
#include <avr/io.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

uint8_t dino1[8] = {
	0x06,
	0x0F,
	0x04,
	0x0E,
	0x0E,
	0x04,
	0x0A,
	0x0A
};
uint8_t dino2[8] = {
	0x06,
	0x0F,
	0x04,
	0x1D,
	0x17,
	0x04,
	0x1A,
	0x03
};

uint8_t dino_jump_lower[8] = {
	0x1D,
	0x17,
	0x04,
	0x0B,
	0x11,
	0x00,
	0x00,
	0x00
};
uint8_t dino_jump_head[8] = {
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x06,
	0x0F
};
uint8_t block_l[8] = {
	 0x1c,
	 0x1c,
	 0x1c,
	 0x1c,
	 0x1c,
	 0x1c,
	 0x1c,
	 0x1c
};

uint8_t block_r[8] = {
	  0x07,
	  0x07,
	  0x07,
	  0x07,
	  0x07,
	  0x07,
	  0x07,
	  0x07
};

uint8_t block[8] = {
	 0x1F,
	 0x1F,
	 0x1F,
	 0x1F,
	 0x1F,
	 0x1F,
	 0x1F,
	 0x1F
};

uint8_t coin[8] = {
	
		0x11,
		0x0A,
		0x1F,
		0x04,
		0x1F,
		0x04,
		0x04,
		0x04
	
};
void data_initialize(data *dt, char difficulty /* = 0 */){
	dt->character.position = MC_ON_GROUND1; //lower
	dt ->character.jumpab = 1; //default
	dt ->lower.block.location = -1; //the 4.5th
	dt -> lower.block.width = 10;	//width is one by one
	dt -> lower.coin.location = -1;
	dt ->lower.coin.width = 1;
	dt->upper.block.location = -1;
	dt -> upper.block.width = 8;
	dt -> upper.coin.location = -1;
	dt ->upper.coin.width = 1;
	dt->score = 0;
	dt -> difficulty = difficulty;
	
}
void lcd_init_custom_chars() {
	lcd_create_custom_char(0, dino1);
	lcd_create_custom_char(1, dino2);
	lcd_create_custom_char(2, dino_jump_head);
	lcd_create_custom_char(3, dino_jump_lower);
	lcd_create_custom_char(4, block_l);
	lcd_create_custom_char(5, block);
	lcd_create_custom_char(6, block_r);
	lcd_create_custom_char(7, coin);
}
void drawchar(data *dt) {
	switch (dt->character.position) {
		case MC_ON_GROUND1:
		lcd_pos(0,0);
		lcd_put(' ');
		lcd_pos(1, 0);
		lcd_put(0); // dino1
		break;
		case MC_ON_GROUND2:
		lcd_pos(0,0);
		lcd_put(' ');
		lcd_pos(1, 0);
		lcd_put(1); // dino2
		break;
		case MC_JUMP_IN_AIR:
		
		lcd_pos(0, 0);
		lcd_put(2); // jump head
		lcd_pos(1, 0);
		lcd_put(3); // jump lower
		break;
		case MC_WALK_IN_AIR:
		lcd_pos(0, 0);
		lcd_put(0); // dino1
		lcd_pos(1,0);
		lcd_put(' ');
		break;
		case MC_WALK_IN_AIR2:
		lcd_pos(0, 0);
		lcd_put(1); // dino2
		lcd_pos(1,0);
		lcd_put(' ');
		break;
		case MC_FALLING:
		lcd_pos(0, 0);
		lcd_put(2); // jump head
		lcd_pos(1, 0);
		lcd_put(3); // jump lower
		break;
	}
}

void drawblock(data *dt) {
	char upper_location = dt->upper.block.location;
	if (upper_location != 255) {
		lcd_pos(0, upper_location / 2);
		if (upper_location % 2 == 1) {
			lcd_put(6); // block_r
			for (int i = 0; i < (dt->upper.block.width - 1) / 2; ++i) {
				lcd_pos(0, upper_location / 2 + i + 1);
				lcd_put(5); // block
			}
			if (dt->upper.block.width % 2 != 1) {
				lcd_pos(0, upper_location / 2 + dt->upper.block.width / 2);
				lcd_put(4); // block_l
			}
			} else {
			lcd_put(4); // block_l
			for (int i = 0; i < (dt->upper.block.width) / 2; ++i) {
				lcd_pos(0, upper_location / 2 + i);
				lcd_put(5); // block
			}
			if (dt->upper.block.width % 2 == 1) {
				lcd_pos(0, upper_location / 2 + dt->upper.block.width / 2);
				lcd_put(4); // block_l
			}
		}
	}

	char lower_location = dt->lower.block.location;
	if (lower_location != 255) {
		lcd_pos(1, lower_location / 2);
		if (lower_location % 2 == 1) {
			lcd_put(6); // block_r
			for (int i = 0; i < (dt->lower.block.width - 1) / 2; ++i) {
				lcd_pos(1, lower_location / 2 + i + 1);
				lcd_put(5); // block
			}
			if (dt->lower.block.width % 2 != 1) {
				lcd_pos(1, lower_location / 2 + dt->lower.block.width / 2);
				lcd_put(4); // block_l
			}
			} else {
			lcd_put(4); // block_l
			for (int i = 0; i < (dt->lower.block.width) / 2; ++i) {
				lcd_pos(1, lower_location / 2 + i);
				lcd_put(5); // block
			}
			if (dt->lower.block.width % 2 == 1) {
				lcd_pos(1, lower_location / 2 + dt->lower.block.width / 2);
				lcd_put(4); // block_l
			}
		}
	}

	char coin_loc = dt->lower.coin.location;
	if (coin_loc != 255) {
		lcd_pos(1, coin_loc / 2);
		lcd_put(7); // coin
	}
	coin_loc = dt->upper.coin.location;
	if (coin_loc != 255) {
		lcd_pos(0, coin_loc / 2);
		lcd_put(7); // coin
	}
}
void advance_bit_func(obstacle *itm){
	if (itm ->location != 255 )
	{
		if (itm ->location == 0)
		{
			if (itm ->width > 1) itm -> width -= 1;
			else itm ->location = -1;
		}
		else itm -> location -= 1;
	}
}
void advance_block(data *dt){
	advance_bit_func(&(dt ->upper.block));
	advance_bit_func(&(dt ->upper.coin));
	advance_bit_func(&(dt ->lower.block));
	advance_bit_func(&(dt ->lower.coin));
	dt->score += 10;
	switch (dt->character.position) {
		case MC_ON_GROUND1:

		dt->character.position = MC_ON_GROUND2;
		break;
		case MC_ON_GROUND2:
		dt->character.position = MC_ON_GROUND1;
		break;
		case MC_JUMP_IN_AIR:
	
		dt->character.position = MC_WALK_IN_AIR;
		break;
		case MC_WALK_IN_AIR:
	
		dt->character.position = MC_WALK_IN_AIR2;
		break;
		case MC_WALK_IN_AIR2:
		if (dt->lower.block.location == 0 || dt->lower.block.location == 1)
		dt->character.position = MC_WALK_IN_AIR;
		else
		dt->character.position = MC_FALLING;
		break;
		case MC_FALLING:

		dt->character.position = MC_ON_GROUND1;
		break;
	}
	
}

int is_collided(data *dt){	//1 means exit game, 0 means normal,, adding point if hit the coin
	int ret_val = 0;
	if (dt->lower.block.location <= 1 )
	{
		if (dt->character.position == MC_ON_GROUND1 || dt->character.position == MC_ON_GROUND2 )
		{
			play_song(die, 4, 1, 1);
			return 1;
		}
	}
	if (dt->upper.block.location <=1)
	{	if (dt->character.position != MC_ON_GROUND1 && dt->character.position != MC_ON_GROUND2 )
		{
			play_song(die, 4, 1, 1);
			
			return 1;
		}
	}
	if (dt->lower.coin.location <=1)
	{
		if (dt->character.position == MC_ON_GROUND1 || dt->character.position == MC_ON_GROUND2 )
		{
			dt->lower.coin.location = -1;
			dt ->score += 30;
			play_song(get_coin, 2, 1, 1);
			avr_wait(10);
		}
	}
	if (dt->upper.coin.location <=1)
	{	if (dt->character.position != MC_ON_GROUND1 && dt->character.position != MC_ON_GROUND2 )
		{
			
			dt->upper.coin.location =-1;
			dt ->score += 30;
			play_song(get_coin, 2, 1, 1);
			avr_wait(10);
		}
	}
	return ret_val;
}


void generate_block(data *dt) {
	WDR();
	char lower_emp_blo = (dt->lower.block.location == 255);
	char upper_emp_blo = (dt->upper.block.location == 255);
	
	if (lower_emp_blo) {
		if (dt->lower.coin.location ==255) {
			if ((rand() % 3) == 0)
			{
				dt->lower.block.location = ((rand() % 3) == 0) ? 32 + rand()%4 : 255;
				dt->lower.block.width = 4 + rand() % 11;
			}
		}
	}
	
	else if (upper_emp_blo) {
		if (dt->upper.coin.location == 255 && (dt ->lower.block.location +dt ->lower.block.width < 28)) {
			if ((rand() % 3) == 0)
			{
				dt->upper.block.location = ((rand() % 3) == 0) ? 32 + rand()%4 : 255;
				dt->upper.block.width = 4 + rand() % 11;
			}
		}
	}

	if (dt->lower.coin.location == 255) {
		if (dt->lower.block.location + dt->lower.block.width < 28) {
			dt->lower.coin.location = ((rand() % 5) == 0) ? 255 : 32;
		}
	}

	if (dt->upper.coin.location == 255) {
		if (dt->upper.block.location + dt->upper.block.width < 28) {
			dt->upper.coin.location = ((rand() % 5) == 0) ? 255 : 32;
		}
	}
}

void game_body(data *dt){
	int int_flag_time = 0;
	switch (dt ->difficulty){	//easy :: 500ms tick medium 300, hard 100
		case 0: 
		int_flag_time = 8;
		break;
		case 1:
		int_flag_time = 5;
		break;
		case 2:
		int_flag_time = 2;
		break;
	}
	int cut_counter = 0;
	while(1){
		char state = dt -> character.position == MC_ON_GROUND1 ||dt -> character.position == MC_ON_GROUND2;
		char state2 = cut_counter >= int_flag_time;
		if ( get_key() == 2 && state)
		{
			dt ->character.position = MC_JUMP_IN_AIR;
			
			
			
			if (is_collided(dt) == 1)
			break;
			
			
		}else avr_wait(20);
		generate_block(dt);
		if (state2)
		{
			cut_counter = 0;
			advance_block(dt);
			if(is_collided(dt) == 1) break;
			
			
		}else avr_wait(10);
		
		lcd_clr();
		drawchar(dt);
		drawblock(dt);
		cut_counter += 1;
		avr_wait(1);
	}
	lcd_clr();
	char final[17];
	sprintf(final, "score:%07d", dt->score);
	lcd_pos(0,0);
	lcd_puts2(final);
	sprintf(final, "press * restart");
	lcd_pos(1, 0);
	lcd_puts2(final);
	avr_wait(3000);
}