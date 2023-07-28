/*
 * File:   main.c
 * Author: marce
 *
 * Created on July 27, 2023, 9:01 PM
 */

// Configuración del microcontrolador
#pragma config FOSC = INTRC_NOCLKOUT
#pragma config WDTE = OFF
#pragma config PWRTE = OFF
#pragma config MCLRE = OFF
#pragma config CP = OFF
#pragma config CPD = OFF
#pragma config BOREN = OFF
#pragma config IESO = OFF
#pragma config FCMEN = OFF
#pragma config LVP = OFF

#pragma config BOR4V = BOR40V
#pragma config WRT = OFF

#include <stdint.h>
#include <xc.h>
#include "LCD.h"    // Librería para controlar el LCD
#include "ADC.h"    // Librería para configurar y leer el ADC
#include "USART.h"  // Librería para comunicación USART (puerto serie)

#define _XTAL_FREQ  8000000

// Variables utilizadas
char old_pot;
uint8_t POT;
char cont;
uint8_t unidad, decena, centena;

// Declaración de funciones
void setup(void);

void main(void) {
    setup();
    while (1) {
        old_pot = POT;

        // Leer valor del potenciómetro
        if (ADCON0bits.GO == 0) {
            POT = ADC_READ();  // Leer los datos del canal 5 y guardarlos en POT
            ADCON0bits.GO = 1; // Iniciar nueva conversión
        }

        // Separar el valor del potenciómetro en centena, decena y unidad para imprimirlos después
        centena = CENTENA(POT);
        decena = DECENA(POT);
        unidad = UNIDAD(POT);

        // Convertir los valores numéricos a caracteres ASCII
        centena += 48;
        decena += 48;
        unidad += 48;

        // Leer si se recibió un carácter '+' o '-'
        cont = USART_READ();

        // Dependiendo de si es '+' o '-', incrementar o decrementar el valor del puerto PORTA
        if (cont == '+') {
            PORTA++;
        } else if (cont == '-') {
            PORTA--;
        }
        cont = 0;

        // Si el valor del potenciómetro ha cambiado desde la última vez, mostrar información en USART
        if (old_pot != POT) {
            __delay_ms(100); // Evitar que la terminal imprima todo el tiempo
            USART_WRITE("\n\r+ Aumentar contador\n\r");
            USART_WRITE("- Disminuir contador\n\r");
            USART_WRITE("Voltaje de POT: ");
            USART_CHAR(centena);
            USART_WRITE(".");
            USART_CHAR(decena);
            USART_CHAR(unidad);
            USART_WRITE("V");
            USART_WRITE("\n\r\n\r");
            __delay_ms(100);
        }

        // Limpiar el LCD y mostrar el voltaje del POT
        LCD_CLEAR8();
        LCD_XY8(1, 1);
        LCD_STRING8("POT");
        LCD_XY8(2, 1);
        LCD_CHAR8(centena);
        LCD_STRING8(".");
        LCD_CHAR8(decena);
        LCD_CHAR8(unidad);
        LCD_STRING8("V");

        // Separar el valor del contador (conectado al puerto PORTA) en centena, decena y unidad para imprimirlos después
        centena = CENTENA(PORTA);
        decena = DECENA(PORTA);
        unidad = UNIDAD(PORTA);

        // Convertir los valores numéricos a caracteres ASCII
        centena += 48;
        decena += 48;
        unidad += 48;

        // Mostrar el voltaje del contador en el LCD
        LCD_XY8(1, 10);
        LCD_STRING8("CPU:");
        LCD_XY8(2, 10);
        LCD_CHAR8(centena);
        LCD_STRING8(".");
        LCD_CHAR8(decena);
        LCD_CHAR8(unidad);
        LCD_STRING8("V");
    }
    return;
}

// Configuración inicial del microcontrolador y periféricos
void setup(void) {
    // Configuración de pines y puertos
    ANSEL = 0b00100000; // Habilitar canal 5 del ADC
    ANSELH = 0x00;
    TRISA = 0x00;
    TRISD = 0x00;
    TRISC = 0b10000000; // Configurar RX como entrada para USART
    PORTA = 0x00;
    PORTD = 0x00;
    PORTC = 0x00;

    // Configuración del oscilador a 8 MHz
    OSCILLATOR(1);

    // Configuración del ADC
    ADC_INIT(5); // Configurar el ADC para el canal 5
    ADCON1bits.VCFG0 = 0; // VDD como referencia positiva
    ADCON1bits.VCFG1 = 0; // VSS como referencia negativa
    ADCON0bits.ADCS0 = 0; // Fosc/32 como fuente de conversión del ADC
    ADCON0bits.ADCS1 = 1;
    ADCON1bits.ADFM = 0; // Justificación izquierda
    ADCON0bits.ADON = 1; // Habilitar el módulo ADC
    __delay_us(50);
    ADCON0bits.GO_nDONE = 1; // Iniciar la primera conversión del ADC

    // Inicializar variables
    POT = 0;
    cont = 0;
    unidad = 0;
    decena = 0;
    centena = 0;
    old_pot = 0;

    // Inicializar el LCD y la comunicación USART
    LCD_INIT8();
    USART_INIT(9600);

    return;
}
