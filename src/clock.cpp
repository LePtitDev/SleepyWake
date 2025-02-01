#include "clock.h"

Clock::Clock()
    : m_rtc(), m_hasError(false), m_startWinterTime(false), m_nowWinterTime(false)
{
}

void Clock::setup()
{
    DateTime buildDate;

    m_hasError = !m_rtc.begin();
    if (!m_hasError)
    {
        if (m_rtc.lostPower())
        {
            m_start = DateTime(F(__DATE__), F(__TIME__));
            buildDate = m_start;
            m_rtc.adjust(m_start);
        }
        else
        {
            buildDate = DateTime(F(__DATE__), F(__TIME__));
            m_start = m_rtc.now();
        }
    }
    else
    {
        m_start = DateTime(F(__DATE__), F(__TIME__));
        buildDate = m_start;
    }

    m_startWinterTime = Clock::isWinterTime(buildDate);
    m_nowWinterTime = Clock::isWinterTime(m_start);
    m_now = m_start;
    m_adjustedNow = getNow();
}

void Clock::loop()
{
    if (m_hasError)
    {
        m_hasError = !m_rtc.begin();
        if (!m_hasError)
        {
            if (m_rtc.lostPower())
            {
                m_start = DateTime(F(__DATE__), F(__TIME__));
                m_rtc.adjust(m_start + TimeSpan(millis() / 1000));
            }
            else
            {
                m_start = m_rtc.now() - TimeSpan(millis() / 1000);
            }
        }
    }

    m_now = m_start + TimeSpan(millis() / 1000);
    m_nowWinterTime = Clock::isWinterTime(m_now);
    m_adjustedNow = getNow();
}

int Clock::hour() const
{
    return m_adjustedNow.hour();
}

int Clock::minute() const
{
    return m_adjustedNow.minute();
}

int Clock::second() const
{
    return m_adjustedNow.second();
}

int Clock::dayOfTheWeek() const
{
    return m_adjustedNow.dayOfTheWeek();
}

uint32_t Clock::time() const
{
    return Clock::toTime(hour(), minute(), second());
}

void Clock::toString(char* buffer) const
{
    int h = hour();
    int m = minute();

    int i = 0;
    if (h < 10)
        buffer[i++] = '0';
    else
        buffer[i++] = '0' + (h / 10);

    buffer[i++] = '0' + (h % 10);
    buffer[i++] = ':';

    if (m < 10)
        buffer[i++] = '0';
    else
        buffer[i++] = '0' + (m / 10);

    buffer[i++] = '0' + (m % 10);
    buffer[i] = '\0';
}

DateTime Clock::getNow() const
{
    if (m_startWinterTime == m_nowWinterTime)
        return m_now;

    return m_nowWinterTime
        ? m_now - TimeSpan(0, 1, 0, 0)
        : m_now + TimeSpan(0, 1, 0, 0);
}

uint32_t Clock::toTime(int hour, int minute, int second)
{
    return hour * 3600 + minute * 60 + second;
}

DateTime Clock::getSummerTimeChangeDate(int year)
{
    // UE complient: last sunday of march
    DateTime lastDayOfMarch = DateTime(year, 3, 31, 12, 0, 0);
    int dayOfTheWeek = lastDayOfMarch.dayOfTheWeek();
    return DateTime(year, 3, 31 - dayOfTheWeek, 2, 0, 0);
}

DateTime Clock::getWinterTimeChangeDate(int year)
{
    // UE complient: last sunday of october
    DateTime lastDayOfOctober = DateTime(year, 10, 31, 12, 0, 0);
    int dayOfTheWeek = lastDayOfOctober.dayOfTheWeek();
    return DateTime(year, 10, 31 - dayOfTheWeek, 2, 0, 0);
}

bool Clock::isWinterTime(const DateTime& date)
{
    int month = date.month();
    if (month < 3 || month > 10)
        return true;

    if (month > 3 || month < 10)
        return false;

    if (month == 3)
        return date < Clock::getSummerTimeChangeDate(date.year());
    else
        return date > Clock::getWinterTimeChangeDate(date.year());
}
