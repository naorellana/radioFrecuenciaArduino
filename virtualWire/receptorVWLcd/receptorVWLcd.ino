// library
#include <VirtualWire.h>

byte message[VW_MAX_MESSAGE_LEN]; // a buffer to store the incoming messages
byte messageLength = VW_MAX_MESSAGE_LEN; // the size of the message

const int led=13;


//pantalla
#include  <Wire.h>
#include  <LiquidCrystal_I2C.h>

// Constructor de la librería de LCD 16x2
// Aqui se configuran los pines asignados a la pantalla del PCF8574
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
void setup()
{
  Serial.begin(9600);
  Serial.println("device is ready...");
  pinMode(LED_BUILTIN, OUTPUT);

  vw_set_rx_pin(12); // pin
  vw_setup(8000); // bps
  vw_rx_start();

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
  String text="";
  if (vw_get_message(message, &messageLength)) // non-blocking
  {
    Serial.print("received: ");
    for (int i = 0; i < messageLength; i++)
    {
      Serial.write(message[i]);
      text=text+char(message[i]);
    }
    Serial.println();
    lcd.begin(16, 2);
    lcd.home ();
  // Imprimir "Hola Mundo" en la primera linea
  lcd.print("Recibido");
  // Mover el cursor a la segunda linea (1) primera columna
  lcd.setCursor ( 0, 1 );
  // Imprimir otra cadena en esta posicion
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  lcd.print("Recibido: " + text);
  }
}
