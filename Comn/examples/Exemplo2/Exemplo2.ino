#include <Comn.h>


Comn comunica(13);
char *  str = "ola";

void setup(){
comunica.initia("Xbee   ",9600);
}
void loop(){
  if(comunica.send('a')==true)
  Serial.println("Verdadeiro");
  else
  Serial.println("False");
  
  delay(1500);
}
