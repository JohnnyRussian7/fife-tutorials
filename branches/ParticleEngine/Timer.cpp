
#include "Timer.h"

// chooses the correct implementation to include
// based on compiler defines
#if defined(_WIN32) || defined(_WIN64)
#include "Win32TimerImpl.h"
#elif defined(__linux) || defined(linux)
#include "LinuxTimerImpl.h"
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

unsigned int Timer::GetTime() const
{
    return m_impl->GetTime();
}

void Timer::SetTime(unsigned int time)
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