#ifndef CLOCK_H
#define CLOCK_H

#include <RTClib.h>

class Clock
{
private:

    RTC_DS3231 m_rtc;
    bool m_hasError;
    DateTime m_start;
    DateTime m_now;
    DateTime m_adjustedNow;
    bool m_startWinterTime;
    bool m_nowWinterTime;

public:

    Clock();

    void setup();
    void loop();

    int hour() const;
    int minute() const;
    int second() const;
    int dayOfTheWeek() const;

    uint32_t time() const;

    /**
     * Write clock value into a char array (length = 6)
     */
    void toString(char* buffer) const;

    static uint32_t toTime(int hour, int minute, int second);

    static DateTime getSummerTimeChangeDate(int year);
    static DateTime getWinterTimeChangeDate(int year);
    static bool isWinterTime(const DateTime& date);

private:

    DateTime getNow() const;

};

#endif // CLOCK_H
