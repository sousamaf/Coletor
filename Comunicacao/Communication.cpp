/*
 * Communication.cpp
 *
 *  Created on: 27/02/2013
 *      Author: marcosousa
 */

#include "Communication.h"
#include <sstream.h>
#include <iomanip.h>

namespace middleware
{
	string sDevice;
	

	Communication::Communication()
	{
		// TODO Auto-generated constructor stub

	}

	Communication::~Communication()
	{
		// TODO Auto-generated destructor stub
	}

	/*
	 * metodo de iniicalização do módulo de comunicação
	 */
	int Communication::init(String device, int frequence)
	{
		sDevice = device;

		switch (device)
		{
			case 'XBEE'
			Serial.begin(frequence);
			
			break;
			
			case 'APC220'
			Serial.begin(frequence);
			
			break;
		}
		return 0;
	}

	/*
	 * Recebe como parametro uma string, converte para tipo de dados do módulo
	 * e enviao sinal
	 */
	int Communication::send(String message)
	{		
		
		std::string str = message;
		std::vector<char> bytes(str.begin(), str.end());
		
		switch (sDevice)
		{
			case 'XBEE'
			Serial.print(bytes);			   
			break;
			
			case 'APC220'
			Serial.print(bytes);			
			break;
		}
		return 0;
	}

	/*
	 * Recebe como parametro uma string, converte para tipo de dados de leitura
	 * e retorna o valor
	 */
	String Communication::read(byte[] message)
	{
			
		std::vector<byte>  source(str.begin(),str.end());
		encrypt(&source[0],source.size());
		
		switch (sDevice)
		{
			case 'XBEE'
			Serial.print("");			   
			break;
			
			case 'APC220'
			Serial.print("");			
			break;
		}
		return 0;
		
		return "";
	}

} /* namespace middleware */
