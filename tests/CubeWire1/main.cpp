#include "BaseLang.hpp"
#include "SysHelper.h"
#include "BaseMath.hpp"
#include "Bitmap.hpp"
#include "SysWindow.hpp"

int main()
{
    auto size = 512;

    auto _bitmap = BitmapCreate(size, size);
    auto bitmap = &_bitmap;
    auto window = SysWindowCreate(700, 100, size, size);

    BitmapSetPerspective(bitmap, size, size, 0.1f, 1000.0f);

    while (SysWindowExists(window))
    {
        FixedTimeStart();

        BitmapReset(bitmap);

        auto time = (float)clock() / 400;

        Camera camera = { 0, 0, 0 };

        BitmapReset(bitmap);
        BitmapSetView(bitmap, &camera);

        {
            Vector3 position = { 0, 0, 2 };
            Vector3 rotation = { 0, time, 0 };
            Vector3 scale = { 1, 1, 1 };
            BitmapDrawCubeWire(bitmap, position, rotation, scale, COLOR_RED);
        }

        SysWindowSetPixels(window, bitmap->pixels, bitmap->width, bitmap->height);
        SysWindowUpdate(window);

        FixedTimeEnd();
    }

    return 0;
}
