// Do not remove the include below
#include "Coletor.h"

int ledPin =  13;    // LED connected to digital pin 13

//The setup function is called once at startup of the sketch
void setup()
{
	pinMode(ledPin, OUTPUT);
}

// The loop function is called in an endless loop
void loop()
{
	  digitalWrite(ledPin, HIGH);   // set the LED on
	  delay(1500);                  // wait for a second
	  digitalWrite(ledPin, LOW);    // set the LED off
	  delay(1500);                  // wait for a second
}
