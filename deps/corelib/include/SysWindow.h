#pragma once

#include <stdint.h>
#include <stdbool.h>

typedef struct SysWindow SysWindow;
SysWindow* SysWindowCreate(int x, int y, int clientWidth, int clientHeight);
bool SysWindowExists(SysWindow* instance);
void SysWindowDestroy(SysWindow* instance);
void SysWindowUpdate(SysWindow* instance);
void SysWindowSetPixel(SysWindow* instance, int x, int y, uint32_t pixel);
void SysWindowSetPixels(SysWindow* instance, uint32_t* pixels, int width, int height);
void SysWindowSetPixelsScaled(SysWindow* instance, uint32_t* pixels, int width, int height, int scale);
void SysWindowSetPixelsScaled2(SysWindow* instance, uint8_t* pixels, int width, int height, int scale);
bool SysWindowKeyDownW(SysWindow* instance);
bool SysWindowKeyDownA(SysWindow* instance);
bool SysWindowKeyDownS(SysWindow* instance);
bool SysWindowKeyDownD(SysWindow* instance);
bool SysWindowKeyDownE(SysWindow* instance);
bool SysWindowKeyDownQ(SysWindow* instance);
bool SysWindowKeyDownUP(SysWindow* instance);
bool SysWindowKeyDownLEFT(SysWindow* instance);
bool SysWindowKeyDownDOWN(SysWindow* instance);
bool SysWindowKeyDownRIGHT(SysWindow* instance);
int SysWindowGetWidth(SysWindow* instance);
int SysWindowGetHeight(SysWindow* instance);
