#pragma once

#include "SysWindow.h"

class Window
{
public:
    Window(int x, int y, int clientWidth, int clientHeight) { instance = SysWindowCreate(x, y, clientWidth, clientHeight); }
    ~Window() { SysWindowDestroy(instance); }
    bool Exists() const { return SysWindowExists(instance); }
    void Update() { SysWindowUpdate(instance); }
    void SetPixel(int x, int y, uint32_t pixel) { SysWindowSetPixel(instance, x, y, pixel); }
    void SetPixels(uint32_t* pixels, int width, int height) { SysWindowSetPixels(instance, pixels, width, height); }
    void SetPixelsScaled(uint32_t* pixels, int width, int height, int scale) { SysWindowSetPixelsScaled(instance, pixels, width, height, scale); }
    void SetPixelsScaled2(uint8_t* pixels, int width, int height, int scale) { SysWindowSetPixelsScaled2(instance, pixels, width, height, scale); }
    bool KeyDown_W() { return SysWindowKeyDownW(instance); };
    bool KeyDown_A() { return SysWindowKeyDownA(instance); };
    bool KeyDown_S() { return SysWindowKeyDownS(instance); };
    bool KeyDown_D() { return SysWindowKeyDownD(instance); };
    bool KeyDown_E() { return SysWindowKeyDownE(instance); };
    bool KeyDown_Q() { return SysWindowKeyDownQ(instance); };
    bool KeyDown_UP() { return SysWindowKeyDownUP(instance); };
    bool KeyDown_LEFT() { return SysWindowKeyDownLEFT(instance); };
    bool KeyDown_DOWN() { return SysWindowKeyDownDOWN(instance); };
    bool KeyDown_RIGHT() { return SysWindowKeyDownRIGHT(instance); };

private:
    SysWindow* instance;
};
