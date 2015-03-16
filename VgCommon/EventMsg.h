/*
 * EventMsg.h
 *
 *  Created on: Feb 3, 2015
 *      Author: lwj
 */

#ifndef EVENTMSG_H_
#define EVENTMSG_H_

#include "BaseType.h"

class EventMsg
{
public:
	EventMsg(){}
	virtual ~EventMsg(){}

	virtual void message(epoll_event& ev) = 0;
};


#endif /* EVENTMSG_H_ */
