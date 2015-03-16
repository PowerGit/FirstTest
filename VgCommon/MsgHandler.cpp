/*
 * MsgHandler.cpp
 *
 *  Created on: Feb 3, 2015
 *      Author: lwj
 */
#include "MsgHandler.h"

MsgHandler::MsgHandler()
{
	mFd = 0;
	mInputBuffer.init(INPUT_BUFF_SIZE);
	mLastBuffer.init(INPUT_BUFF_SIZE);
	mOutputBuff.init(OUTPUT_BUFF_SIZE);
}

MsgHandler::~MsgHandler()
{

}

void MsgHandler::message(epoll_event& ev)
{

}
