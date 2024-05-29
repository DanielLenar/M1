/*
 * File:   main.c
 * Author: danir
 *
 * Created on 23 de mayo de 2024, 10:43
 */

// CONFIG1
#pragma config FEXTOSC = OFF    // External Oscillator mode selection bits (EC above 8MHz; PFM set to high power)
#pragma config RSTOSC = HFINTPLL  // Power-up default value for COSC bits (HFINTOSC (1MHz))
#pragma config CLKOUTEN = OFF   // Clock Out Enable bit (CLKOUT function is disabled; i/o or oscillator function on OSC2)
#pragma config CSWEN = OFF       // Clock Switch Enable bit (Writing to NOSC and NDIV is allowed)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (FSCM timer disabled)

// CONFIG2
#pragma config MCLRE = ON       // Master Clear Enable bit (MCLR pin is Master Clear function)
#pragma config PWRTS = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config LPBOREN = OFF    // Low-Power BOR enable bit (ULPBOR disabled)
#pragma config BOREN = OFF      // Brown-out reset enable bits (Brown-out reset disabled)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (VBOR) set to 2.45V)
#pragma config ZCD = OFF        // Zero-cross detect disable (Zero-cross detect circuit is disabled at POR.)
#pragma config PPS1WAY = OFF     // Peripheral Pin Select one-way control (The PPSLOCK bit can be cleared and set only once in software)
#pragma config STVREN = OFF      // Stack Overflow/Underflow Reset Enable bit (Stack Overflow or Underflow will cause a reset)
#pragma config DEBUG = OFF      // Background Debugger (Background Debugger disabled)

// CONFIG3
#pragma config WDTCPS = WDTCPS_31// WDT Period Select bits (Divider ratio 1:65536; software control of WDTPS)
#pragma config WDTE = OFF        // WDT operating mode (WDT enabled regardless of sleep; SWDTEN ignored)
#pragma config WDTCWS = WDTCWS_7// WDT Window Select bits (window always open (100%); software control; keyed access not required)
#pragma config WDTCCS = SC      // WDT input clock selector (Software Control)

// CONFIG4
#pragma config BBSIZE = BB512   // Boot Block Size Selection bits (512 words boot block size)
#pragma config BBEN = OFF       // Boot Block Enable bit (Boot Block disabled)
#pragma config SAFEN = OFF      // SAF Enable bit (SAF disabled)
#pragma config WRTAPP = OFF     // Application Block Write Protection bit (Application Block not write protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot Block not write protected)
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration Register not write protected)
#pragma config WRTD = OFF       // Data EEPROM write protection bit (Data EEPROM NOT write protected)
#pragma config WRTSAF = OFF     // Storage Area Flash Write Protection bit (SAF not write protected)
#pragma config LVP = ON         // Low Voltage Programming Enable bit (Low Voltage programming enabled. MCLR/Vpp pin function is MCLR.)

// CONFIG5
#pragma config CP = OFF  

#include <xc.h>
#define _XTAL_FREQ 16000000

uint16_t numero[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
uint16_t display[]={0,0xE0,0xD0,0xB0,0x70};

uint16_t a,c,desena,centenar,miler,digit,imprim;
char i;

void main(void) {
    TRISAbits.TRISA2 = 0;
    TRISB = 0;
    TRISC = 0;
    ANSELB = 0;
    ANSELC = 0;
    ADCON0bits.FM = 1;
    ADCON0bits.CS = 1;
    ADPCH = 0b000101;
    TRISAbits.TRISA5 = 1;
    ANSELAbits.ANSA5 = 1;
    ADCON0bits.ON = 1;
    
    while(1){
    ADCON0bits.GO = 1;
    while (ADCON0bits.GO);
    
    imprim = ((ADRESH<<8)+ADRESL);
    
       miler=imprim/1000;  //individualitzador de numeros
       a=imprim%1000;
       centenar=a/100;
       c=a%100;
       desena=c/10;
       digit=c%10;
       
       while (i < 25){
        __delay_ms(1);
        PORTB=display[4];
        PORTC=numero[miler];
        __delay_ms(1);
        PORTB=display[3];
        PORTC=numero[centenar];
        __delay_ms(1);
        PORTB=display[2];
        PORTC=numero[desena];
        __delay_ms(1);
        PORTB=display[1];
        PORTC=numero[digit];
        i++;
       }
        i=0;
    }
    
    }
    

