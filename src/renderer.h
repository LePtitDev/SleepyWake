#ifndef RENDERER_H
#define RENDERER_H

#include <Adafruit_ST7735.h>

#include "clock.h"
#include "resources.h"

class Renderer
{
private:

    Adafruit_ST7735 m_tft;

    uint8_t m_pict1_data_1[CAT_PIXELS_DATA_LENGTH];
    uint8_t m_pict1_data_2[CAT_PIXELS_DATA_LENGTH];
    uint8_t m_pict1_data_3[CAT_PIXELS_DATA_LENGTH];

    uint8_t m_pict2_data_1[CAT_ALT_PIXELS_DATA_LENGTH];
    uint8_t m_pict2_data_2[CAT_ALT_PIXELS_DATA_LENGTH];
    uint8_t m_pict2_data_3[CAT_ALT_PIXELS_DATA_LENGTH];

    uint16_t m_pict1_color_1;
    uint16_t m_pict1_color_2;
    uint16_t m_pict1_color_3;

    int m_pict1_width;
    int m_pict1_height;
    int m_pict2_width;
    int m_pict2_height;

    uint8_t m_symb1_data[SYM_PIXELS_1_DATA_LENGTH];
    uint8_t m_symb2_data[SYM_PIXELS_2_DATA_LENGTH];
    uint8_t m_symb3_data[SYM_ALT_PIXELS_1_DATA_LENGTH];
    uint8_t m_symb4_data[SYM_ALT_PIXELS_2_DATA_LENGTH];
    uint16_t m_symb_color;

    int m_symb1_width;
    int m_symb1_height;
    int m_symb2_width;
    int m_symb2_height;
    int m_symb3_width;
    int m_symb3_height;
    int m_symb4_width;
    int m_symb4_height;

    uint8_t m_num_0_data[NUM_PIXELS_DATA_LENGTH];
    uint8_t m_num_1_data[NUM_PIXELS_DATA_LENGTH];
    uint8_t m_num_2_data[NUM_PIXELS_DATA_LENGTH];
    uint8_t m_num_3_data[NUM_PIXELS_DATA_LENGTH];
    uint8_t m_num_4_data[NUM_PIXELS_DATA_LENGTH];
    uint8_t m_num_5_data[NUM_PIXELS_DATA_LENGTH];
    uint8_t m_num_6_data[NUM_PIXELS_DATA_LENGTH];
    uint8_t m_num_7_data[NUM_PIXELS_DATA_LENGTH];
    uint8_t m_num_8_data[NUM_PIXELS_DATA_LENGTH];
    uint8_t m_num_9_data[NUM_PIXELS_DATA_LENGTH];
    uint8_t m_num_s_data[NUM_PIXELS_DATA_LENGTH];

    int m_num_width;
    int m_num_height;

    int m_symbolsSec;

    bool m_altMode;
    bool m_clockMode;
    bool m_pictRenderReq;
    bool m_symbRenderReq;
    bool m_clockRenderReq;

    int m_clockHour;
    int m_clockMinute;
    char m_clockStr[6];

public:

    Renderer();

    void setup();
    void loop();

    void setAltMode(bool value);
    void setClockMode(bool value);
    void updateClock(Clock& clock);

private:

    void renderChar(char c, uint16_t x, uint16_t y, uint16_t color);

};

#endif // RENDERER_H
