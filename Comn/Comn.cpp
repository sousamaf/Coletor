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

int idDevice=-1;
/**************************************************
 * Constructor of class
***************************************************/
Comn::Comn() {}

/**************************************************
 * metodo de inicalização do módulo de comunicação
***************************************************/	
void Comn::init(char *str, int freq )
{
	// Define o baud rate (taxa de trasmissão) 
	Serial.begin(freq);		
	trim(str);	
	String s = convertertostring(str);
	int op=0;
	bool ret= false;
	
	if(s=="Xbee")
	{
		op=1;		
	}
		
	if(s=="APC220")
	{
		op=2;		
	}
	
	idDevice=op;
	
	if(op==0)
	{
		Serial.println("Option is not valid!");
		return;
	}
	
	 switch (op)
	{
		case 1:
		Serial.println("Xbee OK");
		delay(50);
		Serial.flush();
		break;
		
		case 2:				
		Serial.println("APC OK");	
		delay(50);	
		Serial.flush();		
		break;			
	}     

}

/**************************************************
 * metodo de envio de mensagens
***************************************************/
void Comn::send(char *str)
{
 
	switch(idDevice)
	{
		case 1:
		{
			String a = convertertostring(str);	
			if(a.length() >= 15)
			{	  
			  Serial.println("Erro! Estou de byte > 15.");
			  delay(20);
			  Serial.flush();	  
			  return;	  
			}	  
			Serial.println(a);	
		}break;
		
		case 2:
		{
			String a = convertertostring(str);	
			if(a.length() >= 15)
			{	  
			  Serial.println("Erro! Estou de byte > 15.");
			  delay(20);
			  Serial.flush();	  
			  return;	  
			} 
			Serial.println(a);	
		}break;
	}
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
	char chr[100];	
	strcpy(chr,str);
	int i=0;
	String sread="";
	
	while(chr[i]!='\0')
	{
		sread += chr[i];
		i++;		
	}

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

  





