
#ifndef WIN32_TIMER_IMPL
#define WIN32_TIMER_IMPL

#include "stdint.h"
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
