#include "button.h"

#include <Arduino.h>

Button::Button(int pin)
{
    m_pin = pin;
    m_state = 1;
    m_time = 0;
    m_click = false;
    m_longClick = false;
    m_longClickState = false;
}

void Button::setup()
{
    pinMode(m_pin, INPUT_PULLUP);
}

void Button::loop()
{
    int state = digitalRead(m_pin);
    m_click = m_state != state && !state;
    m_state = state;

    if (m_click)
    {
      m_time = millis();
    }

    bool longClickState = !state && (millis() - m_time > 3000);
    m_longClick = m_longClickState != longClickState && longClickState;
    m_longClickState = longClickState;
}

bool Button::click() const
{
    return m_click;
}

bool Button::longClick() const
{
    return m_longClick;
}
