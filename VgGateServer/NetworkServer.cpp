/*
 * NetworkServer.cpp
 *
 *  Created on: Dec 29, 2014
 *      Author: lwj
 */
#include "GateInstance.h"
#include "NetworkServer.h"
#include "Session.h"

NetworkServer::NetworkServer()
{
	mPort     = 0;
	mQueueFd  = 0;
	mListenFd = 0;

	mEvents.clear();
	mEvents.resize(1024);
}

NetworkServer::~NetworkServer()
{

}

void NetworkServer::init(uint32 port)
{
	mPort = port;
	mQueueFd = epoll_create(1);

	mListenFd = socket(AF_INET, SOCK_STREAM, 0);
	if(mListenFd < 0)
	{
		cout << "Socket create err!" << endl;
		close(mListenFd);
		assert(false);
	}

	GameUtil::setSocketNonBlocking(mListenFd, true);

	int32 flag = 1;
	setsockopt(mListenFd, SOL_SOCKET, SO_REUSEADDR, (char*)&flag, int32(sizeof(flag)));

	struct sockaddr_in localAddr;
	localAddr.sin_family = AF_INET;
	localAddr.sin_addr.s_addr = INADDR_ANY;
	localAddr.sin_port = htons(mPort);

	if(bind(mListenFd, (struct sockaddr*)&localAddr, sizeof(localAddr)) < 0)
	{
		cout << "Socket bind err!" << endl;
		close(mListenFd);
		assert(false);
	}

	if(listen(mListenFd, 128) < 0)
	{
		cout << "Socket listen err!" << endl;
		close(mListenFd);
		assert(false);
	}

	epoll_event event;
	memset(&event, 0, sizeof(event));
	event.data.ptr = this;
	event.events   = EPOLLIN;

	epoll_ctl(mQueueFd, EPOLL_CTL_ADD, mListenFd, &event);
}

void NetworkServer::update()
{
	int32 activeFd = epoll_wait(mQueueFd, &mEvents[0], mEvents.size(), 1);
	if(activeFd <= 0)
	{
		return;
	}

	for(uint32 i = 0; i < (uint32)activeFd; i++)
	{
		epoll_event& ev = mEvents[i];

		EventMsg* eventMsg = (EventMsg*)ev.data.ptr;
		if(eventMsg != NULL)
		{
			eventMsg->message(ev);
		}
	}
}

void NetworkServer::message(epoll_event& ev)
{
	this->acceptConn(ev);
}

void NetworkServer::acceptConn(epoll_event& ev)
{
	sockaddr_in remoteAddr;
	uint32 len = sizeof(remoteAddr);

	int32 connFd = accept(mListenFd, (struct sockaddr*)&remoteAddr, &len);
	GameUtil::setSocketNonBlocking(connFd, true);
	cout << "new Fd = " << connFd;

	Session* sesn = gSessionMgr->newConn(connFd);
	if(sesn != NULL)
	{
		epoll_event newEv;
		memset(&newEv, 0, sizeof(newEv));
		newEv.events = EPOLLIN;
		newEv.data.ptr = sesn;
		epoll_ctl(mQueueFd, EPOLL_CTL_ADD, connFd, &newEv);

		mActiveFd[connFd] = sesn;
		sesn->setNetworkServer(this);
	}
}

void NetworkServer::closeConn(int32 connFd)
{
	map<int32, Session*>::iterator iter = mActiveFd.find(connFd);
	if(iter != mActiveFd.end())
	{
		Session* sesn = iter->second;
		if(sesn != NULL)
		{
			epoll_event delEv;
			memset(&delEv, 0, sizeof(delEv));
			delEv.events = EPOLLIN;
			delEv.data.ptr = sesn;
			epoll_ctl(mQueueFd, EPOLL_CTL_DEL, connFd, &delEv);

			gSessionMgr->delConn(sesn);
			mActiveFd.erase(iter);
			close(connFd);
		}
	}
}
