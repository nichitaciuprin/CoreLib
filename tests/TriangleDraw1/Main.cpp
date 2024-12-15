#include "SysHelper.h"
#include "SysWindow.h"
#include "BaseLang.hpp"
#include "BaseMath.hpp"
#include "Bitmap.h"

int main()
{
    auto size = 400;

    auto _bitmap = BitmapCreate(size, size);
    auto bitmap = &_bitmap;
    auto window = SysWindowCreate(700, 100, size, size);

    while (SysWindowExists(window))
    {
        BitmapReset(bitmap);

        Vector3 p0;
        Vector3 p1;
        Vector3 p2;
        Vector3 p3;

        // MAIN
        {
            p0 = { 250,  50 };
            p1 = { 200, 100 };
            p2 = { 300, 150 };
            BitmapDrawTriangleScreenspace(bitmap, p0, p1, p2, COLOR_RED);

            p0 = { 150,  50 };
            p1 = { 200, 100 };
            p2 = { 100,  150 };
            BitmapDrawTriangleScreenspace(bitmap, p0, p1, p2, COLOR_GREEN);
        }

        // SQUARES
        {
            p0 = {  0,  0 };
            p1 = { 25,  0 };
            p2 = { 25, 25 };
            p3 = {  0, 25 };
            BitmapDrawTriangleScreenspace(bitmap, p2, p3, p0, COLOR_RED);
            BitmapDrawTriangleScreenspace(bitmap, p0, p1, p2, COLOR_GREEN);

            p0 = {  0 + 50,  0 };
            p1 = { 25 + 50,  0 };
            p2 = { 25 + 50, 25 };
            p3 = {  0 + 50, 25 };
            BitmapDrawTriangleScreenspace(bitmap, p0, p3, p2, COLOR_BLUE);
            BitmapDrawTriangleScreenspace(bitmap, p1, p0, p2, COLOR_YELLOW);
        }

        // MALTA CROSS
        {
            p0 = { 200, 250 };

            p1 = { 150, 250 };
            p2 = { 100, 200 }; BitmapDrawTriangleScreenspace(bitmap, p0, p1, p2, COLOR_RED);
            p2 = { 100, 300 }; BitmapDrawTriangleScreenspace(bitmap, p2, p0, p1, COLOR_RED);

            p1 = { 250, 250 };
            p2 = { 300, 300 }; BitmapDrawTriangleScreenspace(bitmap, p1, p0, p2, COLOR_GREEN);
            p2 = { 300, 200 }; BitmapDrawTriangleScreenspace(bitmap, p1, p2, p0, COLOR_GREEN);

            p1 = { 200, 300 };
            p2 = { 150, 350 }; BitmapDrawTriangleScreenspace(bitmap, p0, p1, p2, COLOR_BLUE);
            p2 = { 250, 350 }; BitmapDrawTriangleScreenspace(bitmap, p0, p2, p1, COLOR_BLUE);

            p1 = { 200, 200 };
            p2 = { 150, 150 }; BitmapDrawTriangleScreenspace(bitmap, p0, p1, p2, COLOR_MAGENTA);
            p2 = { 250, 150 }; BitmapDrawTriangleScreenspace(bitmap, p0, p1, p2, COLOR_MAGENTA);
        }

        // ROMB
        {
            p1 = { 100,  50 };
            p2 = {  25, 125 };
            p0 = {  50,  75 }; BitmapDrawTriangleScreenspace(bitmap, p0, p1, p2, COLOR_ORANGE);
            p0 = {  75, 100 }; BitmapDrawTriangleScreenspace(bitmap, p0, p1, p2, COLOR_ORANGE);
        }

        BitmapFillBorder(bitmap, COLOR_GREEN);

        SysWindowSetPixels(window, bitmap->pixels, bitmap->width, bitmap->height);
        SysWindowUpdate(window);
    }

    return 0;
}
