#include "main.h"

#define _XTAL_FREQ 20000000

void __interrupt() isr(void){
    
    if (INTCONbits.INT0IF){
        INTCONbits.INT0IF = 0;
        LATBbits.LATB7 = ~PORTBbits.RB7; // invertendo o estado do led
    }
}


void main(void) {
    
    TRISB = 0b01111111; // RB7 saida RB0 entrada
    
    INTCONbits.GIE = 1; // ativar interrupções
    INTCONbits.INT0IE = 1; // ativiar interrupção INT0
    INTCONbits.INT0IF = 0; // reset de flag
    
    INTCON2bits.RBPU = 1; // desatirvar PULL-UPS
    INTCON2bits.INTEDG0 = 1; // rising edge 
    
    while(1){
        
    }
}

