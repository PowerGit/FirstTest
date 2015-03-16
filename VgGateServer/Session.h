/*
 * Session.h
 *
 *  Created on: Jan 19, 2015
 *      Author: lwj
 */

#ifndef SESSION_H_
#define SESSION_H_

#include "Common.h"

class NetworkServer;

class Session : public EventMsg
{
public:
	Session(int32 connFd);
	~Session();

	virtual void message(epoll_event& ev);
	void setNetworkServer(NetworkServer* netServer);
	void readMsg(ByteBuffer& msg, uint32 recvLen);

private:
	int32          mFd;
	ByteBuffer     mInputBuffer;
	ByteBuffer     mLastBuffer;
	NetworkServer* mNetworkServer;
};


#endif /* SESSION_H_ */
