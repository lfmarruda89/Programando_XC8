#include "main.h"

#define _XTAL_FREQ 20000000

void main(void) {
    
    // io's
    TRISB = 0b01111111; // colocando o pino B7 como saída 
    
    while(1){
        
        LATBbits.LATB7 = 1; // coloca em nivel alto
        __delay_ms(100); // esperar 100 milessegundos
        LATBbits.LATB7 = 0; // coloca em nivel baixo
        __delay_ms(100); // esperar 100 milessegundos
    
    }
    return;
}
