/*
 * SessionMgr.h
 *
 *  Created on: Jan 6, 2015
 *      Author: lwj
 */

#ifndef SESSIONMGR_H_
#define SESSIONMGR_H_

#include "Common.h"
#include "NetworkServer.h"
#include "Session.h"

class SessionMgr
{
public:
	SessionMgr();
	~SessionMgr();

	void init();
	void fini();
	void heartbeat(uint64 uSec);
	Session* getSesn(int32 connFd);

	Session* newConn(int32 connFd);
	void delConn(Session* sesn);

private:
	NetworkServer mNetwork;
	TimerUtil     mTimer;
};

#endif /* SESSIONMGR_H_ */
