/*
 * TimerUtil.h
 *
 *  Created on: Jan 13, 2015
 *      Author: lwj
 */

#ifndef TIMERUTIL_H_
#define TIMERUTIL_H_

#include "BaseType.h"

class TimerUtil
{
public:
	TimerUtil(){mTick = 0; mInterval = 0;}
	~TimerUtil(){}

	void startTimer(uint64 now, uint64 interval)
	{
		mTick     = now;
		mInterval = interval;
	}

	bool isArriveTime(uint64 now)
	{
		if(now >= mTick + mInterval)
		{
			mTick = now;
			return true;
		}

		return false;
	}

private:
	uint64 mTick;
	uint64 mInterval;
};

#endif /* TIMERUTIL_H_ */
