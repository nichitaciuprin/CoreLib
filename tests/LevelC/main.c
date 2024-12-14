#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <memory.h>
#include <time.h>
#include <math.h>

#include "SysHelper.h"
#include "SysWindow.h"
#include "BaseMath.h"
#include "Bitmap.h"
#include "BitmapResize.h"

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

    Vector3 p0 = { +size, 0, +size }; p0 = Vector3Add(p0, position);
    Vector3 p1 = { +size, 0, -size }; p1 = Vector3Add(p1, position);
    Vector3 p2 = { -size, 0, -size }; p2 = Vector3Add(p2, position);
    Vector3 p3 = { -size, 0, +size }; p3 = Vector3Add(p3, position);

    BitmapDrawPoligon(bitmap, p0, p1, p2, p3, COLOR_WHITE);
}
void Draw(Bitmap* bitmap, Camera camera)
{
    float time = GetTime();

    BitmapReset(bitmap);
    BitmapSetView(bitmap, &camera);

    // Vector3 lightPosition = { 0, 10, 0 };
    // Vector3 lightPosition = { 0, 10, MathPingPong(GetTime()/50, 120) - 10 };
    Vector3 lightPosition = camera.position;

    DrawPlane(bitmap, (Vector3){ 0, 0, 0 });
    DrawCube(bitmap, (Vector3){ 0, 0.5f, 0 }, (float)time / 3000);

    DrawPlane(bitmap, (Vector3){ 0, 0, 100 });
    DrawCube(bitmap, (Vector3){ 0, 0.5f, 100 }, (float)time / 600);
    DrawCube(bitmap, (Vector3){ 0, 1.5f, 100 }, (float)time / 300);

    // bridge
    {
        Vector3 p0 = (Vector3){ -1, 0,  2 };
        Vector3 p1 = (Vector3){ -1, 0, 95 };
        Vector3 p2 = (Vector3){  1, 0, 95 };
        Vector3 p3 = (Vector3){  1, 0,  2 };
        BitmapDrawPoligon(bitmap, p0, p1, p2, p3, COLOR_WHITE);
    }

    BitmapApplyLight(bitmap, lightPosition);
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

        UpdateCameraRotation(&camera, 0.0230f, left, up, down, right);
        UpdateCameraPosition(&camera, 0.0020f, w, a, s, d, e, q);

        Draw(&bitmap, camera);

        SysWindowSetPixels(window, bitmap.pixels, bitmap.width, bitmap.height);
        SysWindowUpdate(window);

        FixedTimeEnd();
    }

    return 0;
}
