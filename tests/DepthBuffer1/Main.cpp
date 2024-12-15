#include "SysHelper.h"
#include "SysWindow.h"
#include "BaseLang.hpp"
#include "BaseMath.hpp"
#include "Bitmap.h"

int main()
{
    auto width = 400;
    auto height = 400;

    auto bitmap_ = BitmapCreate(width, height);
    auto bitmap = &bitmap_;
    auto window = SysWindowCreate(700, 100, width, height);

    while (SysWindowExists(window))
    {
        BitmapReset(bitmap);

        float zFar = 10;
        float zClose = 9;

        {
            Vector3 p0 = { -0.2f,  0.6f,  zFar };
            Vector3 p1 = {  0.0f,  0.6f,  zFar };
            Vector3 p2 = {  0.4f, -0.6f,  zClose };
            BitmapDrawTriangleNdc(bitmap, p0, p1, p2, COLOR_RED);
        }
        {
            Vector3 p0 = {  0.6f, -0.2f,  zFar };
            Vector3 p1 = {  0.6f, -0.4f,  zFar };
            Vector3 p2 = { -0.8f, -0.2f,  zClose };
            BitmapDrawTriangleNdc(bitmap, p0, p1, p2, COLOR_GREEN);
        }
        {
            Vector3 p0 = { -0.4f, -0.4f,  zFar };
            Vector3 p1 = { -0.6f, -0.4f,  zFar };
            Vector3 p2 = {  0.2f,  0.6f,  zClose };
            BitmapDrawTriangleNdc(bitmap, p0, p1, p2, COLOR_BLUE);
        }

        BitmapFillBorder(bitmap, COLOR_GREEN);

        SysWindowSetPixels(window, bitmap->pixels, bitmap->width, bitmap->height);
        SysWindowUpdate(window);
    }

    return 0;
}
