#ifndef COMMUNICATION2_H_
#define COMMUNICATION2_H_
#include <sstream.h>
#include <iostream.h>
#include <iomanip.h>
#include <vector.h>
#include <Arduino.h>
#include <string.h>

//using namespace std;

namespace middleware
{

class Communication2
{
	//int frequence;
	//char * idDevice;
public:
	Communication2(int);
	virtual ~Communication2();
	char* initia(char *,int);
	int set(int);
	//int send(char * message);
	//char read(char * message);
};

} /* namespace middleware */
#endif /* COMMUNICATION_H_ */
