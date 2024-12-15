#include "SysWindow.h"
#include "BaseMath.hpp"
#include "BaseLang.hpp"
#include "Bitmap.h"

int main()
{
    auto width = 10;
    auto height = 10;

    auto scale = 40;

    auto bitmap_ = BitmapCreate(width, height);
    auto bitmap = &bitmap_;
    auto window = SysWindowCreate(700, 100, width * scale, height * scale);

    while (SysWindowExists(window))
    {
        BitmapReset(bitmap);

        float zFar = 0;
        float zClose = -10;

        {
            Vector3 p0 = { 1, 2, zFar };
            Vector3 p1 = { 8, 2, zClose };
            BitmapDrawLineScreenSpace(bitmap, p0, p1, COLOR_RED);
        }
        {
            Vector3 p0 = { 7, 1, zFar };
            Vector3 p1 = { 7, 8, zClose };
            BitmapDrawLineScreenSpace(bitmap, p0, p1, COLOR_GREEN);
        }
        {
            Vector3 p1 = { 8, 7, zFar };
            Vector3 p0 = { 1, 7, zClose };
            BitmapDrawLineScreenSpace(bitmap, p0, p1, COLOR_BLUE);
        }
        {
            Vector3 p1 = { 2, 8, zFar };
            Vector3 p0 = { 2, 1, zClose };
            BitmapDrawLineScreenSpace(bitmap, p0, p1, COLOR_YELLOW);
        }

        SysWindowSetPixelsScaled(window, bitmap->pixels, bitmap->width, bitmap->height, scale);

        SysWindowUpdate(window);
    }

    return 0;
}
