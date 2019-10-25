#include<Keypad.h> //libreria para usar el teclado
#include <VirtualWire.h> //libreria para usar modulo 433

const byte filas = 4; //filas del teclado
const byte columnas = 4;//columnas del teclado
byte pinesF[filas] = {9, 11, 10, 8};//conectar pines de las filas
byte pinesC[columnas] = {7, 6, 5, 4}; //conectar pines de las columnas

char teclas[filas][columnas] = {

  {'1', '2', '3', 'a'},
  {'4', '5', '6', 'b'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'd'}
};

Keypad teclado = Keypad(makeKeymap(teclas), pinesF, pinesC, filas, columnas);

char tecla ;


#include <Wire.h> //libreria para pantalla lcd
#include <LiquidCrystal_I2C.h> //libreria para pantalla lcd 
// Constructor de la librería de LCD 16x2
// Aqui se configuran los pines asignados a la pantalla del PCF8574
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
const int button=13;
const int option=A1;

void setup()
{
  Serial.begin(9600);
  pinMode(button, INPUT);
  pinMode(option, INPUT);
  // virtual wire
  vw_set_tx_pin(12); // pin para modulo emisor ATAD
  vw_setup(8000); // bps

  //pantalla
  printScreen("Proyecto Final", "Telco 2019");
}

void loop()
{
  if (digitalRead(button)==HIGH){
    Serial.println("Alto");
  }else{
    Serial.println("BAJO");
  }
  if (digitalRead(option)==HIGH){
    Serial.println("Paralelo");
  }else{
    Serial.println("Serial");
  }
  int i = 0;
  String digitos = "";
  printScreen("Esperando datos...", "Ingresar 2 digitos");
  Serial.println("Ingresar 2 digitos");
  while (i < 2) {
    if (tecla = teclado.getKey()) {
      i++;
      digitos = digitos + tecla;
      Serial.println("dats a enviar: " + digitos);

    }
  }
  Serial.println("procesando");
  while(digitalRead(button)==LOW){
    Serial.print("... ");
  }
  sendString(digitos, true); 
  delay(100);
  
  printScreen("Enviando...", digitos);
  printScreen("Enviado!", digitos);
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

void printScreen(String text1, String text2){
  //pantalla
  // Indicar a la libreria que tenemos conectada una pantalla de 16x2
  lcd.begin(16, 2);
  // Mover el cursor a la primera posición de la pantalla (0, 0)
  lcd.home ();
  lcd.print(text1);
  // Mover el cursor a la segunda linea (1) primera columna
  lcd.setCursor ( 0, 1 );
  // Imprimir otra cadena en esta posicion
  lcd.print(text2);
  // Esperar un segundo
  delay(1000);
}
