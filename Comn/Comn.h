#ifndef Comn_h
#define Comn_h
#include "Arduino.h"
#include <vector.h>
#include <String.h>

class Comn  {  
  public:
    Comn();   
	void init(char *str,int);
	void send(char *str);  	
	String read();	
  private:    		
    int _pin;
    bool _send;	
	char *trim(char *);
	String convertertostring(char *);
};

#endif