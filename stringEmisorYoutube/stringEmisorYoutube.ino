/*
  Capitulo 46 de Arduino desde cero en Español.
  Programa que envia mensaje a traves del modulo emisor RF de 433 Mhz cada
  un segundo.
  Requiere instalar libreria RadioHead.h
  Autor: bitwiseAr  
*/

//// Programa 1 lado Emisor ////

#include <RH_ASK.h>   // incluye libreria RadioHead.h
#include <SPI.h>    // incluye libreria SPI necesaria por RadioHead.h
 
RH_ASK rf_driver;   // crea objeto para modulacion por ASK
 
void setup(){
  
    rf_driver.init();   // inicializa objeto con valores por defecto
    Serial.begin(9600);
}
 
void loop(){
  Serial.println("entró");
    const char *msg = "Hola desde lejos!";  // puntero de mensaje a emitir
    rf_driver.send((uint8_t *)msg, strlen(msg));// funcion para envio del mensaje
    Serial.println("envió");
    rf_driver.waitPacketSent();     // espera al envio correcto
    Serial.println("confirmó");
    delay(1000);        // demora de 1 segundo entre envios
}
