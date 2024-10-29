#include "config.h"

#define WEEK_SLEEP_HOUR 19
#define WEEK_SLEEP_MINUTE 30
#define WEEK_WAKE_HOUR 6
#define WEEK_WAKE_MINUTE 30

#define WEEKEND_SLEEP_HOUR 19
#define WEEKEND_SLEEP_MINUTE 30
#define WEEKEND_WAKE_HOUR 7
#define WEEKEND_WAKE_MINUTE 0

DayConfig::DayConfig(const DayConfig& config)
    : m_sleepTime(config.m_sleepTime), m_wakeTime(config.m_wakeTime)
{
}

DayConfig::DayConfig(int sleepHour, int sleepMinute, int wakeHour, int wakeMinute)
    : m_sleepTime(Clock::toTime(sleepHour, sleepMinute, 0)), m_wakeTime(Clock::toTime(wakeHour, wakeMinute, 0))
{
}

uint32_t DayConfig::sleepTime() const
{
    return m_sleepTime;
}

uint32_t DayConfig::wakeTime() const
{
    return m_wakeTime;
}

Config::Config() :
    m_days
    {
        DayConfig(WEEKEND_SLEEP_HOUR, WEEKEND_SLEEP_MINUTE, WEEKEND_WAKE_HOUR, WEEKEND_WAKE_MINUTE),
        DayConfig(WEEK_SLEEP_HOUR, WEEK_SLEEP_MINUTE, WEEK_WAKE_HOUR, WEEK_WAKE_MINUTE),
        DayConfig(WEEK_SLEEP_HOUR, WEEK_SLEEP_MINUTE, WEEK_WAKE_HOUR, WEEK_WAKE_MINUTE),
        DayConfig(WEEK_SLEEP_HOUR, WEEK_SLEEP_MINUTE, WEEK_WAKE_HOUR, WEEK_WAKE_MINUTE),
        DayConfig(WEEK_SLEEP_HOUR, WEEK_SLEEP_MINUTE, WEEK_WAKE_HOUR, WEEK_WAKE_MINUTE),
        DayConfig(WEEK_SLEEP_HOUR, WEEK_SLEEP_MINUTE, WEEK_WAKE_HOUR, WEEK_WAKE_MINUTE),
        DayConfig(WEEKEND_SLEEP_HOUR, WEEKEND_SLEEP_MINUTE, WEEKEND_WAKE_HOUR, WEEKEND_WAKE_MINUTE)
    }
{
}

void Config::updateClock(Clock& clock)
{
    DayConfig& config = m_days[clock.dayOfTheWeek()];

    uint32_t time = clock.time();
    uint32_t sleepTime = config.sleepTime();
    uint32_t wakeTime = config.wakeTime();

    m_sleepMode = wakeTime < sleepTime
        ? time >= sleepTime || time < wakeTime
        : time < wakeTime && time >= sleepTime;
}

bool Config::sleepMode() const
{
    return m_sleepMode;
}
