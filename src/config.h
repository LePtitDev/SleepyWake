#ifndef CONFIG_H
#define CONFIG_H

#include "clock.h"

class DayConfig
{
private:

    uint32_t m_sleepTime;
    uint32_t m_wakeTime;

public:

    DayConfig(const DayConfig& config);
    DayConfig(int sleepHour, int sleepMinute, int wakeHour, int wakeMinute);

    uint32_t sleepTime() const;
    uint32_t wakeTime() const;

};

class Config
{
private:

    DayConfig m_days[7];

    bool m_sleepMode;

public:

    Config();

    void updateClock(Clock& clock);
    bool sleepMode() const;

};

#endif
