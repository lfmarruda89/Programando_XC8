#include "main.h"

#define _XTAL_FREQ 20000000

int value_ADC = 0;


void main(void) {
    
    // io's
    TRISB = 0b01111111; // colocando o pino B7 como saída 
    TRISA = 0b11111111; // colocando o pino AN0 como entrada 
    
    // ADC
    ADCON0bits.CHS = 0b0000; // canal AN0
    ADCON0bits.ADON = 1; // ativar o conversor ADC
    
    ADCON1bits.VCFG = 0b00; // configurando as tensões de referência
    ADCON1bits.PCFG = 0b1110; // colocando AN0 como analógico
    
    ADCON2bits.ADFM = 1; // alinhado a direita
    ADCON2bits.ACQT = 0b101; // 12 Tad
    ADCON2bits.ADCS = 0b010; // Fosc/32
    
    while(1){
        
        // leitura analógica
        ADCON0bits.GO = 1; // entra em conversão
        while(ADCON0bits.GO); // aguarda processo de conversão
        value_ADC = (((int) ADRESH)<<8) | (ADRESL);
        
        if (value_ADC > 512){
            LATBbits.LATB7 = 1; // coloca em nivel alto
            __delay_ms(100); // esperar 100 milessegundos
            LATBbits.LATB7 = 0; // coloca em nivel baixo
            __delay_ms(100); // esperar 100 milessegundos
        }
        __delay_ms(100); // esperar 100 milessegundos
    }
    
    return;
}
