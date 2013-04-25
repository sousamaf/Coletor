#include "Communication2.h"
#include <sstream.h>
#include <iostream.h>
#include <iomanip.h>
#include <vector.h>
#include <Arduino.h>
#include <string.h>

//using namespace std;

namespace middleware
{
    char* sDevice;
	int pin;

	Communication2::Communication2(int freq)
	{
		// TODO Auto-generated constructor stub
		

	}

	Communication2::~Communication2()
	{
		// TODO Auto-generated destructor stub
	}

	/*
	 * metodo de iniicalização do módulo de comunicação
	 */
	char* Communication2::initia(char* device, int frequence)
	{
		sDevice = device;
		
		/* for(int i =0; i<device.length; i++)
		{
		  char vet = (char)device;
		} */
		
		 Serial.begin(frequence);
		/* switch (""+sDevice)
		{
			case 'XBEE':				
			break;
			
			case 'APC220':					
			break;
		 } */
		return device;
	}

	int Communication2::set(int pin)
	{
		return pin;
	}
	
	/*
	 * Recebe como parametro uma string, converte para tipo de dados do módulo
	 * e enviao sinal
	 */
	/* int Communication2::send(char * message)
	{		
		
		char *str = message;
		vector<char> bytes(str.begin(), str.end());
		
		switch (*sDevice)
		{
			case 'XBEE':
			Serial.print("XBEE");			   
			break;
			
			case 'APC220':
			Serial.print("XBEE");			
			break;
		}
		return 0;
	} */

	/*
	 * Recebe como parametro uma string, converte para tipo de dados de leitura
	 * e retorna o valor
	 */
	/* char Communication2::read(const char * message)
	{
			
		//std::vector<byte>  source(str.begin(),str.end());
		//encrypt(&source[0],source.size());
		
		switch (sDevice)
		{
			case 'XBEE'
			Serial.print("");			   
			break;
			
			case 'APC220'
			Serial.print("");			
			break;
		}
		return "";
	} */

} /* namespace middleware */
