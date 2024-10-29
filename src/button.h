#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>

class Button
{
private:

    int m_pin;
    int m_state;
    uint32_t m_time;

    bool m_click;
    bool m_longClick;
    bool m_longClickState;

public:

    Button(int pin);

    void setup();
    void loop();

    bool click() const;
    bool longClick() const;

};

#endif // BUTTON_H
