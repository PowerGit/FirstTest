/*
 * NetworkClient.cpp
 *
 *  Created on: Jan 12, 2015
 *      Author: lwj
 */
#include "NetworkClient.h"

NetworkClient::NetworkClient(eServerType type)
{
	mState = eUnConnect;
	mFd    = 0;
	mPort  = 0;
	mInputBuff.init(INPUT_BUFF_SIZE);
	mOutputBuff.init(OUTPUT_BUFF_SIZE);
	mIp.clear();

	mType = type;
}

NetworkClient::~NetworkClient()
{

}

void NetworkClient::connect(string ip, uint32 port)
{
	mFd = socket(AF_INET, SOCK_STREAM, 0);
	if(mFd < 0)
	{
		cout << "Err$$ socket create err" << endl;
		return;
	}

	sockaddr_in addr;
	addr.sin_family      = AF_INET;
	addr.sin_addr.s_addr = inet_addr(ip.c_str());
	addr.sin_port        = htons(port);


	//设置为非阻塞
	GameUtil::setSocketNonBlocking(mFd, true);

	int optval = 1;
	setsockopt(mFd, IPPROTO_TCP, TCP_NODELAY, &optval, sizeof(optval));
	setsockopt(mFd, IPPROTO_TCP, SO_KEEPALIVE, &optval, sizeof(optval));

	::connect(mFd, (sockaddr*)&addr, sizeof(addr));
	if(errno != EINPROGRESS)
	{
		cout << "Err$$ socket connect errno != EINPROGRESS, errno = " << errno << endl;
		return;
	}

	mIp   = ip;
	mPort = port;

	mUpdateTimer.startTimer(GameUtil::now64(), THOUSAND * 10);
}

void NetworkClient::update(uint64 now)
{
	if(true == mUpdateTimer.isArriveTime(now))
	{
		if(mState == eDisConnect)
		{
			assert(false && "connect fail!!!");
		}
		else if(mState == eUnConnect || mState == eConnecting)
		{
			checkConn();
		}


	}
}

void NetworkClient::checkConn()
{
	timeval timeout;
	timeout.tv_sec = 0;
	timeout.tv_usec = 0;

	fd_set writeSet;
	FD_ZERO(&writeSet);
	FD_SET(mFd, &writeSet);

	int ret = select(mFd + 1, NULL, &writeSet, NULL, &timeout);

	if(ret == 0)
	{
		mState = eConnecting;
	}
	else if(ret < 0)
	{
		mState = eDisConnect;
	}
	else if(ret > 0)
	{
		if(FD_ISSET(mFd, &writeSet) == true)
		{
			int32 err;
			socklen_t len = sizeof(err);
			int32 optRet = getsockopt(mFd, SOL_SOCKET, SO_ERROR, (char*)(&err), &len);
			if(optRet < 0 || err != 0)
			{
				mState = eDisConnect;
			}
			else
			{
				mState = eConnected;
				cout << "Connect Succ!!!" << endl;

				afterConn();
			}
		}
	}
}

void NetworkClient::recv()
{

}

void NetworkClient::afterConn()
{
	Proto::ProGateRegister proRis;
	proRis.serverType = mType;
	writeBuff(Opcodes::OCGateRegister, proRis);

	sendMsg();
}

void NetworkClient::sendMsg()
{
	char* buff = mOutputBuff.mBuff;
	int32 ret = ::send(mFd, buff, mOutputBuff.mSize, 0);
	if(ret < 0)
	{
		cout << "Err sendMsg, ret = " << ret << endl;
		return;
	}

	mOutputBuff.cleanUp();
}

void NetworkClient::writeBuff(uint32 opcode, ProtoBuff& proBuff)
{
	uint32 msgLen = proBuff.getLen() + sizeof(opcode);
	mOutputBuff.writeUint32(msgLen);
	mOutputBuff.writeUint32(opcode);
	mOutputBuff.writeMsg(proBuff);
}
