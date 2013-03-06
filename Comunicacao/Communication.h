/*
 * Communication.h
 *
 *  Created on: 27/02/2013
 *      Author: marcosousa
 */

#ifndef COMMUNICATION_H_
#define COMMUNICATION_H_

namespace middleware
{

class Communication
{
	int frequence;
	int idDevice;
public:
	Communication();
	virtual ~Communication();
};

} /* namespace middleware */
#endif /* COMMUNICATION_H_ */
