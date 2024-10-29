#include <Arduino.h>

#include "button.h"
#include "clock.h"
#include "renderer.h"
#include "config.h"
#include "resources.h"

#define BT_1   2

Button m_bt1 = Button(BT_1);
Clock m_clock;
Renderer m_renderer;
Config m_config;

uint32_t m_clickTime;
bool m_invertMode;

void setup() {
  Serial.begin(9600);

  m_bt1.setup();
  m_clock.setup();
  m_renderer.setup();

  m_clickTime = m_clock.time();
  m_invertMode = false;
}

void loop() {
  m_bt1.loop();
  m_clock.loop();

  m_renderer.updateClock(m_clock);
  m_config.updateClock(m_clock);

  if (m_bt1.click())
  {
    m_clickTime = m_clock.time();
  }

  if (m_bt1.longClick())
  {
    m_invertMode = !m_invertMode;
  }

  m_renderer.setAltMode(m_invertMode ? m_config.sleepMode() : !m_config.sleepMode());
  m_renderer.setClockMode(m_clock.time() - m_clickTime < 10);
  m_renderer.loop();
}
