/**************************************************
 * BIBLIOECA DE COMUNICAÇÃO SEM FIO PARA MICROCON-
 * TROLADORES
***************************************************/

/**************************************************
 * Includes
***************************************************/
#include "Arduino.h"
#include "Comn.h"
#include <vector.h>
#include <string>
#include <String.h>
#include <SoftwareSerial.h>

const int setPino = 8; //set pin
/**************************************************
 * Constructor of class
***************************************************/
Comn::Comn(int pin) {
     setPin(pin);
}


bool Comn::start_apc220(char *hz, char *rf_rate, char *pwr, char *uart_rate, char *sc) {

	
  //Validating parameters
  if (strlen(hz) != 6) 
  {
    Serial.println("Parameter Frequency of incorrect... - coll between 418000 - 455000");
  return false;
  }
  
  if (strlen(rf_rate) != 1 ) 
  {
    Serial.println("Parameter RF  is not 1 digit: legal values is 1,2,3,4...");
    return false;
  }
  
  if (strlen(pwr) != 1 ) 
  {
    Serial.println("Power parameter needs only 1 digit: legal values is 1..9"); 
    return false;
  }

  if (strlen(uart_rate) != 1 ) 
  {
    Serial.println("Uart baudrate needs only 1 digit: legal values is 0..6"); 
    return false;
  }
  
  if (strlen(sc) != 1 ) 
  {
    Serial.println("Parity parameter needs only 1 digit: legal values is 0,1,2"); 
    return false;
  }
  
   setupApc();
  
  //Preparing for writing the module parameters
  digitalWrite(setPino, LOW); // set radio in config mode
  delay(50);
  Serial.print("WR");
  Serial.print(" ");
  
  Serial.print(hz);
  Serial.print(" ");
  
  Serial.print(rf_rate);
  Serial.print(" ");
  
  Serial.print(pwr);
  Serial.print(" ");
  
  Serial.print(uart_rate);
  Serial.print(" ");
  
  Serial.print(sc);
  
  Serial.write(0x0D);
  Serial.write(0x0A);
  return true;
  delay(10);

   while (Serial.available()) {
    Serial.write(Serial.read());
  }
 }

 
 void Comn::getconfig(void) {
 
  delay(10); // stabilize please
  digitalWrite(setPino, LOW); // set radio in config mode
  Serial.println("RD"); // ask for data
  delay(10);
  
  while (Serial.available()) {
    Serial.write(Serial.read()); 
  }
  
  digitalWrite(setPino, HIGH); // set radio back in normal tx/rx mode
}

 void Comn::setupApc(void)
{
  pinMode(setPino,OUTPUT);
  digitalWrite(setPino,HIGH);
  delay(50);
  /* pinMode(fiveV,OUTPUT);  // 5V
  digitalWrite(fiveV,HIGH); // turn on 5V
  delay(50);
  pinMode(enPin,OUTPUT); // ENABLE
  digitalWrite(enPin,HIGH); //
  delay(100);
  apc220.begin(9600); */
}
 
/**************************************************
 * metodo de inicalização do módulo de comunicação
***************************************************/	
void Comn::init(char *str, int freq )
{
	// Define o baud rate (taxa de trasmissão) como 9600
	Serial.begin(freq);
	// Clear string
	trim(str);	
	String s = convertertostring(str);
	int op=0;
	bool ret= false;
	
	if(s=="Xbee")
		op=1;
		
	if(s=="APC220")
		op=2;
		
	delay(10);	
	
	if(op==0)
	{
		Serial.println("Option is not valid!");
		return;
	}
	
	 switch (op)
	{
		case 1:
		Serial.println("Xbee OK");
		break;
		
		case 2:
		{
			ret = start_apc220("436000", "3", "9", "3", "0");
			if(ret)
			Serial.println("APC OK");
			else
			Serial.println("ERRO!");
			
		break;}				
	}     

    Serial.println("--"+s);

}

/**************************************************
 * metodo de envio de mensagens
***************************************************/
bool Comn::send(char *str){
 
	trim(str);
	char ch[40];
	strcpy(ch,str);
	
	//Convertendo char para string
	int i=0;
	String a="";
	while(ch[i]!=' ')
	{
		a += ""+ch[i];
		i++;
	}
	
	//Verifcando modulo de envio
	if (a=="Xbee")
	{
	  _send = true;
	 
	}
	else
	  _send = false;
	  
	return _send;
}

/**************************************************
 * metodo para recebimento de mensagens
***************************************************/
String Comn::read()
{

	String sread;
	char a;
	if(Serial.available()){
		  a = (char)Serial.read();
		  a+=a;
		  }
		  Serial.flush();
		  
    //Retornando String
	return sread;
}

/**************************************************
 * metodo converter ponteiro "*char" para string
***************************************************/
 String Comn::convertertostring(char *str)
{
	trim(str);
	char chr[15];
	strcpy(chr,str);
	int i=0;
	String sread="";
	
	
	while(chr[i]!='\0')
	{
		sread += chr[i];
		i++;		
	}
	//Serial.flush();
	
	return sread;
}
 
/**************************************************
 * metodo para limpar espaços dentro da string
***************************************************/
char* Comn::trim(char *s) {
   char *ptr;
   if (!s)
       return NULL;   // handle NULL string
   if (!*s)
       return s;      // handle empty string
   for (ptr = s + strlen(s) - 1; (ptr >= s) && isspace(*ptr); --ptr);
   ptr[1] = '\0';
   return s;
}

/**************************************************
 * metodo para setar o pino de status
***************************************************/
void Comn::setPin(int pin = 13){
  
}




