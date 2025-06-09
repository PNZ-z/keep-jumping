/*
 * CFile1.c
 *
 * Created: 2025/4/27 15:36:42
 *  Author: ucirv
 */ 
#ifndef _LCD_H
#define _LCD_H
#include <stdint.h>
void lcd_init(void);

void lcd_clr(void);

void lcd_pos(unsigned char r, unsigned char c);

void lcd_put(char c);

void lcd_puts1(const char *s);

void lcd_puts2(const char *s);
void lcd_create_custom_char(uint8_t index, const uint8_t *pattern);

#endif /* _LCD_H */