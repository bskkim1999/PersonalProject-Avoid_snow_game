/*
 * main.h
 *
 * Created: 2024-09-15(일) 오후 11:08:42
 *  Author: step
 */ 


#ifndef MAIN_H_
#define MAIN_H_

#define F_CPU 16000000UL
#define piezo_pin 5
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "include/UART0.h"
#include "include/LCD.h"
#include "include/PiezoSpeaker.h"


extern FILE OUTPUT;
extern FILE INPUT;

extern volatile unsigned long timer0_millis;
extern volatile int timer0_micros;

//int status[20]={0};
extern int count_character_moving;
extern int case_even;
extern int case_odd;
extern int dangerous_flag;
extern int gameover_flag;
extern unsigned char lcd_screen_data_col_0_row_0;
extern unsigned char lcd_screen_data_col_0_row_1;

extern unsigned char lcd_screen_data[2][16];

extern unsigned char character_code[8];
extern unsigned char gameover_emoji[8];



#endif /* MAIN_H_ */