#include <Comn.h>

Comn comunica(13);

void setup(){
Serial.begin(9600);
}
void loop(){
  if(comunica.send('b')==true)
  Serial.println("Verdadeiro");
  else
  Serial.println("False");
  
  delay(1500);
}
