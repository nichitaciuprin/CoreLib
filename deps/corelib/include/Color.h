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

inline uint32_t ColorCreate(uint8_t a, uint8_t r, uint8_t g, uint8_t b)
{
    Color result = 0;
    result += a; result <<= 8;
    result += r; result <<= 8;
    result += g; result <<= 8;
    result += b;
    return result;
}
inline uint32_t ColorCreateRgb(uint8_t r, uint8_t g, uint8_t b)
{
    Color result = 0;
    result += r; result <<= 8;
    result += g; result <<= 8;
    result += b;
    return result;
}
inline uint32_t ColorCreateBw(uint32_t color)
{
    int r = (uint8_t)(color >> 8 * 2);
    int g = (uint8_t)(color >> 8 * 1);
    int b = (uint8_t)(color >> 8 * 0);

    uint8_t value = (r + g + b) / 3;
    float fraction = (float)value / 255;

    return 0x00FFFFFF * fraction;
}
inline uint32_t ColorCreateBwFloat(float t)
{
    uint8_t byte = (uint8_t)(255.0f * t);
    Color color = ColorCreateRgb(byte, byte, byte);
    return color;
}
inline uint32_t ColorCreateBwByte(uint8_t color)
{
    // TODO need fix?
    float fraction = (float)color / 255;
    return 0x00FFFFFF * fraction;
}
inline uint8_t ColorGetLightValue(uint32_t color)
{
    int r = (uint8_t)(color >> 8 * 2);
    int g = (uint8_t)(color >> 8 * 1);
    int b = (uint8_t)(color >> 8 * 0);

    uint8_t value = (r + g + b) / 3;

    return value;
}
