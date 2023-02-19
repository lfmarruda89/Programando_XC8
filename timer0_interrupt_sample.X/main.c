#include "main.h"

#define _XTAL_FREQ 20000000


//contador = fclk / (4* presc*256*fcontagem);
// contador = 200000000 / (4 * 256 * 256 * 1) = 76,2

int count = 0;

void __interrupt() isr(void){
    
    if (INTCONbits.TMR0IF){
        INTCONbits.TMR0IF = 0;
        count++;
        if (count == 76){
            LATBbits.LATB7 = ~PORTBbits.RB7;
            count = 0;
        }
    }

}


void main(void) {
    
    TRISB = 0b01111111; // pino B7 saida 
    
    INTCONbits.GIE = 1; // ativar as interrupções
    INTCONbits.TMR0IE = 1; // ativar interrupções Timer0
    INTCONbits.TMR0IF = 0; // resetar flag interrupção timer0
    
    T0CONbits.TMR0ON =1 ; // ativar Timer0
    T0CONbits.T0CS = 0;   // instrução interna de clock
    T0CONbits.T0SE = 0;   // contagem de low-to-high
    T0CONbits.PSA = 0;    // utiliza prescaler 
    T0CONbits.T0PS = 0b111; // prescaler 256
    
    while(1){
        
    }
}

