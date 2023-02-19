#include "main.h"

#include <stdio.h>
#include <string.h> //para usar funçoes de string deve se adicionar este header
#include <stdlib.h>

#define _XTAL_FREQ 20000000

int count = 0;

////////////////////////////////////////////////variaveis globais///////////////////////////////////////////////////////////
char caracter;
short int flag_interrupcao = 0;
///////////////////////////////////////////////////interrupção//////////////////////////////////////////////////////////////

void __interrupt() isr()//vetor de interrupção
 {
    caracter = RCREG;
    flag_interrupcao = 1;
    RCIF = 0;//  limpa flag de interrupção de recepção
 }
 
/////////////////////////////////funçoes usadas pela uart //////////////////////////////////////////////////////
void inicializa_RS232(long velocidade,int modo)
{////por padrão é usado o modo 8 bits e sem paridade, mas se necessario ajuste aqui a configuração desejada.
    //verifique datasheet para ver a porcentagem de erro e se a velocidade é possivel para o cristal utilizado.
    RCSTA = 0X90;//habilita porta serial,recepção de 8 bit em modo continuo,assincrono.
    int valor;
        if(modo == 1)
        {//modo = 1 ,modo alta velocidade
            TXSTA = 0X24;//modo assincrono,trasmissao 8 bits.
            valor =(int)(((_XTAL_FREQ/velocidade)-16)/16);//calculo do valor do gerador de baud rate
        }
        else
        {//modo = 0 ,modo baixa velocidade
            TXSTA = 0X20;//modo assincrono,trasmissao 8 bits.
            valor =(int)(((_XTAL_FREQ/velocidade)-64)/64);//calculo do valor do gerador de baud rate
        }
    SPBRG = valor;
    RCIE = 1;//habilita interrupção de recepção
    TXIE = 0;//deixa interrupção de transmissão desligado(pois corre se o risco de ter uma interrupção escrita e leitura ao mesmo tempo)
}
void escreve(char valor)
{
    TXIF = 0;//limpa flag que sinaliza envio completo.
    TXREG = valor;
    while(TXIF ==0);//espera enviar caracter
}
void imprime(const char frase[])
{
    char indice = 0;
    char tamanho = strlen(frase);
    while(indice < tamanho ) ///veja que o programa pode travar se aqui não tiver as duas aspas
    {
        escreve(frase[indice]);
        indice++;
    }
}
//////////////////////////////////////////////////////Rotina principal///////////////////////////////////////////////////////////////

void main(void) {
    
    TRISB = 0b11111111;//configura portB  B1 (pino RX) como entrada
    PORTB = 0b00000000;  // limpar as portas que estão configuradas como saidas
    
    inicializa_RS232(9600,1);//modo de alta velocidade
    
    PEIE = 1;//habilita interrupção de perifericos do pic
    GIE = 1; //GIE: Global Interrupt Enable bit
    imprime("Usando a serial MPlab xc8 \n\r");
    imprime("digite algo? \n\r");
    
    for(;;)
    {
        if(flag_interrupcao ==  1)
        {//tem dados para ler
            imprime(" \n\r caracter digitado :");
            escreve(caracter);
            flag_interrupcao = 0;
        }
    }
    
}

