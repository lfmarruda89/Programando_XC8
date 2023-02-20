#define _XTAL_FREQ 20000000

#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lcd.h"

void main ( void ) {

    LCD lcd = { &PORTD, 2, 3, 4, 5, 6, 7}; // PORT, RS, EN, D4, D5, D6, D7
    LCD_Init(lcd);

    while (1){
        
        LCD_Clear();
        LCD_Set_Cursor(0,0);
        LCD_putrs("LUIZ FERNANDO");
        
		LCD_Set_Cursor(1,0);
		for ( char c = 'A'; c <= 'P'; c++ ) { 
			 LCD_putc(c);
			 for ( unsigned char i = 0; i < 30; i++ ) { 
			 	__delay_ms(10);
			 }
		}
		for ( unsigned char i = 0; i < 100; ++i ) { 
		 	__delay_ms(10);
		 }
	}
    return;
}

