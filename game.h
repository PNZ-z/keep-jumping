/*
 * game.h
 *
 * Created: 2025/5/31 16:07:04
 *  Author: ucirv
 */ 


#ifndef GAME_H_
#define GAME_H_		
#define MC_ON_GROUND1 1			//positions: 1:runing 1, 2: running 2, 3: jumping or falling, 4: in air walk 1(it can last in air for one frame), 5: in air walk 2, 6 fall
#define MC_ON_GROUND2 2
#define MC_JUMP_IN_AIR 3
#define MC_WALK_IN_AIR 4
#define MC_WALK_IN_AIR2 5
#define MC_FALLING 6
#define EMPTYLOC -1
typedef struct  
{	char position;
	char jumpab;
}mc;


typedef struct  
{	char width;	//one unit in lcd is seperated into two
	char location;
}obstacle;

typedef struct
{
	obstacle block;
	obstacle coin;	//coin is 30 point each, one tick survive is 5pt
	
}line;

typedef struct  
{
	mc character;
	line upper;
	line lower;
	unsigned long score;
	char difficulty;
}data;

void data_initialize(data *dt, char difficulty);	//diff: 0:easy, 1: medium, 2:hard

void lcd_init_custom_chars();
void draw(data *dt);
void drawchar(data *dt);
void drawblock(data *dt);
void advance_block(data *dt);
void advance_bit_func(obstacle *itm);
int is_collided(data *dt);
void game_body(data *dt);
void jumpfuc(data *dt);
void generate_block(data *dt);
#endif /* GAME_H_ */