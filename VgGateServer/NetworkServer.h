/*
 * NetworkServer.h
 *
 *  Created on: Dec 29, 2014
 *      Author: lwj
 */

#ifndef NETWORKSERVER_H_
#define NETWORKSERVER_H_

#include "Common.h"
#include "Session.h"
#include "EventMsg.h"

class NetworkServer : public EventMsg
{
public:
	NetworkServer();
	~NetworkServer();

	void init(uint32 port);
	void update();
	void acceptConn(epoll_event& ev);
	void closeConn(int32 connFd);

	virtual void message(epoll_event& ev);

private:
	uint32               mPort;
	int32                mQueueFd;
	int32                mListenFd;
	vector<epoll_event>  mEvents;
	map<int32, Session*> mActiveFd;
};


#endif /* NETWORKSERVER_H_ */
