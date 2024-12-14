#include "SysHelper.h"
#include "SysWindow.h"
#include "BaseMath.hpp"
#include "Bitmap.h"
#include "BitmapResize.h"
#include "BaseLang.hpp"

void DrawCube(Bitmap* bitmap, Vector3 position, float time)
{
    Vector3 rotation = { 0, time, 0 };
    Vector3 scale = { 1, 1, 1 };

    BitmapDrawCubeColored(bitmap, position, rotation, scale);
    BitmapDrawCubeWire(bitmap, position, rotation, scale, COLOR_RED);
}
void DrawPlane(Bitmap* bitmap, Vector3 position)
{
    float size = 5;

    Vector3 p0 = { +size, 0, +size }; p0 += position;
    Vector3 p1 = { +size, 0, -size }; p1 += position;
    Vector3 p2 = { -size, 0, -size }; p2 += position;
    Vector3 p3 = { -size, 0, +size }; p3 += position;

    BitmapDrawPoligon(bitmap, p0, p1, p2, p3, COLOR_WHITE);
}
void Draw(Bitmap* bitmap, Camera camera)
{
    float time = GetTime();

    BitmapReset(bitmap);
    BitmapSetView(bitmap, &camera);

    DrawPlane(bitmap, { 0, 0, 0 });
    DrawCube(bitmap, { 0, 0.5f, 0 }, (float)time / 3000);
}

int main()
{
    auto size = 512;

    Bitmap bitmap = BitmapCreate(size, size);
    auto window = SysWindow_Create(700, 100, size, size);

    BitmapSetPerspective(&bitmap, size, size, 0.1f, 1000.0f);

    Camera camera = { 0, 1.70f, -10 };

    while (SysWindow_Exists(window))
    {
        FixedTimeStart();

        AdaptBitmapToWindow(&bitmap, window);

        auto left = SysWindow_KeyDown_LEFT(window);
        auto up = SysWindow_KeyDown_UP(window);
        auto down = SysWindow_KeyDown_DOWN(window);
        auto right = SysWindow_KeyDown_RIGHT(window);

        auto w = SysWindow_KeyDown_W(window);
        auto a = SysWindow_KeyDown_A(window);
        auto s = SysWindow_KeyDown_S(window);
        auto d = SysWindow_KeyDown_D(window);
        auto e = SysWindow_KeyDown_E(window);
        auto q = SysWindow_KeyDown_Q(window);

        CameraUpdateRotation(&camera, 0.0230f, left, up, down, right);
        CameraUpdatePosition(&camera, 0.0020f, w, a, s, d, e, q);

        Draw(&bitmap, camera);

        SysWindow_SetPixels(window, bitmap.pixels, bitmap.width, bitmap.height);
        SysWindow_Update(window);

        FixedTimeEnd();
    }

    return 0;
}
