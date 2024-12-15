#include "SysHelper.h"
#include "SysWindow.h"
#include "BaseMath.hpp"
#include "Bitmap.h"
#include "BitmapResize.h"
#include "BaseLang.hpp"

void DrawCube(Bitmap* bitmap, Vector3 position)
{
    Vector3 rotation = { 0, 0, 0 };
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
    BitmapDrawTriangle(bitmap, p0, p1, p2, COLOR_WHITE);
}
void Draw(Bitmap* bitmap, Camera camera)
{
    BitmapReset(bitmap);
    BitmapSetView(bitmap, &camera);

    DrawPlane(bitmap, { 0, 0, 0 });
    DrawCube(bitmap, { 0, 0.5f, 0 });

    float time = SysHelperGetTime();

    time /= 1000;

    float x = MathSin(time) * 4;
    float z = MathCos(time) * 4;

    Vector3 lightPosition = { x, 5, z };

    BitmapApplyLightAndShadows(bitmap, lightPosition);

    BitmapDrawCube(bitmap, lightPosition, {}, { 1, 1, 1 }, COLOR_WHITE);
}

int main()
{
    auto size = 512;

    auto bitmap = BitmapCreate(size, size);
    auto window = SysWindowCreate(700, 100, size, size);

    BitmapSetPerspective(&bitmap, size, size, 0.1f, 1000.0f);

    Camera camera = { 0, 1.70f, -10 };

    while (SysWindowExists(window))
    {
        SysHelperFixedTimeStart();

        AdaptBitmapToWindow(&bitmap, window);

        auto left = SysWindowKeyDownLEFT(window);
        auto up = SysWindowKeyDownUP(window);
        auto down = SysWindowKeyDownDOWN(window);
        auto right = SysWindowKeyDownRIGHT(window);

        auto w = SysWindowKeyDownW(window);
        auto a = SysWindowKeyDownA(window);
        auto s = SysWindowKeyDownS(window);
        auto d = SysWindowKeyDownD(window);
        auto e = SysWindowKeyDownE(window);
        auto q = SysWindowKeyDownQ(window);

        CameraUpdateRotation(&camera, 0.0230f, left, up, down, right);
        CameraUpdatePosition(&camera, 0.0020f, w, a, s, d, e, q);

        Draw(&bitmap, camera);

        SysWindowSetPixels(window, bitmap.pixels, bitmap.width, bitmap.height);
        SysWindowUpdate(window);

        SysHelperFixedTimeEnd();
    }

    return 0;
}
