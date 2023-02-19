#include "main.h"

#define _XTAL_FREQ 20000000
#define TMR2PRESCALE 4

short int leitura_B6 = 0;
int value_ADC = 0;
long PWM_freq = 5000;

void main(void) {
    
    // io's
    TRISB = 0b01111111; // colocando o pino B7 como saída 
    TRISA = 0b11111111; // colocando o pino AN0 como entrada 
    TRISC = 0b11111011; // colcoando o pino RC2 como saída
    
    // ADC
    ADCON0bits.CHS = 0b0000; // canal AN0
    ADCON0bits.ADON = 1; // ativar o conversor ADC
    
    ADCON1bits.VCFG = 0b00; // configurando as tensões de referência
    ADCON1bits.PCFG = 0b1110; // colocando AN0 como analógico
    
    ADCON2bits.ADFM = 1; // alinhado a direita
    ADCON2bits.ACQT = 0b101; // 12 Tad
    ADCON2bits.ADCS = 0b010; // Fosc/32
    
    // PWM
    PR2 = (_XTAL_FREQ / (PWM_freq * 4 * TMR2PRESCALE)) -1;
    CCP1CONbits.CCP1M = 0b1100; // PWM
    T2CONbits.T2CKPS = 0b01; // Prescaller 4
    T2CONbits.TMR2ON = 1; // ativar TIMER2
       
    while(1){
        
        // leitura analógica
        ADCON0bits.GO = 1; // entra em conversão
        while(ADCON0bits.GO); // aguarda processo de conversão
        value_ADC = (((int) ADRESH)<<8) | (ADRESL);
        
        // Razão Cíclica PWM proporcional ao ADC
        CCP1CONbits.DC1B0 = (value_ADC & 0b00000001);
        CCP1CONbits.DC1B1 = (value_ADC & 0b00000010) >> 1;
        CCPR1L = value_ADC >> 2;        
        
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
