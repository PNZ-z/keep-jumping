/*
 * music.h
 *
 * Created: 2025/5/10 19:39:17
 *  Author: ucirv
 */ 


#ifndef MUSIC_H_
#define MUSIC_H_

typedef enum{
	A, As, B, C, Cs, D, Ds, Ee, F, Fs, G, Gs
	} Note;

typedef enum{
	W, H, Q, Ei
	}Duration;

typedef struct{
	Note note;
	Duration duration;
	int is_rest;
	int octave;
	} PlayingNote;
	
void play_song(const PlayingNote song[], int length, int speed, int pitch);
void play_note(const PlayingNote* note, int speed, int pitch);

extern const PlayingNote debug[];

extern const PlayingNote jump[];
extern const PlayingNote get_coin[];
extern const PlayingNote die[];
typedef struct {
	const PlayingNote* notes;
	int length;
	const char* name;
} Song;



#endif /* MUSIC_H_ */