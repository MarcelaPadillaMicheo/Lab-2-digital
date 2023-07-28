#include <stdint.h>
#include <xc.h>
#include "USART.h"
#define _XTAL_FREQ  8000000

void USART_INIT(uint16_t BAUD){
    unsigned char n;                //pag. 167 datasheet
    n = ((_XTAL_FREQ/BAUD)/4) -1;   //207
    
    TXSTAbits.SYNC = 0;         // Comunicación ascincrona (full-duplex)
    TXSTAbits.BRGH = 1;         // Baud rate de alta velocidad 
    BAUDCTLbits.BRG16 = 1;      // 16-bits para generar el baud rate
    
    SPBRG = n;
    SPBRGH = 0;                 // Baud rate 9600, error 0.16%
    
    RCSTAbits.SPEN = 1;         // Habilitamos comunicación
    TXSTAbits.TX9 = 0;          // Utilizamos solo 8 bits
    RCSTAbits.RX9 = 0;
    TXSTAbits.TXEN = 1;         // Habilitamos transmisor
    RCSTAbits.CREN = 1;         // Habilitamos receptor
}
void USART_CHAR(char d){
    while(TXSTAbits.TRMT == 0); //Envio de caracter por caracter
        TXREG = d;
}
void USART_WRITE(char *c){      //Envio de multiples caracteres
    while(*c != '\0'){          //usando el puntero de la variable
        USART_CHAR(*c);
        c++;
    }
}
char USART_READ(){
    if(PIR1bits.RCIF == 1){     //Chequeamos si recivimos un dato
        return RCREG;
    }
    __delay_ms(100);
}
