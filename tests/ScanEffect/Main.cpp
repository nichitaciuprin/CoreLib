#include "SysHelper.h"
#include "SysWindow.h"
#include "BaseLang.hpp"
#include "BaseMath.hpp"
#include "Bitmap.h"
#include "Subgen.h"

int main()
{
    auto width = 200;
    auto height = 200;

    auto _bitmap = BitmapCreate(width, height);
    auto bitmap = &_bitmap;
    auto window = SysWindowCreate(700, 100, width, height);

    int iteration = 0;

    Subgen subgen = SubgenCreate(0);

    while (SysWindowExists(window))
    {
        int i1 = iteration;
        int i2 = SubgenNext(&subgen);
        int pixelCount = width * height;
        i1 %= pixelCount;
        i2 %= pixelCount;
        bitmap->pixels[i1] = SubgenNext(&subgen);
        bitmap->pixels[i2] = 0;
        iteration++;

        BitmapFillBorder(bitmap, COLOR_GREEN);

        SysWindowSetPixels(window, bitmap->pixels, bitmap->width, bitmap->height);
        SysWindowUpdate(window);
    }

    return 0;
}
