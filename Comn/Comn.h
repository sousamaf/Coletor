#ifndef Comn_h
#define Comn_h
#include "Arduino.h"
#include <vector.h>
#include <String.h>

class Comn  {  
  public:
    Comn(int);
    void setPin(int);
	bool start_apc220(char *,char *,char *,char *,char *);
	void getconfig();
	void setupApc();
	void init(char *str,int);
	bool send(char *str);  
	char *trim(char *);
	String read();
	String convertertostring(char *);
	
  private:
    int _pin;
    bool _send;	
};

#endif