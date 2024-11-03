#ifndef SYSWINDOW_H
#define SYSWINDOW_H

#include <stdint.h>
#include <stdbool.h>

typedef struct SysWindow SysWindow;
SysWindow* SysWindow_Create(int x, int y, int clientWidth, int clientHeight);
bool SysWindow_Exists(SysWindow* instance);
void SysWindow_Destroy(SysWindow* instance);
void SysWindow_Update(SysWindow* instance);
void SysWindow_SetPixel(SysWindow* instance, int x, int y, uint32_t pixel);
void SysWindow_SetPixels(SysWindow* instance, uint32_t* pixels, int width, int height);
void SysWindow_SetPixelsScaled(SysWindow* instance, uint32_t* pixels, int width, int height, int scale);
void SysWindow_SetPixelsScaled2(SysWindow* instance, uint8_t* pixels, int width, int height, int scale);
bool SysWindow_KeyDown_W(SysWindow* instance);
bool SysWindow_KeyDown_A(SysWindow* instance);
bool SysWindow_KeyDown_S(SysWindow* instance);
bool SysWindow_KeyDown_D(SysWindow* instance);
bool SysWindow_KeyDown_E(SysWindow* instance);
bool SysWindow_KeyDown_Q(SysWindow* instance);
bool SysWindow_KeyDown_UP(SysWindow* instance);
bool SysWindow_KeyDown_LEFT(SysWindow* instance);
bool SysWindow_KeyDown_DOWN(SysWindow* instance);
bool SysWindow_KeyDown_RIGHT(SysWindow* instance);

#endif
