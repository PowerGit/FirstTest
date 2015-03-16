/*
 * Session.cpp
 *
 *  Created on: Jan 19, 2015
 *      Author: lwj
 */
#include "Session.h"
#include "NetworkServer.h"

Session::Session(int32 connFd)
{
	mFd = connFd;
	mInputBuffer.init(INPUT_BUFF_SIZE);
	mLastBuffer.init(2 * INPUT_BUFF_SIZE);
	mNetworkServer = NULL;
}

Session::~Session()
{

}

void Session::setNetworkServer(NetworkServer* netServer)
{
	mNetworkServer = netServer;
}

void Session::message(epoll_event& ev)
{
	int32 recvLen = ::recv(mFd, mInputBuffer.mBuff, MAX_PACKAGE, 0);
	if(recvLen <= 0)
	{
		mNetworkServer->closeConn(mFd);
		return;
	}

	if(mLastBuffer.mSize > 0)
	{
		memcpy(mLastBuffer.mPos, mInputBuffer.mBuff, MAX_PACKAGE);
		memset(mLastBuffer.mBuff, 0, 2 * INPUT_BUFF_SIZE);
	}


}

void Session::readMsg(ByteBuffer& msg, uint32 recvLen)
{
	while(true)
	{
		uint32 packLen = msg.readUint32();
		if(recvLen < packLen + 4)
		{
			mLastBuffer = msg;
			mLastBuffer.mSize = recvLen;
			return;
		}


	}
}
