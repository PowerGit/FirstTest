/*
 * main.cpp
 *
 *  Created on: Dec 12, 2014
 *      Author: lwj
 */
#include "Common.h"
#include "GateInstance.h"
#include "SessionMgr.h"

void tickMilliSec(int signo)
{
	uint64 now = GameUtil::now64();

	gSessionMgr->heartbeat(now);
}

void sys_exit(int dunno)
{
	gSessionMgr->fini();
	SAFE_DEL(gSessionMgr);

	cout << "stop VgGateServer Succ." << endl;
	exit(0);
}

int main()
{
	GameUtil::setQuitSignal(sys_exit);

	gSessionMgr = new SessionMgr();
	gSessionMgr->init();

	GameUtil::startTimer(0, 10000, tickMilliSec);

	cout << "start VgGateServer Succ." << endl;
	while(true)
	{
		sleep(31536000);   //1年
	}
}

