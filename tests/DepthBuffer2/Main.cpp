#include "BaseLang.hpp"
#include "SysHelper.h"
#include "BaseMath.hpp"
#include "Bitmap.hpp"
#include "Window.h"

int main()
{
    auto size = 512;

    auto _bitmap = BitmapCreate(size, size);
    auto bitmap = &_bitmap;
    auto window = SysWindow_Create(700, 100, size, size);

    BitmapSetPerspective(bitmap, size, size, 0.1f, 1000.0f);

    while (SysWindow_Exists(window))
    {
        FixedTimeStart();

        BitmapReset(bitmap);

        Camera camera = { 0, 0, 0 };

        BitmapReset(bitmap);
        BitmapSetView(bitmap, &camera);

        {
            auto time = (float)clock() / 1500;
            Vector3 position = { 0, 0, 2 };
            Vector3 rotation = { 0, time, 0 };
            Vector3 scale = { 1, 1, 1 };
            BitmapDrawCubeColored(bitmap, position, rotation, scale);
        }
        {
            Vector3 position = { 0.5f, 0.5f, 2 };
            Vector3 rotation = { 0, 0, 0 };
            Vector3 scale = { 1, 1, 1 };
            BitmapDrawCubeColored(bitmap, position, rotation, scale);
        }

        SysWindow_SetPixels(window, bitmap->pixels, bitmap->width, bitmap->height);
        SysWindow_Update(window);

        FixedTimeEnd();
    }

    return 0;
}
