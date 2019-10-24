#include<Keypad.h>
#include <VirtualWire.h>

const byte filas = 4;
const byte columnas = 4;
byte pinesF[filas] = {9, 11, 10, 8};
byte pinesC[columnas] = {7, 6, 5, 4};

char teclas[filas][columnas] = {

  {'1', '2', '3', 'a'},
  {'4', '5', '6', 'b'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

Keypad teclado = Keypad(makeKeymap(teclas), pinesF, pinesC, filas, columnas);

char tecla ;


#include <Wire.h>
#include <LiquidCrystal_I2C.h> 
// Constructor de la librería de LCD 16x2
// Aqui se configuran los pines asignados a la pantalla del PCF8574
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);


void setup()
{
  Serial.begin(9600);

  // virtual wire
  vw_set_tx_pin(12); // pin
  vw_setup(8000); // bps

  //pantalla
  // Indicar a la libreria que tenemos conectada una pantalla de 16x2
  lcd.begin(16, 2);
  // Mover el cursor a la primera posición de la pantalla (0, 0)
  lcd.home ();
  // Imprimir "Hola Mundo" en la primera linea
  lcd.print("Proyecto Final");
  // Mover el cursor a la segunda linea (1) primera columna
  lcd.setCursor ( 0, 1 );
  // Imprimir otra cadena en esta posicion
  lcd.print("Telco 2019");
  // Esperar un segundo
  delay(1000);
}

void loop()
{
  int i = 0;
  String digitos = "";
  //pantalla
  // Indicar a la libreria que tenemos conectada una pantalla de 16x2
  lcd.begin(16, 2);
  // Mover el cursor a la primera posición de la pantalla (0, 0)
  lcd.home ();
  // Imprimir "Hola Mundo" en la primera linea
  lcd.print("Preparado");
  // Mover el cursor a la segunda linea (1) primera columna
  lcd.setCursor ( 0, 1 );
  // Imprimir otra cadena en esta posicion
  lcd.print("Ingrese 2 digitos");
  // Esperar un segundo
  delay(1000);
  Serial.println("INGRESE 2 digitos");
  while (i < 2) {
    if (tecla = teclado.getKey()) {
      i++;
      digitos = digitos + tecla;
      Serial.println("dats a enviar: " + digitos);

    }
  }
  Serial.println("procesando");
  sendString(digitos, true); 
  delay(100);
  
  //pantalla
  // Indicar a la libreria que tenemos conectada una pantalla de 16x2
  lcd.begin(16, 2);
  // Mover el cursor a la primera posición de la pantalla (0, 0)
  lcd.home ();
  // Imprimir "Hola Mundo" en la primera linea
  lcd.print("Enviando...");
  // Mover el cursor a la segunda linea (1) primera columna
  lcd.setCursor ( 0, 1 );
  // Imprimir otra cadena en esta posicion
  lcd.print(digitos);
  // Esperar un segundo
  delay(1000);
}

void sendString(String message, bool wait)
{
  byte messageLength = message.length() + 1; 

  // convert string to char array
  char charBuffer[messageLength]; 
  message.toCharArray(charBuffer, messageLength);

  vw_send((uint8_t *)charBuffer, messageLength); 

  if (wait) vw_wait_tx(); 

  Serial.println("Enviado: " + message); 
}
