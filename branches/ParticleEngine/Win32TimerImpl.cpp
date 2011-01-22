/**********************************************************************
*	Filename: Win32TimerImpl.cpp
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

#include "Win32TimerImpl.h"

namespace 
{
    LARGE_INTEGER HighPerformanceFrequency;
}

Timer::TimerImpl::TimerImpl()
: m_realTimeStart(0), m_realTime(0), m_virtualTime(0), m_multiplier(1.f),
  m_isStopped(false), m_isPaused(false), m_hasMultiCore(false), m_hasHighPerformanceCounter(true)
{
    // gather system related information
    SYSTEM_INFO sysinfo;
    GetSystemInfo(&sysinfo);
    m_hasMultiCore = (sysinfo.dwNumberOfProcessors > 1);
    m_hasHighPerformanceCounter = (QueryPerformanceFrequency(&HighPerformanceFrequency) == TRUE) ? true : false;

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
    if (m_hasHighPerformanceCounter)
    {
        // high performance counter has known issues with multi-core processors
        // so temporarily disable multi-core to get around these problems
        DWORD_PTR affinityMask = 1;
        if (m_hasMultiCore)
        {
            affinityMask = SetThreadAffinityMask(GetCurrentThread(), 1);
        }

        LARGE_INTEGER time;
        BOOL success = QueryPerformanceCounter(&time);

        if (m_hasMultiCore)
        {
            // restore multi-core if it was enabled before we disabled it
            SetThreadAffinityMask(GetCurrentThread(), affinityMask);
        }

        if (success)
        {
            return uint32_t((time.QuadPart) * 1000 / HighPerformanceFrequency.QuadPart);
        }
    }

    // drop back to non-high performance counter when not available
    return GetTickCount();
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