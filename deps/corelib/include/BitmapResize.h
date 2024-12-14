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
        AdaptBitmapToWindowWidth = SysWindowGetWidth(window);
        AdaptBitmapToWindowHeight = SysWindowGetHeight(window);
        return;
    }

    int width = SysWindowGetWidth(window);
    int height = SysWindowGetHeight(window);

    bool sizeChanged =
        AdaptBitmapToWindowWidth != width ||
        AdaptBitmapToWindowHeight != height;

    if (!sizeChanged) return;

    AdaptBitmapToWindowWidth = width;
    AdaptBitmapToWindowHeight = height;

    BitmapResize(bitmap, width, height);
    BitmapSetPerspective(bitmap, width, height, bitmap->near, 1000.0f);
}
