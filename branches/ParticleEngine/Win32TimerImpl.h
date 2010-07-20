
#ifndef WIN32_TIMER_IMPL
#define WIN32_TIMER_IMPL

#include "Timer.h"

class Timer::TimerImpl
{
public:
    TimerImpl();
    ~TimerImpl();

    unsigned int GetTime() const;
    void SetTime(unsigned int time);

    float GetMultiplier() const;
    void SetMultiplier(float multiplier);

    bool IsRunning();

    void Start();
    void Stop();
    void Pause();

    void Reset();

    void Tick();

    unsigned int QueryRealTime();

private:
    void ResetRealTime();
    void ResetVirtualTime();

private:
    unsigned int m_realTimeStart;
    unsigned int m_realTime;
    unsigned int m_virtualTime;
    float m_multiplier;
    bool m_isStopped;
    bool m_isPaused;
    bool m_hasMultiCore;
    bool m_hasHighPerformanceCounter;
};

#endif
