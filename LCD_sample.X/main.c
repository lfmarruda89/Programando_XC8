#define _XTAL_FREQ 20000000

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "main.h"
#include "lcd.h"

void main ( void ) {

    LCD lcd = { &PORTD, 2, 3, 4, 5, 6, 7}; // PORT, RS, EN, D4, D5, D6, D7

    LCD_Init(lcd);

    for ( ;; ) {

        LCD_Clear();
        LCD_Set_Cursor(0,0);
        LCD_putrs("HELLO WORLD!");

		LCD_Set_Cursor(1,0);
		for ( char c = 'A'; c <= 'P'; c++ ) { // Print characters A-P
			 LCD_putc(c);
			 for ( unsigned char i = 0; i < 30; i++ ) { // 300ms Delay
			 	__delay_ms(10);
			 }
		}
		
		for ( unsigned char i = 0; i < 100; ++i ) { // 1s Delay
		 	__delay_ms(10);
		 }

	}

    return;
}

