/* 
 * File:   PRCT7.c
 * Author: diego
 *
 * Created on 8 de abril de 2022, 08:14 AM
 */

#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <stdint.h>
#include <stdlib.h>
#define _XTAL_FREQ 1000000
int bandera = 0;
int valor = 0;
int centena = 0;
int decena = 0;
int unidad = 0;
int display[10] = {0b10111111, 0b10000110, 0b11011011, 0b11001111, 0b11100110, 0b11101101, 0b11111101, 0b10000111, 0b11111111, 0b11101111};

/*
 * 
 */
void __interrupt() intr (void){

   if (INTCONbits.T0IF){
            TMR0 = 252;
            INTCONbits.T0IF = 0;
            PORTDbits.RD0 = 0;
            PORTDbits.RD1 = 0;
            PORTDbits.RD2 = 0;
    
            if (bandera == 0){
                PORTDbits.RD0 = 1;
                PORTC = display[unidad];
                bandera = 1;}
            else if (bandera == 1){
                PORTDbits.RD1 = 1;
                PORTC = display[decena];
                bandera = 2;}
            else if (bandera == 2){
                PORTDbits.RD2 = 1;
                PORTC = display[centena];
                bandera = 0;}
    }
      
}
void setup(void){
    ANSEL = 0;
    ANSELH = 0;               // I/O digitales
    
    OSCCONbits.IRCF = 0b0100; 
    OSCCONbits.SCS = 1;       // Oscilador interno
    
    
    TRISC = 0;     // RC como salida
    TRISDbits.TRISD0 = 0;
    TRISDbits.TRISD1 = 0;
    TRISDbits.TRISD2 = 0;
    INTCONbits.GIE = 1;
    PORTB = 0;
    
    OPTION_REGbits.T0CS = 0;
    OPTION_REGbits.PSA = 0;
    OPTION_REGbits.PS2 = 1;
    OPTION_REGbits.PS1 = 1;
    OPTION_REGbits.PS0 = 0;
    INTCONbits.T0IF = 0;
    INTCONbits.T0IE = 1;
    TMR0 = 252; //2ms       
    
    centena = valor/100;
    decena = (valor -(centena*100))/10;
    unidad = ((valor -(centena*100)) -(decena*10));

    return;
}
void main(void) {
    PORTB = 0;
    PORTD = 0;
    centena = 0;
    decena = 0;
    unidad = 0;
    valor = 420;
    setup();
    while(1)
    {
    }
   return;
}

