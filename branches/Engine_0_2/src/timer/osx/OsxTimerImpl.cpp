/**********************************************************************
 *	Filename: OsxTimerImpl.cpp
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
#include "PrecompiledIncludes.h"

#include "OsxTimerImpl.h"

#include <mach/mach_time.h>

Timer::TimerImpl::TimerImpl()
: m_realTimeStart(0), m_realTime(0), m_virtualTime(0), m_multiplier(1.f),
m_isStopped(false), m_isPaused(false)
{	
    // set to an initial state
    Reset();
}

Timer::TimerImpl::~TimerImpl()
{
    
}

uint32_t Timer::TimerImpl::GetTime() const
{
    return m_virtualTime;
}

void Timer::TimerImpl::SetTime(uint32_t time)
{
    // reset to initial state
    Reset();
	
    // set the virtual time
    m_virtualTime = time;
}

float Timer::TimerImpl::GetMultiplier() const
{
    return m_multiplier;
}

void Timer::TimerImpl::SetMultiplier(float multiplier)
{
    m_multiplier = multiplier;
}

bool Timer::TimerImpl::IsRunning()
{
    return (!m_isStopped && !m_isPaused);
}

void Timer::TimerImpl::Start()
{
    if (m_isPaused)
    {
        m_isPaused = false;
    }
	
    if (m_isStopped)
    {
        ResetVirtualTime();
        m_isStopped = false;
    }
	
    ResetRealTime();
}

void Timer::TimerImpl::Stop()
{
    // stop overrides paused
    if (m_isPaused)
    {
        m_isPaused = false;
    }
	
    m_isStopped = true;
}

void Timer::TimerImpl::Pause()
{
    m_isPaused = true;
}

void Timer::TimerImpl::Reset()
{
	ResetRealTime();
	ResetVirtualTime();
}

void Timer::TimerImpl::Tick()
{
    if (IsRunning())
    {
        // query for real time from system timer
        m_realTime = QueryRealTime();
		
        // update the virtual time based on the real time
        m_virtualTime = static_cast<uint32_t>((m_realTime - m_realTimeStart) * m_multiplier);
    }
}

uint32_t Timer::TimerImpl::QueryRealTime()
{
    static bool timeBaseAcquired = false;
    static double timeBase = 0.0;
    
    if (!timeBaseAcquired)
    {
        // only need to calculate this once
        mach_timebase_info_data_t info;
        mach_timebase_info(&info);
        timeBase = static_cast<double>(info.numer) / static_cast<double>(info.denom);
        timeBaseAcquired = true;
    }
    
    double timeInNanoseconds = mach_absolute_time() * timeBase;
	
	const double MsMultiplier = 1e-6;
    
    return uint32_t(timeInNanoseconds * MsMultiplier);
    
    //const uint32_t MsMultiplier = 1000;
    //struct timeval time;
	//gettimeofday(&time, 0);
    //return uint32_t((time.tv_sec*MsMultiplier) + time.tv_usec);
}

void Timer::TimerImpl::ResetVirtualTime()
{
    m_virtualTime = 0;
}

void Timer::TimerImpl::ResetRealTime()
{
    // query real time to set start time
    m_realTimeStart = QueryRealTime();
	
    // initially set current real to start real time
    m_realTime = m_realTimeStart;
}

