#include "SysHelper.h"
#include "SysWindow.h"
#include "HelperExt.h"
#include "Bitmap.h"
#include "BitmapResize.h"
#include "BaseExt.h"

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
    BitmapDrawTriangle(bitmap, p0, p1, p2, COLOR_WHITE);
}
void Draw(Bitmap* bitmap, Camera camera)
{
    float time = GetTime();

    BitmapReset(bitmap);
    BitmapSetView(bitmap, &camera);

    // Vector3 lightPosition = { 0, 10, 0 };
    // Vector3 lightPosition = { 0, 10, MathPingPong(GetTime()/50, 120) - 10 };
    // Vector3 lightPosition = camera.position;

    // DrawPlane(bitmap, { 0, 0, 0 });
    // DrawCube(bitmap, { 0, 0.5f, 0 }, (float)time / 3000);

    // DrawPlane(bitmap, { 0, 0, 100 });
    // DrawCube(bitmap, { 0, 0.5f, 100 }, (float)time / 600);
    // DrawCube(bitmap, { 0, 1.5f, 100 }, (float)time / 300);

    // // bridge
    // {
    //     Vector3 p0 = { -1, 0,  2 };
    //     Vector3 p1 = { -1, 0, 95 };
    //     Vector3 p2 = {  1, 0, 95 };
    //     Vector3 p3 = {  1, 0,  2 };
    //     BitmapDrawPoligon(bitmap, p0, p1, p2, p3, COLOR_WHITE);
    // }

    // BitmapApplyLight(bitmap, lightPosition);
    // BitmapApplyLight2(bitmap, lightPosition);

    // float size = 5;

    // Vector3 p0 = { +size, 0, +size };
    // Vector3 p1 = { +size, 0, -size };
    // Vector3 p2 = { -size, 0, -size };

    // BitmapDrawTriangle(bitmap, p0, p1, p2, COLOR_WHITE);
    DrawPlane(bitmap, { 0, 0, 0 });
    // DrawCube(bitmap, { 0, 0.5f, 0 }, (float)time / 3000);
    DrawCube(bitmap, { 0, 0.5f, 0 }, 0);

    // BitmapCreateSurfacePoints(bitmap);

    float x = MathSin(time / 1000) * 4;
    float z = MathCos(time / 1000) * 4;

    Vector3 lightPosition = { x, 5, z };

    BitmapApplyLightAndShadows(bitmap, lightPosition);

    BitmapDrawCube(bitmap, lightPosition, {}, { 1, 1, 1 }, COLOR_WHITE);
    // DrawCube(bitmap, { 0, 0.5f, 0 }, (float)time / 3000);

    // for (size_t i = 0; i < points.size(); i++)
    // {
    //     if (i % 100 != 0) continue;

    //     auto p = points[i] + Vector3Up() / 10;

    //     // float size = 5;
    //     // Vector3 p0 = { +size, 0, +size };
    //     // Vector3 p1 = { +size, 0, -size };
    //     // Vector3 p2 = { -size, 0, -size };
    //     // Vector3 start = p;
    //     // Vector3 end = lightPosition;
    //     // Vector3 dirNorm;
    //     // dirNorm = Vector3Sub(end, start);
    //     // dirNorm = Vector3Normalize(dirNorm);
    //     // auto isHit = RaycastTriangleV3(p0, p1, p2, p, dirNorm);

    //     auto isHit = RaycastTriangleAll(p, lightPosition, triangles.data(), triangles.size());

    //     BitmapDrawLineWire(bitmap, lightPosition, p, isHit ? COLOR_RED : COLOR_GREEN);
    // }
}

int main()
{
    auto size = 256;

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

        UpdateCameraRotation(&camera, 0.0230f, left, up, down, right);
        UpdateCameraPosition(&camera, 0.0020f, w, a, s, d, e, q);

        Draw(&bitmap, camera);

        SysWindow_SetPixels(window, bitmap.pixels, bitmap.width, bitmap.height);
        SysWindow_Update(window);

        FixedTimeEnd();
    }

    return 0;
}
