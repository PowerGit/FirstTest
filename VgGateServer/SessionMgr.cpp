/*
 * SessionMgr.cpp
 *
 *  Created on: Jan 6, 2015
 *      Author: lwj
 */
#include "SessionMgr.h"

SessionMgr::SessionMgr()
{

}

SessionMgr::~SessionMgr()
{

}

void SessionMgr::init()
{
	mNetwork.init(33333);

	mTimer.startTimer(GameUtil::now64(), THOUSAND * 100);
}

void SessionMgr::fini()
{

}

void SessionMgr::heartbeat(uint64 uSec)
{
	if(true == mTimer.isArriveTime(uSec))
	{
		mNetwork.update();
	}
}

Session* SessionMgr::newConn(int32 connFd)
{
	Session* newSesn = new Session(connFd);
	if(newSesn == NULL)
	{
		cout << "Err create Session connFd = " << connFd << endl;
		return NULL;
	}

	return newSesn;
}

void SessionMgr::delConn(Session* sesn)
{
	if(sesn != NULL)
	{
		SAFE_DEL(sesn);
	}
}
