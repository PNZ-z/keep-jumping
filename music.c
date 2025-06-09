/*
 * CFile1.c
 *
 * Created: 2025/5/10 19:38:51
 *  Author: ucirv
 */ 
#include "music.h"
#include "avr.h"
#include "lcd.h"
#include <math.h>
#include <stdio.h>
void play_song(const PlayingNote song[], int length, int speed, int pitch) {
	int i;
	for (i = 0; i < length; i++) {

		play_note(&song[i], speed, pitch);
	}
};
void play_note(const PlayingNote* note, int speed, int pitch) {
	int i;

	long total_duration = (long)(80000.0 * pow(0.5, note->duration + speed));

	if (note->is_rest) {
		for (int z = 0; z < (int)(total_duration/50000); ++ z)
		{
			
			waitmus(50000);
		}
		waitmus(total_duration % 50000); 
		} else {
		double freq = 220.0 * pow(2.0, ((double)note->note + 12.0 * (note->octave - 4 + pitch)) / 12.0);
		int TH = (int)(50000.0 / freq);
		
		int k = (int)(total_duration / (2 * TH));

		for (i = 0; i < k; i++) {
			SET_BIT(PORTB, 3);
			waitmus(TH);
			CLR_BIT(PORTB, 3);
			waitmus(TH);
		}
	}
}


extern const PlayingNote debug[] = {
	{Ee, W, 0, 5},
	{Ee, W, 0, 5},
	{Ee, W, 0, 5},
	{Ee, W, 0, 5},
	{Ee, W, 1, 5},
	{Ee, W, 1, 5},
	{Ee, W, 1, 5},
	{Ee, W, 1, 5},
	{B, H, 0, 5},
	{B, H, 0, 5},
	{B, H, 0, 5},
	{B, H, 0, 5},
	{Ee, W, 0, 5},
	{B, H, 0, 5},
// 		{Ee, W, 0, 5},
// 		{B, H, 0, 5}
// 		{Ds, W, 0, 5},
// 		{Ds, H, 1, 5},
// 	{Ds, W, 0, 5},
// 	{Ds, W, 1, 5},
// 	{Ds, W, 0, 5},
// 	{Ds, W, 1, 5}
};
extern const int debug_length = sizeof(debug)/ sizeof(debug[0]);


extern const PlayingNote jump[] = {
	{D, H, 0, 4},
	{B, H, 0, 4},
};

extern const PlayingNote get_coin[] = {
	{G, H, 0, 5},
	{G, H, 0, 5},
};

extern const PlayingNote die[] = {
	{A, H, 0, 5},
	{A, H, 0, 4},
	{A, H, 0, 3},
	{A, H, 0, 2},
};