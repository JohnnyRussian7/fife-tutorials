
#ifndef TIMER_H_
#define TIMER_H_

class Timer
{
public:
    Timer();
    ~Timer();

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

	unsigned int QueryRealTime() const;
private:
    class TimerImpl;
    TimerImpl* m_impl;
};

#endif