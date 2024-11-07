#pragma once

typedef uint32_t Color;

const Color COLOR_BLACK      = 0x00000000;
const Color COLOR_WHITE      = 0x00FFFFFF;
const Color COLOR_RED        = 0x00FF0000;
const Color COLOR_GREEN      = 0x0000FF00;
const Color COLOR_BLUE       = 0x000000FF;
const Color COLOR_YELLOW     = 0x00FFFF00;
const Color COLOR_MAGENTA    = 0x00FF00FF;
const Color COLOR_CYAN       = 0x0000FFFF;
const Color COLOR_ORANGE     = 0x00FF8000;
const Color COLOR_PINK       = 0x00FF0080;
const Color COLOR_LIME       = 0x0080FF00;
const Color COLOR_GREENCOLD  = 0x0000FF80;
const Color COLOR_VIOLET     = 0x008000FF;
const Color COLOR_LIGHTBLUE  = 0x000080FF;

uint32_t ColorToBwColor(uint32_t color)
{
    int r = (uint8_t)(color >> 8 * 2);
    int g = (uint8_t)(color >> 8 * 1);
    int b = (uint8_t)(color >> 8 * 0);

    uint8_t value = (r + g + b) / 3;
    float fraction = (float)value / 255;

    return 0x00FFFFFF * fraction;
}
uint8_t ColorToLightValue(uint32_t color)
{
    int r = (uint8_t)(color >> 8 * 2);
    int g = (uint8_t)(color >> 8 * 1);
    int b = (uint8_t)(color >> 8 * 0);

    uint8_t value = (r + g + b) / 3;

    return value;
}
uint32_t LightValueToColor(uint8_t color)
{
    float fraction = (float)color / 255;
    return 0x00FFFFFF * fraction;
}
