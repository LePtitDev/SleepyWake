#include <Adafruit_ST7735.h>

#include "renderer.h"
#include "resources.h"

#define TFT_CS     8
#define TFT_RST    9
#define TFT_DC     10

Renderer::Renderer() :
    m_tft(TFT_CS, TFT_DC, TFT_RST),
    m_pict1_data_1 CAT_PIXELS_1, m_pict1_data_2 CAT_PIXELS_2, m_pict1_data_3 CAT_PIXELS_3,
    m_pict2_data_1 CAT_ALT_PIXELS_1, m_pict2_data_2 CAT_ALT_PIXELS_2, m_pict2_data_3 CAT_ALT_PIXELS_3,
    m_pict1_color_1(CAT_COLOR_1), m_pict1_color_2(CAT_COLOR_2), m_pict1_color_3(CAT_COLOR_3),
    m_pict1_width(CAT_PIXELS_WIDTH), m_pict1_height(CAT_PIXELS_HEIGHT),
    m_pict2_width(CAT_ALT_PIXELS_WIDTH), m_pict2_height(CAT_ALT_PIXELS_HEIGHT),
    m_symb1_data SYM_PIXELS_1, m_symb2_data SYM_PIXELS_2, m_symb_color(CAT_COLOR_1),
    m_symb3_data SYM_ALT_PIXELS_1, m_symb4_data SYM_ALT_PIXELS_2,
    m_symb1_width(SYM_PIXELS_1_WIDTH), m_symb1_height(SYM_PIXELS_1_HEIGHT),
    m_symb2_width(SYM_PIXELS_2_WIDTH), m_symb2_height(SYM_PIXELS_2_HEIGHT),
    m_symb3_width(SYM_ALT_PIXELS_1_WIDTH), m_symb3_height(SYM_ALT_PIXELS_1_HEIGHT),
    m_symb4_width(SYM_ALT_PIXELS_2_WIDTH), m_symb4_height(SYM_ALT_PIXELS_2_HEIGHT),
    m_num_0_data ZERO_PIXELS,
    m_num_1_data ONE_PIXELS,
    m_num_2_data TWO_PIXELS,
    m_num_3_data THREE_PIXELS,
    m_num_4_data FOUR_PIXELS,
    m_num_5_data FIVE_PIXELS,
    m_num_6_data SIX_PIXELS,
    m_num_7_data SEVEN_PIXELS,
    m_num_8_data EIGHT_PIXELS,
    m_num_9_data NINE_PIXELS,
    m_num_s_data SEPARATOR_PIXELS,
    m_num_width(NUM_PIXELS_WIDTH), m_num_height(NUM_PIXELS_HEIGHT),
    m_altMode(false), m_clockMode(false), m_pictRenderReq(true), m_symbRenderReq(true), m_clockRenderReq(true), m_symbolsSec(0),
    m_clockHour(-1), m_clockMinute(-1), m_clockStr { 0, 0, 0, 0, 0, 0 }
{
}

void Renderer::setup()
{
    m_tft.initR(INITR_BLACKTAB);
    m_tft.fillScreen(ST7735_BLACK);
}

