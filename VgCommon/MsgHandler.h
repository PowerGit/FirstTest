/*
 * MsgHandler.h
 *
 *  Created on: Feb 3, 2015
 *      Author: lwj
 */

#ifndef MSGHANDLER_H_
#define MSGHANDLER_H_

#include "BaseType.h"
#include "EventMsg.h"
#include "ByteBuffer.h"

class MsgHandler : public EventMsg
{
public:
	MsgHandler();
	~MsgHandler();

	virtual void message(epoll_event& ev);

private:
	int32      mFd;
	ByteBuffer mInputBuffer;
	ByteBuffer mLastBuffer;
	ByteBuffer mOutputBuff;
};


#endif /* MSGHANDLER_H_ */
