/*
 * NetworkClient.h
 *
 *  Created on: Jan 12, 2015
 *      Author: lwj
 */

#ifndef NETWORKCLIENT_H_
#define NETWORKCLIENT_H_

#include "BaseType.h"
#include "ByteBuffer.h"
#include "TimerUtil.h"
#include "GameUtil.h"
#include "ProtoBuff.h"

enum eConnState
{
	eUnConnect  = 0,
	eConnecting = 1,
	eConnected  = 2,
	eDisConnect = 3
};

class NetworkClient
{
public:
	NetworkClient(eServerType type);
	~NetworkClient();

	void connect(string ip, uint32 port);
	void afterConn();
	void recv();
	void sendMsg();
	void writeBuff(uint32 opcode, ProtoBuff& proBuff);
	void update(uint64 now);

private:
	void checkConn();

private:
	eConnState  mState;
	eServerType mType;
	int32       mFd;
	string      mIp;
	uint32      mPort;
	ByteBuffer  mInputBuff;
	ByteBuffer  mOutputBuff;
	TimerUtil   mUpdateTimer;
};


#endif /* NETWORKCLIENT_H_ */
