#pragma once

// TODO

#include "SysWindow.h"
#include "Bitmap.h"

bool AdaptBitmapToWindowInit = true;
int AdaptBitmapToWindowWidth = 0;
int AdaptBitmapToWindowHeight = 0;
void AdaptBitmapToWindow(Bitmap* bitmap, SysWindow* window)
{
    if (AdaptBitmapToWindowInit)
    {
        AdaptBitmapToWindowInit = false;
        AdaptBitmapToWindowWidth = SysWindow_GetWidth(window);
        AdaptBitmapToWindowHeight = SysWindow_GetHeight(window);
        return;
    }

    int width = SysWindow_GetWidth(window);
    int height = SysWindow_GetHeight(window);

    bool sizeChanged =
        AdaptBitmapToWindowWidth != width ||
        AdaptBitmapToWindowHeight != height;

    if (!sizeChanged) return;

    AdaptBitmapToWindowWidth = width;
    AdaptBitmapToWindowHeight = height;

    BitmapResize(bitmap, width, height);
    BitmapSetPerspective(bitmap, width, height, bitmap->near, 1000.0f);
}
