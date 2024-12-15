#include "SysHelper.h"
#include "SysWindow.h"
#include "BaseMath.hpp"
#include "Bitmap.h"
#include "BitmapResize.h"
#include "BaseLang.hpp"

void Draw(Bitmap* bitmap, Camera camera)
{
    // float time = GetTime();

    BitmapReset(bitmap);
    BitmapSetView(bitmap, &camera);

    {
        Vector3 v0 = { +5, 0, +5 };
        Vector3 v1 = { +5, 0, -5 };
        Vector3 v2 = { -5, 0, -5 };
        Vector3 v3 = { -5, 0, +5 };
        BitmapDrawPoligon(bitmap, v0, v1, v2, v3, COLOR_WHITE);
    }

    Vector3 origin = camera.position;
    Vector3 dirNorm = CameraGetAxisZ(&camera);

    Vector3 v0 = {  0, -5, 10 };
    Vector3 v1 = { -5, +5, 10 };
    Vector3 v2 = { +5, +5, 10 };

    bool isHit = RaycastTriangle(origin, dirNorm, v0, v1, v2);
    Color color = isHit ? COLOR_RED : COLOR_GREEN;

    BitmapDrawTriangle(bitmap, v0, v1, v2, color);

    BitmapFillCross(bitmap, COLOR_WHITE);
}

int main()
{
    auto size = 512;

    Bitmap bitmap = BitmapCreate(size, size);
    auto window = SysWindowCreate(700, 100, size, size);

    BitmapSetPerspective(&bitmap, size, size, 0.1f, 1000.0f);

    Camera camera = { 0, 0, 0 };

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

        CameraUpdateRotation(&camera, 0.0030f, left, up, down, right);
        CameraUpdatePosition(&camera, 0.0010f, w, a, s, d, e, q);

        Draw(&bitmap, camera);

        SysWindowSetPixels(window, bitmap.pixels, bitmap.width, bitmap.height);
        SysWindowUpdate(window);

        SysHelperFixedTimeEnd();
    }

    return 0;
}
