

#include <xc.h>
#include <stdint.h>
#include "mcc_generated_files/mcc.h"
#include "LCD_I2C_16X2.h"
#include "I2C.h"

void PCF8574_Write(uint8_t byte){
   
//    I2C_Master_Write(0x27);
  
    I2C_Master_Write(byte);
    
}

//Enviar un byte de comando al controlador hitachi HD44780
void LCD_I2C_WriteCommand(uint8_t command){ 
    uint8_t highnibble;
    uint8_t lownibble;
    
    highnibble = (command & 0xF0) | BACKLIGHT;
    lownibble  = (uint8_t)(((command & 0x0F)<<4)| BACKLIGHT);
    
    PCF8574_Write(highnibble | PIN_EN); //habilito EN 
    __delay_us(20);
    PCF8574_Write(highnibble); //deshabilito EN
    __delay_us(20);

    PCF8574_Write(lownibble | PIN_EN); //habilito EN 
    __delay_us(20);
    PCF8574_Write(lownibble); //deshabilito EN
    __delay_us(20);
}

//Enviar un byte de datos al controlador hitachi HD44780
void LCD_I2C_WriteData(uint8_t data){ 
    uint8_t highnibble;
    uint8_t lownibble;
    //backligth siempre activado
    highnibble = (data & 0xF0) | BACKLIGHT;
    lownibble  = (uint8_t)(((data & 0x0F)<<4)| BACKLIGHT);
    
    PCF8574_Write(highnibble | PIN_EN | PIN_RS); //habilito EN 
    __delay_us(20);
    PCF8574_Write(highnibble | PIN_RS); //deshabilito EN
    __delay_us(20);

  
    PCF8574_Write(lownibble | PIN_EN | PIN_RS); //habilito EN 
    __delay_us(20);
    PCF8574_Write(lownibble | PIN_RS); //deshabilito EN
    __delay_us(20);
}

void LCD_I2C_Init(void){

    I2C_Master_Init(100000);
    
    PCF8574_Write(0x00);
    __delay_ms(1000);

    //MANDO 3 VECES ESTE DATO
    PCF8574_Write(0x30); 
    __delay_us(20);
    PCF8574_Write(0x34);    
    __delay_us(20);
    PCF8574_Write(0x30);     
    __delay_ms(5);
    
    PCF8574_Write(0x30); 
    __delay_us(20);
    PCF8574_Write(0x34);   
    __delay_us(20);
    PCF8574_Write(0x30);

    __delay_ms(5);
    
    PCF8574_Write(0x30);
    __delay_us(20);
    PCF8574_Write(0x34);  
    __delay_us(20);
    PCF8574_Write(0x30);
    
    __delay_us(250);
    
    
    PCF8574_Write(0x20);  
    __delay_us(20);
    PCF8574_Write(0x24);  
    __delay_us(20);
    PCF8574_Write(0x20); 
    
    __delay_us(75);

    PCF8574_Write(0x20);  
    __delay_us(20);
    PCF8574_Write(0x24);  
    __delay_us(20);
    PCF8574_Write(0x20); 
    
    __delay_us(75);
    
    PCF8574_Write(0x80);  
    __delay_us(20);
    PCF8574_Write(0x84);  
    __delay_us(20);
    PCF8574_Write(0x80); 
    
    __delay_us(75); 
    
    
    PCF8574_Write(0x00); 
    __delay_us(20);
    PCF8574_Write(0x04); 
    __delay_us(20);
    PCF8574_Write(0x00); 
    
     __delay_us(75);
 
    
    PCF8574_Write(0xC0); 
    __delay_us(20);
    PCF8574_Write(0xC4); 
    __delay_us(20);
    PCF8574_Write(0xC0); 
    
     __delay_us(75);
 
    
    PCF8574_Write(0x00); 
    __delay_us(20);
    PCF8574_Write(0x04); 
    __delay_us(20);
    PCF8574_Write(0x00);

     __delay_us(75);
 
    
    PCF8574_Write(0x10); 
    __delay_us(20);
    PCF8574_Write(0x14);  
    __delay_us(20);
    PCF8574_Write(0x10); 
    
     __delay_ms(2);
 
      
    
    PCF8574_Write(0x00); 
    __delay_us(02);
    PCF8574_Write(0x04);   
    __delay_us(20);
    PCF8574_Write(0x00); 
     
     __delay_us(75);
 
    PCF8574_Write(0x60); 
    __delay_us(02);
    PCF8574_Write(0x64);
    __delay_us(20);
    PCF8574_Write(0x60);

     __delay_us(75);
   
    PCF8574_Write(0x00); 
    __delay_us(20);
    PCF8574_Write(0x04); 
    __delay_us(20);
    PCF8574_Write(0x00);
    
    __delay_us(75);
    
    PCF8574_Write(0x20); 
    __delay_us(20);
    PCF8574_Write(0x24); 
    __delay_us(20);
    PCF8574_Write(0x20);
    
    __delay_us(75);
    
    LCD_I2C_ClearText();  
}

// Limpiar el texto de la pantalla
void LCD_I2C_ClearText(){
  LCD_I2C_WriteCommand(DISPLAY_CLEAR);
  __delay_ms(5);
}

//TEXTO
void LCD_I2C_WriteText(uint8_t row, uint8_t col, char* string){
    //row -> 0,1,2,3        col -> 0,1,2,3,4,5,6,7
    switch (row) {
        case 0: col = col + 0x80;break; // operacion para agregar ala fila 0 su columna "x"
        case 1: col = col + 0xC0;break; // operacion para agregar ala fila 1 su columna "x"
        case 2: col = col + 0x94;break; // operacion para agregar ala fila 2 su columna "x"
        case 3: col = col + 0xD4;break; // operacion para agregar ala fila 3 su columna "x"
        default:col = col + 0x80;break; // fila 0 si ingresa un valor que no es del 0 al 3
    }

    LCD_I2C_WriteCommand(col);
    //Funcion para mandar strings sin saber el tama�o de la cadena
    //while(*string != '\0')
    while (*string)
        LCD_I2C_WriteData(*string++);
}













