/*
 * main.cpp
 *
 *  Created on: Jan 9, 2015
 *      Author: lwj
 */

#include "Common.h"
#include "WorldInstance.h"
#include "NetworkClient.h"

void tickMilliSec(int signo)
{
	uint64 now = GameUtil::now64();

	gSocket->update(now);
//	char* testChar;
//	cout << "Input:";
//	cin >> testChar;


}

void stopServer(int dunno)
{
	SAFE_DEL(gSocket);

	cout << "stop VgWorldServer Succ." << endl;
	exit(0);
}

int main()
{
	GameUtil::setQuitSignal(stopServer);

	gSocket = new NetworkClient(eServerTypeWorld);

	gSocket->connect("127.0.0.1", 33333);
//	gSocket->connect("192.168.8.214", 33333);
//	assert(true == gSocket->connect("88.88.88.88", 33333));

	GameUtil::startTimer(0, 10000, tickMilliSec);

	cout << "start VgWorldServer Succ." << endl;
	while(true)
	{
		sleep(31536000);   //1年
	}
}