void Renderer::loop()
{
    if (m_pictRenderReq)
    {
        m_pictRenderReq = false;

        m_tft.fillScreen(ST7735_BLACK);

        if (!m_altMode)
        {
            m_tft.drawBitmap(32, 24, m_pict1_data_1, m_pict1_width, m_pict1_height, m_pict1_color_1);
            m_tft.drawBitmap(32, 24, m_pict1_data_2, m_pict1_width, m_pict1_height, m_pict1_color_2);
            m_tft.drawBitmap(32, 24, m_pict1_data_3, m_pict1_width, m_pict1_height, m_pict1_color_3);
        }
        else
        {
            m_tft.drawBitmap(32, 32, m_pict2_data_1, m_pict2_width, m_pict2_height, m_pict1_color_1);
            m_tft.drawBitmap(32, 32, m_pict2_data_2, m_pict2_width, m_pict2_height, m_pict1_color_2);
            m_tft.drawBitmap(32, 32, m_pict2_data_3, m_pict2_width, m_pict2_height, m_pict1_color_3);
        }
    }

    if (m_symbRenderReq)
    {
        m_symbRenderReq = false;

        if (!m_altMode)
        {
            if (m_symbolsSec % 2)
            {
                m_tft.fillRect(36, 140, m_symb1_width, m_symb1_height, ST7735_BLACK);
                m_tft.fillRect(46, 126, m_symb2_width, m_symb2_height, ST7735_BLACK);
                m_tft.drawBitmap(46, 140, m_symb1_data, m_symb1_width, m_symb1_height, m_symb_color);
                m_tft.drawBitmap(52, 126, m_symb2_data, m_symb2_width, m_symb2_height, m_symb_color);
            }
            else
            {
                m_tft.fillRect(46, 140, m_symb1_width, m_symb1_height, ST7735_BLACK);
                m_tft.fillRect(52, 126, m_symb2_width, m_symb2_height, ST7735_BLACK);
                m_tft.drawBitmap(36, 140, m_symb1_data, m_symb1_width, m_symb1_height, m_symb_color);
                m_tft.drawBitmap(46, 126, m_symb2_data, m_symb2_width, m_symb2_height, m_symb_color);
            }
        }
        else
        {
            if (m_symbolsSec % 2)
            {
                m_tft.fillRect(38, 2, m_symb3_width, m_symb3_height, ST7735_BLACK);
                m_tft.fillRect(38, 136, m_symb4_width, m_symb4_height, ST7735_BLACK);
                m_tft.drawBitmap(42, 8, m_symb3_data, m_symb3_width, m_symb3_height, m_symb_color);
                m_tft.drawBitmap(42, 130, m_symb4_data, m_symb4_width, m_symb4_height, m_symb_color);
            }
            else
            {
                m_tft.fillRect(42, 8, m_symb3_width, m_symb3_height, ST7735_BLACK);
                m_tft.fillRect(42, 130, m_symb4_width, m_symb4_height, ST7735_BLACK);
                m_tft.drawBitmap(38, 2, m_symb3_data, m_symb3_width, m_symb3_height, m_symb_color);
                m_tft.drawBitmap(38, 136, m_symb4_data, m_symb4_width, m_symb4_height, m_symb_color);
            }
        }
    }

    if (m_clockRenderReq)
    {
        m_clockRenderReq = false;

        m_tft.fillRect(106, 100 - 4 * m_num_height, m_num_width, m_num_height * 5, ST7735_BLACK);

        uint16_t charColor = m_clockMode ? ST7735_WHITE : 0x10A2;

        int strY = 100;
        for (int i = 0; i < 6; i++)
        {
            renderChar(m_clockStr[i], 106, strY, charColor);
            strY -= 16;
        }
    }
}

void Renderer::setAltMode(bool value)
{
    if (m_altMode != value)
    {
        m_pictRenderReq = true;
        m_symbRenderReq = true;
    }

    m_altMode = value;
}

void Renderer::setClockMode(bool value)
{
    if (m_clockMode != value)
    {
        m_clockRenderReq = true;
    }

    m_clockMode = value;
}

void Renderer::updateClock(Clock& clock)
{
    int sec = clock.second();
    if (sec != m_symbolsSec)
        m_symbRenderReq = true;

    m_symbolsSec = sec;

    int hour = clock.hour();
    int minute = clock.minute();
    if (hour != m_clockHour || minute != m_clockMinute)
    {
        m_clockRenderReq = true;
        clock.toString(m_clockStr);
    }

    m_clockHour = hour;
    m_clockMinute = minute;
}

void Renderer::renderChar(char c, uint16_t x, uint16_t y, uint16_t color)
{
    switch (c)
    {
        case '0':
            m_tft.drawBitmap(x, y, m_num_0_data, m_num_width, m_num_height, color);
            break;
        case '1':
            m_tft.drawBitmap(x, y, m_num_1_data, m_num_width, m_num_height, color);
            break;
        case '2':
            m_tft.drawBitmap(x, y, m_num_2_data, m_num_width, m_num_height, color);
            break;
        case '3':
            m_tft.drawBitmap(x, y, m_num_3_data, m_num_width, m_num_height, color);
            break;
        case '4':
            m_tft.drawBitmap(x, y, m_num_4_data, m_num_width, m_num_height, color);
            break;
        case '5':
            m_tft.drawBitmap(x, y, m_num_5_data, m_num_width, m_num_height, color);
            break;
        case '6':
            m_tft.drawBitmap(x, y, m_num_6_data, m_num_width, m_num_height, color);
            break;
        case '7':
            m_tft.drawBitmap(x, y, m_num_7_data, m_num_width, m_num_height, color);
            break;
        case '8':
            m_tft.drawBitmap(x, y, m_num_8_data, m_num_width, m_num_height, color);
            break;
        case '9':
            m_tft.drawBitmap(x, y, m_num_9_data, m_num_width, m_num_height, color);
            break;
        case ':':
            m_tft.drawBitmap(x, y, m_num_s_data, m_num_width, m_num_height, color);
            break;
    }
}
