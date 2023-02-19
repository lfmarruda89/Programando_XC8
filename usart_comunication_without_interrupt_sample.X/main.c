#include "main.h"
#include <string.h>

#define _XTAL_FREQ 20000000

void usart_printf(const char frase[])
{
    for (int i = 0; i < strlen(frase); i++ )
    {
        TXIF = 0;
        TXREG = frase[i];
        while(TXIF == 0);
    }
}

void main(void) {
    
    TRISC = 0b11011111;
    
    char caracter;
    
    TXSTA1bits.TXEN = 1; // HABILITA TRANSMISSAO
    TXSTA1bits.BRGH = 1; // HIGH SPEED
    
    RCSTA1bits.SPEN = 1; // HABILITA SERIAL
    RCSTA1bits.CREN = 1; // HABILITAR RECEPÇÃO
    
    BAUDCONbits.BRG16 = 0; // UTILIZA SPBRG
    
    SPBRG = (int) (((_XTAL_FREQ/9600)/16)-1);
    
    usart_printf("Ola mundo! \n\r");
    usart_printf("Digite algo? \n\r");
    
    while(1)
    {
        
        if (RCIF)
        {
            caracter = RCREG;
            
            usart_printf(" \n\r caracter digitado :");
            
            TXIF = 0;
            TXREG = caracter;
            while(TXIF==0);
            
            RCIF = 0;
        }
    }
}

