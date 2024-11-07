#pragma once

typedef uint32_t Pixel;

const Pixel COLOR_BLACK      = 0x00000000;
const Pixel COLOR_WHITE      = 0x00FFFFFF;
const Pixel COLOR_RED        = 0x00FF0000;
const Pixel COLOR_GREEN      = 0x0000FF00;
const Pixel COLOR_BLUE       = 0x000000FF;
const Pixel COLOR_YELLOW     = 0x00FFFF00;
const Pixel COLOR_MAGENTA    = 0x00FF00FF;
const Pixel COLOR_CYAN       = 0x0000FFFF;
const Pixel COLOR_ORANGE     = 0x00FF8000;
const Pixel COLOR_PINK       = 0x00FF0080;
const Pixel COLOR_LIME       = 0x0080FF00;
const Pixel COLOR_GREENCOLD  = 0x0000FF80;
const Pixel COLOR_VIOLET     = 0x008000FF;
const Pixel COLOR_LIGHTBLUE  = 0x000080FF;

uint32_t PixelToBwPixel(uint32_t pixel)
{
    int r = (uint8_t)((pixel >> 8 * 2));
    int g = (uint8_t)((pixel >> 8 * 1));
    int b = (uint8_t)((pixel >> 8 * 0));

    uint8_t value = ((r + g + b) / 3);
    float fraction = (float)value / 255;

    return 0x00FFFFFF * fraction;
}
uint8_t PixelToLightValue(uint32_t pixel)
{
    int r = (uint8_t)((pixel >> 8 * 2));
    int g = (uint8_t)((pixel >> 8 * 1));
    int b = (uint8_t)((pixel >> 8 * 0));

    uint8_t value = ((r + g + b) / 3);

    return value;
}
uint32_t LightValueToPixel(uint8_t pixel)
{
    float fraction = (float)pixel / 255;
    return 0x00FFFFFF * fraction;
}
