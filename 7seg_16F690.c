/*
 * File:   main.c
 * Author: danir
 *
 * Created on 9 de febrero de 2024, 8:21
 */

/*
 Table:
 * 0 -> 0xC0
 * 1 -> 0xF9
 * 2 -> 0xA4
 * 3 -> 0xB0
 * 4 -> 0x99
 * 5 -> 0x92
 * 6 -> 0x82
 * 7 -> 0xF8
 * 8 -> 0x80
 * 9 -> 0x98
 */

// PIC16F690 Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = INTRCIO   // Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA4/OSC2/CLKOUT pin, I/O function on RA5/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select bit (MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown-out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.
#include <xc.h>
#define _XTAL_FREQ 4000000

char P1;
char nume = 0;
char estat = 0;

char llist[]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x98,0x98};

void main(void) {
    TRISC=0; //tot sortides
    TRISB=0x80; //RB7 entrada
    ANSEL=0; //res analogic
    ANSELH=0; //res analogic
    PORTC=0xC0;
    
    while(1){
        
        P1 = PORTBbits.RB7;
        __delay_ms(125);
        
        if (P1 == 1 && estat == 0){
            nume++;
        }else if (P1 == 1 && estat == 1){
            nume--;
        }else if (nume == 9){
            estat = 1;
        }else if (nume == 0){
            estat=0;
        }else if (estat > 1){
            estat=1;
        }
        
        if (P1 == 1){
            PORTC=llist[nume];
        }
    
        __delay_ms(50);
    }
}
