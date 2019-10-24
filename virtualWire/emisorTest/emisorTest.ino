// library
#include <VirtualWire.h>

void setup() 
{
  Serial.begin(9600); 

  // virtual wire
  vw_set_tx_pin(12); // pin
  vw_setup(8000); // bps
}

void loop()
{
  sendString("me", true); 
  delay(100); 
}

void sendString(String message, bool wait)
{
  byte messageLength = message.length() + 1; 

  // convert string to char array
  char charBuffer[messageLength]; 
  message.toCharArray(charBuffer, messageLength);

  vw_send((uint8_t *)charBuffer, messageLength); 

  if (wait) vw_wait_tx(); 

  Serial.println("sent: " + message); 
}
