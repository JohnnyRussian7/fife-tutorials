
#include "Win32TimerImpl.h"

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

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

unsigned int Timer::TimerImpl::GetTime() const
{
    return m_virtualTime;
}

void Timer::TimerImpl::SetTime(unsigned int time)
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
    m_multiplier = m_multiplier;
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
        m_virtualTime = m_virtualTime + static_cast<unsigned int>((m_realTime - m_realTimeStart) * m_multiplier);
    }
}

unsigned int Timer::TimerImpl::QueryRealTime()
{
    if (m_hasHighPerformanceCounter)
    {
        // high performance counter has known issues with multi-core processors
        // so temporarily disable multi-core to get around these problems
        DWORD_PTR affinityMask;
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
            return unsigned int((time.QuadPart) * 1000 / HighPerformanceFrequency.QuadPart);
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