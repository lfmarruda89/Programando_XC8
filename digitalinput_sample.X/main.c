#include "main.h"

#define _XTAL_FREQ 20000000

short int leitura_B6 = 0;

void main(void) {
    
    // io's
    TRISB = 0b01111111; // colocando o pino B7 como saída 
       
    while(1){
        
        //blink com leitura digital
        leitura_B6 = PORTBbits.RB6; // guardar valor de B6
        if (leitura_B6 == 0){
            LATBbits.LATB7 = 1; // coloca em nivel alto
            __delay_ms(100); // esperar 100 milessegundos
            LATBbits.LATB7 = 0; // coloca em nivel baixo
            __delay_ms(100); // esperar 100 milessegundos
        }
        __delay_ms(100); // esperar 100 milessegundos
    }
    
    return;
}
