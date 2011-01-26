/**********************************************************************
*	Filename: Win32TimerImpl.h
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
#ifndef WIN32TIMERIMPL_H_
#define WIN32TIMERIMPL_H_

#include "StdIncludes.h"

#include "Timer.h"

class Timer::TimerImpl
{
public:
    TimerImpl();
    ~TimerImpl();

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

    uint32_t QueryRealTime();

private:
    void ResetRealTime();
    void ResetVirtualTime();

private:
    uint32_t m_realTimeStart;
    uint32_t m_realTime;
    uint32_t m_virtualTime;
    float m_multiplier;
    bool m_isStopped;
    bool m_isPaused;
    bool m_hasMultiCore;
    bool m_hasHighPerformanceCounter;
};

#endif
