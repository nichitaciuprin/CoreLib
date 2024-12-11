#include "BaseExt.h"
#include "SysHelper.h"
#include "HelperExt.h"
#include "BitmapClass.h"
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

        auto time = (float)clock() / 1000;

        Camera camera = { Vector3Zero(), time, 0 };

        BitmapReset(bitmap);
        BitmapSetView(bitmap, &camera);

        {
            Vector3 position = { 0, 0, 0 };
            Vector3 rotation = { 0, 0, 0 };
            Vector3 scale = { 1, 1, 4 };
            BitmapDrawCubeWire(bitmap, position, rotation, scale, COLOR_RED);
        }

        SysWindow_SetPixels(window, bitmap->pixels, bitmap->width, bitmap->height);
        SysWindow_Update(window);

        FixedTimeEnd();
    }

    return 0;
}
