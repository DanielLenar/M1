/*
 * File:   main.c
 * Author: danir
 *
 * Created on 10 de febrero de 2024, 13:27
 */

 /*Table:
 * 0 -> 0x3F
 * 1 -> 0x06
 * 2 -> 0x5B
 * 3 -> 0x4F
 * 4 -> 0x66
 * 5 -> 0x6D
 * 6 -> 0x7D
 * 7 -> 0x07
 * 8 -> 0x7F
 * 9 -> 0x6F
 */

/*Displays:
 * 1 -> 0xE0
 * 2 -> 0xD0
 * 3 -> 0xB0
 * 4 -> 0x70
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


char disp=1;

char numd1=0;
char numd2=0;
char numd3=0;
char numd4=0;

char desena;
char centenar;
char miler;

char numero[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
char display[]={0,0xE0,0xD0,0xB0,0x70};

void main(void) {
    TRISC=0;
    TRISB=0;
    ANSEL=0;
    ANSELH=0;
    PORTC=0;
    PORTB=0xFF;
    
    while (1){
        
        char i = 0;
       
        while (i < 25){
        __delay_ms(2);
        PORTB=display[3];
        PORTC=numero[numd3];
        __delay_ms(2);
        PORTB=display[2];
        PORTC=numero[numd2];
        __delay_ms(2);
        PORTB=display[1];
        PORTC=numero[numd1];
        __delay_ms(2);
        PORTB=display[4];
        PORTC=numero[numd4];
        i++;
        }
        
        if(numd1 <= 9){
        numd1++;
        }
        
        if (numd4 > 9){
            numd4=0;
            numd3=0;
            numd2=0;
            numd1=0;
        }else if (numd3 >= 9 && numd4 <= 9 && numd2 >= 9 && numd1 > 9){
            numd4++;
            numd3=0;
            numd2=0;
            numd1=0;
            
        }else if (numd2 >= 9 && numd3 <= 9 && numd1 > 9 && numd4 <= 9){
            numd2=0;
            numd1=0;
            numd3++;
            
        }else if (numd1 > 9 && numd2 <= 9 && numd4 <= 9){
            numd2++;
            numd1=0;
        }
        
    }
}
