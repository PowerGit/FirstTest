/*
 * GameUtil.h
 *
 *  Created on: Jan 13, 2015
 *      Author: lwj
 */

#ifndef GAMEUTIL_H_
#define GAMEUTIL_H_

#include "BaseType.h"

class GameUtil
{
public:
	static uint32 now32()
	{
		time_t now;
		time(&now);
		return now;
	}

	static uint64 now64()
	{
		timeval tv;
		gettimeofday(&tv, NULL);

		uint64 now = tv.tv_sec * MILLION + tv.tv_usec;
		return now;
	}

	static void startTimer(uint32 sec, uint64 uSec, __sighandler_t callback)
	{
		struct sigaction tact;
		/*信号到了要执行的任务处理函数为prompt_info*/
		tact.sa_handler = callback;
		tact.sa_flags = 0;
		/*初始化信号集*/
		sigemptyset(&tact.sa_mask);
		/*建立信号处理机制*/
		sigaction(SIGALRM, &tact, NULL);

		struct itimerval value;
		/*设定执行任务的时间间隔为2秒0微秒*/
		value.it_value.tv_sec = sec;
		value.it_value.tv_usec = uSec;
		/*设定初始时间计数也为2秒0微秒*/
		value.it_interval = value.it_value;
		/*设置计时器ITIMER_REAL*/
		setitimer(ITIMER_REAL, &value, NULL);
	}

	static void setQuitSignal(__sighandler_t callback)
	{
		struct sigaction tact;
		tact.sa_handler = callback;
		tact.sa_flags = 0;
		sigemptyset(&tact.sa_mask);
		sigaction(SIGQUIT, &tact, NULL);
		sigaction(SIGINT, &tact, NULL);
	}

	static void setSocketNonBlocking(int32 socket, bool on)
	{
		int32 flags = fcntl(socket, F_GETFL, 0);
		if (true == on)
		{
			flags |= O_NONBLOCK;
		}
		else
		{
			flags &= ~O_NONBLOCK;
		}

		fcntl(socket, F_SETFL, flags);
	}
};


#endif /* GAMEUTIL_H_ */
