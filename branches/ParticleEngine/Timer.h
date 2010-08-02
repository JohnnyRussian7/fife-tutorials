
#ifndef TIMER_H_
#define TIMER_H_

#include "stdint.h"

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