/**********************************************************************
*	Filename: Timer.cpp
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

#include "Timer.h"

// chooses the correct timer implementation
#if defined(_WIN32) || defined(_WIN64)
#include "win32/Win32TimerImpl.h"
#elif defined(__linux) || defined(linux)
#include "linux/LinuxTimerImpl.h"
#elif defined(__APPLE__) || defined(__APPLE_CC__)
#include "osx/OsxTimerImpl.h"
#endif

Timer::Timer()
{
    m_impl = new TimerImpl();
}

Timer::~Timer()
{
    delete m_impl;
    m_impl = 0;
}

uint32_t Timer::GetTime() const
{
    return m_impl->GetTime();
}

void Timer::SetTime(uint32_t time)
{
    m_impl->SetTime(time);
}

float Timer::GetMultiplier() const
{
    return m_impl->GetMultiplier();
}

void Timer::SetMultiplier(float multiplier)
{
    m_impl->SetMultiplier(multiplier);
}

bool Timer::IsRunning()
{
    return m_impl->IsRunning();
}

void Timer::Start()
{
    m_impl->Start();
}

void Timer::Stop()
{
    m_impl->Stop();
}

void Timer::Pause()
{
    m_impl->Pause();
}

void Timer::Reset()
{
    m_impl->Reset();
}

void Timer::Tick()
{
    m_impl->Tick();
}

uint32_t Timer::QueryRealTime() const
{
	return m_impl->QueryRealTime();
}