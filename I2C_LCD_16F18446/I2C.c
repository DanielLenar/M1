


#include <xc.h>
#include <stdint.h>
#include "mcc_generated_files/mcc.h"
#include "I2C.h"
// Para realizar la libreria del MODULO I2C me base de este video: https://www.youtube.com/watch?v=uAR0lRPnKVA&list=PLmX2_OhrubDChbULG3e9M6o0AQsyAJNwP&index=74
void I2C_Master_Init(uint32_t clock){
       
}

//Garantizar que la situacion para poder continuar con la escritura o lectura de datos este presente y correcta
//mientras el buffer esta lleno esperar hasta q se vacie y bits 0-5 del registro SSPCON2
//mientras esta leyendo esperar para que escriba bit 3 del registro SSPSTAT
void I2C_Master_Wait(void){  
    
}

void I2C_Start(void){
    
}

void I2C_Stop(void){
    
}

void I2C_Repeated_Start(void){
     
}

void I2C_Master_Write(uint8_t dato){
//    I2C_Master_Wait();
//    SSPBUF = dato;      //cargamos el dato en el buffer para enviar
    char data[]={dato,0};
    i2c_writeNBytes(0x27,  data, 1);
}

uint8_t I2C_Master_Read(uint8_t ACK){
   
    
}
