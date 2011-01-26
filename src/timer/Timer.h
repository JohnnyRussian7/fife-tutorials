/**********************************************************************
*	Filename: Timer.h
*	
*	Copyright (C) 2011, FIFE team
*	http://www.fifengine.net
*
*	This file is part of FIFE.
*
*	FIFE is free software: you can redistribute it and/or modify it
*	under the terms of the GNU Lesser General Public License as
*	published by the Free Software Foundation, either version 3 of
*	the License, or any later version.
*
*	FIFE is distributed in the hope that it will be useful,
*	but WITHOUT ANY WARRANTY; without even the implied warranty of
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* 	GNU Lesser General Public License for more details.
*
*	You should have received a copy of the GNU Lesser General Public
*	License along with FIFE. If not, see http://www.gnu.org/licenses/.
***********************************************************************/
#ifndef TIMER_H_
#define TIMER_H_

#include "../StdIncludes.h"

class Timer
{
public:
    Timer();
    ~Timer();

    uint32_t GetTime() const;
    void SetTime(uint32_t time);

    float GetMultiplier() const;
    void SetMultiplier(float multiplier);

    bool IsRunning();

    void Start();
    void Stop();
    void Pause();

    void Reset();

    void Tick();

	uint32_t QueryRealTime() const;
private:
    class TimerImpl;
    TimerImpl* m_impl;
};

#endif