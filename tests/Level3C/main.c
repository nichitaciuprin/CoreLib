#include "SysHelper.h"
#include "SysWindow.h"
#include "BaseMath.h"
#include "Bitmap.h"
#include "BitmapResize.h"

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

    Vector3 p0 = { +size, 0, +size }; p0 = Vector3Add(p0, position);
    Vector3 p1 = { +size, 0, -size }; p1 = Vector3Add(p1, position);
    Vector3 p2 = { -size, 0, -size }; p2 = Vector3Add(p2, position);
    Vector3 p3 = { -size, 0, +size }; p3 = Vector3Add(p3, position);

    BitmapDrawPoligon(bitmap, p0, p1, p2, p3, COLOR_WHITE);
    BitmapDrawTriangle(bitmap, p0, p1, p2, COLOR_WHITE);
}
void Draw(Bitmap* bitmap, Camera camera)
{
    BitmapReset(bitmap);
    BitmapSetView(bitmap, &camera);

    Vector3 position = { 0, 0.5f, 0 };

    DrawPlane(bitmap, Vector3Zero());
    DrawCube(bitmap, position);

    float time = GetTime();

    time /= 1000;

    float x = MathSin(time) * 4;
    float z = MathCos(time) * 4;

    Vector3 lightPosition = { x, 5, z };

    BitmapApplyLightAndShadows(bitmap, lightPosition);

    Vector3 scale = { 1, 1, 1 };

    BitmapDrawCube(bitmap, lightPosition, Vector3Zero(), scale, COLOR_WHITE);
}

int main()
{
    int size = 512;

    Bitmap bitmap = BitmapCreate(size, size);
    SysWindow* window = SysWindowCreate(700, 100, size, size);

    BitmapSetPerspective(&bitmap, size, size, 0.1f, 1000.0f);

    Camera camera = { 0, 1.70f, -10 };

    while (SysWindowExists(window))
    {
        FixedTimeStart();

        AdaptBitmapToWindow(&bitmap, window);

        bool left = SysWindowKeyDownLEFT(window);
        bool up = SysWindowKeyDownUP(window);
        bool down = SysWindowKeyDownDOWN(window);
        bool right = SysWindowKeyDownRIGHT(window);

        bool w = SysWindowKeyDownW(window);
        bool a = SysWindowKeyDownA(window);
        bool s = SysWindowKeyDownS(window);
        bool d = SysWindowKeyDownD(window);
        bool e = SysWindowKeyDownE(window);
        bool q = SysWindowKeyDownQ(window);

        CameraUpdateRotation(&camera, 0.0230f, left, up, down, right);
        CameraUpdatePosition(&camera, 0.0020f, w, a, s, d, e, q);

        Draw(&bitmap, camera);

        SysWindowSetPixels(window, bitmap.pixels, bitmap.width, bitmap.height);
        SysWindowUpdate(window);

        FixedTimeEnd();
    }

    return 0;
}
