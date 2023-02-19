#include "main.h"

#include <stdio.h>
#include <string.h> //para usar fun�oes de string deve se adicionar este header
#include <stdlib.h>

#define _XTAL_FREQ 20000000

int count = 0;

////////////////////////////////////////////////variaveis globais///////////////////////////////////////////////////////////
char caracter;
short int flag_interrupcao = 0;
///////////////////////////////////////////////////interrup��o//////////////////////////////////////////////////////////////

void __interrupt() isr()//vetor de interrup��o
 {
    caracter = RCREG;
    flag_interrupcao = 1;
    RCIF = 0;//  limpa flag de interrup��o de recep��o
 }
 
/////////////////////////////////fun�oes usadas pela uart //////////////////////////////////////////////////////
void inicializa_RS232(long velocidade,int modo)
{////por padr�o � usado o modo 8 bits e sem paridade, mas se necessario ajuste aqui a configura��o desejada.
    //verifique datasheet para ver a porcentagem de erro e se a velocidade � possivel para o cristal utilizado.
    RCSTA = 0X90;//habilita porta serial,recep��o de 8 bit em modo continuo,assincrono.
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
    RCIE = 1;//habilita interrup��o de recep��o
    TXIE = 0;//deixa interrup��o de transmiss�o desligado(pois corre se o risco de ter uma interrup��o escrita e leitura ao mesmo tempo)
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
    while(indice < tamanho ) ///veja que o programa pode travar se aqui n�o tiver as duas aspas
    {
        escreve(frase[indice]);
        indice++;
    }
}
//////////////////////////////////////////////////////Rotina principal///////////////////////////////////////////////////////////////

void main(void) {
    
    TRISB = 0b11111111;//configura portB  B1 (pino RX) como entrada
    PORTB = 0b00000000;  // limpar as portas que est�o configuradas como saidas
    
    inicializa_RS232(9600,1);//modo de alta velocidade
    
    PEIE = 1;//habilita interrup��o de perifericos do pic
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

