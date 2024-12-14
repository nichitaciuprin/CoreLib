#pragma once

#include "SysWindow.h"

class Window
{
public:
    Window(int x, int y, int clientWidth, int clientHeight) { instance = SysWindow_Create(x, y, clientWidth, clientHeight); }
    ~Window() { SysWindow_Destroy(instance); }
    bool Exists() const { return SysWindow_Exists(instance); }
    void Update() { SysWindow_Update(instance); }
    void SetPixel(int x, int y, uint32_t pixel) { SysWindow_SetPixel(instance, x, y, pixel); }
    void SetPixels(uint32_t* pixels, int width, int height) { SysWindow_SetPixels(instance, pixels, width, height); }
    void SetPixelsScaled(uint32_t* pixels, int width, int height, int scale) { SysWindow_SetPixelsScaled(instance, pixels, width, height, scale); }
    void SetPixelsScaled2(uint8_t* pixels, int width, int height, int scale) { SysWindow_SetPixelsScaled2(instance, pixels, width, height, scale); }
    bool KeyDown_W() { return SysWindow_KeyDown_W(instance); };
    bool KeyDown_A() { return SysWindow_KeyDown_A(instance); };
    bool KeyDown_S() { return SysWindow_KeyDown_S(instance); };
    bool KeyDown_D() { return SysWindow_KeyDown_D(instance); };
    bool KeyDown_E() { return SysWindow_KeyDown_E(instance); };
    bool KeyDown_Q() { return SysWindow_KeyDown_Q(instance); };
    bool KeyDown_UP() { return SysWindow_KeyDown_UP(instance); };
    bool KeyDown_LEFT() { return SysWindow_KeyDown_LEFT(instance); };
    bool KeyDown_DOWN() { return SysWindow_KeyDown_DOWN(instance); };
    bool KeyDown_RIGHT() { return SysWindow_KeyDown_RIGHT(instance); };

private:
    SysWindow* instance;
};
