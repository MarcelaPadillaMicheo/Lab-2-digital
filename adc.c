#include <stdint.h>
#include <xc.h>
#include "ADC.h"
#define _XTAL_FREQ  8000000

uint8_t CENTENA(unsigned char c){    //se separa el bit mas significativo   
    c = (uint8_t)((c*1.9607)/100);
    return c;
}
uint8_t DECENA(unsigned char c){         //se separa el bit medio significativo
    c = (uint8_t)((c*1.9607) - CENTENA(c)*100)/10;
    return c;
}

uint8_t UNIDAD(unsigned char c){         // se separa el bit menos significativo
    c = (uint8_t)((c*1.9607) - CENTENA(c)*100 - DECENA(c)*10);
    return c;
}

void OSCILLATOR(uint8_t f){         //Escogo que frecuencia quiero para el oscilador
    OSCCONbits.SCS = 1;
    
    switch(f){
        case(1):
            OSCCONbits.IRCF2 =1;        //8M Hz    
            OSCCONbits.IRCF1 =1;
            OSCCONbits.IRCF0 =1;
            break;
            
        case(2):
            OSCCONbits.IRCF2 =1;        //4M Hz    
            OSCCONbits.IRCF1 =1;
            OSCCONbits.IRCF0 =0;
            break;
            
        case(3):
            OSCCONbits.IRCF2 =1;        //2M Hz    
            OSCCONbits.IRCF1 =0;
            OSCCONbits.IRCF0 =1;
            break;
            
        case(4):
            OSCCONbits.IRCF2 =1;        //1M Hz    
            OSCCONbits.IRCF1 =0;
            OSCCONbits.IRCF0 =0;
            break;
            
        case(5):
            OSCCONbits.IRCF2 =0;        //500k Hz    
            OSCCONbits.IRCF1 =1;
            OSCCONbits.IRCF0 =1;
            break;
        
        case(6):
            OSCCONbits.IRCF2 =0;        //250k Hz    
            OSCCONbits.IRCF1 =1;
            OSCCONbits.IRCF0 =0;
            break;
        
        case(7):
            OSCCONbits.IRCF2 =0;        //125k Hz    
            OSCCONbits.IRCF1 =0;
            OSCCONbits.IRCF0 =1;
            break;
        
        case(8):
            OSCCONbits.IRCF2 =0;        //31k Hz    
            OSCCONbits.IRCF1 =0;
            OSCCONbits.IRCF0 =0;
            break;
        
        default:
            OSCCONbits.IRCF2 =1;        //4M Hz    
            OSCCONbits.IRCF1 =1;
            OSCCONbits.IRCF0 =0;
            break;
    }
    return;
}


void ADC_INIT(int c){               //Seleccion de canales
    switch(c){
        case 0:
            ADCON0bits.CHS3 = 0;    //canal 0
            ADCON0bits.CHS2 = 0;
            ADCON0bits.CHS1 = 0;
            ADCON0bits.CHS0 = 0;
            break;
            
        case 1:
            ADCON0bits.CHS3 = 0;    //canal 1
            ADCON0bits.CHS2 = 0;
            ADCON0bits.CHS1 = 0;
            ADCON0bits.CHS0 = 1;
            break;
            
        case 2:
            ADCON0bits.CHS3 = 0;    //canal 2
            ADCON0bits.CHS2 = 0;
            ADCON0bits.CHS1 = 1;
            ADCON0bits.CHS0 = 0;
            break;
            
        case 3:
            ADCON0bits.CHS3 = 0;    //canal 3
            ADCON0bits.CHS2 = 0;
            ADCON0bits.CHS1 = 1;
            ADCON0bits.CHS0 = 1;
            break;
            
        case 4:
            ADCON0bits.CHS3 = 0;    //canal 4
            ADCON0bits.CHS2 = 1;
            ADCON0bits.CHS1 = 0;
            ADCON0bits.CHS0 = 0;
            break;
            
        case 5:
            ADCON0bits.CHS3 = 0;    //canal 5
            ADCON0bits.CHS2 = 1;
            ADCON0bits.CHS1 = 0;
            ADCON0bits.CHS0 = 1;
            break;
            
        case 6:
            ADCON0bits.CHS3 = 0;    //canal 6
            ADCON0bits.CHS2 = 1;
            ADCON0bits.CHS1 = 1;
            ADCON0bits.CHS0 = 0;
            break;
            
        case 7:
            ADCON0bits.CHS3 = 0;    //canal 7
            ADCON0bits.CHS2 = 1;
            ADCON0bits.CHS1 = 1;
            ADCON0bits.CHS0 = 1;
            break;
            
        case 8:
            ADCON0bits.CHS3 = 1;    //canal 8
            ADCON0bits.CHS2 = 0;
            ADCON0bits.CHS1 = 0;
            ADCON0bits.CHS0 = 0;
            break;
            
        case 9:
            ADCON0bits.CHS3 = 1;    //canal 9
            ADCON0bits.CHS2 = 0;
            ADCON0bits.CHS1 = 0;
            ADCON0bits.CHS0 = 1;
            break;
            
        case 10:
            ADCON0bits.CHS3 = 1;    //canal 10
            ADCON0bits.CHS2 = 0;
            ADCON0bits.CHS1 = 1;
            ADCON0bits.CHS0 = 0;
            break;
            
        case 11:
            ADCON0bits.CHS3 = 1;    //canal 11
            ADCON0bits.CHS2 = 0;
            ADCON0bits.CHS1 = 1;
            ADCON0bits.CHS0 = 1;
            break;
            
        case 12:
            ADCON0bits.CHS3 = 1;    //canal 12
            ADCON0bits.CHS2 = 1;
            ADCON0bits.CHS1 = 0;
            ADCON0bits.CHS0 = 0;
            break;
            
        case 13:
            ADCON0bits.CHS3 = 1;    //canal 13
            ADCON0bits.CHS2 = 1;
            ADCON0bits.CHS1 = 0;
            ADCON0bits.CHS0 = 1;
            break;
            
        default:
            ADCON0bits.CHS3 = 0;    //canal 0
            ADCON0bits.CHS2 = 0;
            ADCON0bits.CHS1 = 0;
            ADCON0bits.CHS0 = 0;
            break;
    }
    return;
}
int ADC_READ(){                     //funcion que lee el potenciometro
    //ADCON0bits.GO = 1;
    //while(ADCON0bits.GO == 1){
        //if (ADCON0bits.GO == 0){
            return ADRESH;           
            //ADCON0bits.GO = 1;
        //}
    //}
    //__delay_us(1);
    //return;
}

void ADC_CHANGE_CHANNEL(int c, int b){      //cambio de canales, si utilizamos
    ADCON0bits.GO = 1;                      //varios
    while(ADCON0bits.GO == 1){
        if(ADCON0bits.GO == 0){
            if(ADCON0bits.CHS == c){
                ADCON0bits.CHS = b;   
            }else if(ADCON0bits.CHS == b){
                ADCON0bits.CHS = c;
            }
            ADCON0bits.GO = 1;
        }
    }
    return;
}

int ADC_GET_CHANNEL(){          //nos dice en que canal estamos
    return ADCON0bits.CHS;
}
