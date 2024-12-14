#include "SysHelper.h"
#include "BaseExt.h"
#include "BaseMath.hpp"
#include "Bitmap.hpp"
#include "Window.h"

float scale = 10;
float t;
float near = 1;
float far = 5;
Matrix view = MatrixView(Vector3Up(), 0, MathToRadians(-90));
Matrix proj = MatrixPerspectiveCube(1, 1, near, far);

Vector4 ToNdcTest(Vector4 v)
{
    v = v * proj;

    if (v.w != 0)
    {
        v.x /= v.w;
        v.y /= v.w;
        v.z /= v.w;
    }

    return v;
}

void BitmapDrawPointNdcScaled(Bitmap* instance, Vector4 p, Color color)
{
    p /= scale;

    Vector3 _v0 = { p.x, p.y, p.z };

    BitmapToScreenSpace(instance, &_v0);

    int minX = _v0.x - 2;
    int maxX = _v0.x + 2;
    int minY = _v0.y - 2;
    int maxY = _v0.y + 2;

    for (int x = minX; x <= maxX; x++)
    for (int y = minY; y <= maxY; y++)
        BitmapSetPixel(instance, x, y, color);
}
void BitmapDrawLineNdcScaled(Bitmap* instance, Vector4 v0, Vector4 v1, Color color)
{
    v0 /= scale;
    v1 /= scale;

    // // REMOVE
    // if (ClipLineLeft   (&v0, &v1)) return;
    // if (ClipLineRight  (&v0, &v1)) return;
    // if (ClipLineDown   (&v0, &v1)) return;
    // if (ClipLineUp     (&v0, &v1)) return;

    Vector3 _v0 = { v0.x, v0.y, v0.z };
    Vector3 _v1 = { v1.x, v1.y, v1.z };

    // if (_v.w != 0)
    // {
    //     _v.x /= _v.w;
    //     _v.y /= _v.w;
    //     _v.z /= _v.w;
    // }

    BitmapToScreenSpace(instance, &_v0);
    BitmapToScreenSpace(instance, &_v1);
    BitmapDrawLineScreenSpace(instance, _v0, _v1, color);
}

void DrawFrustum(Bitmap* bitmap)
{
    {
        Vector4 f0 = { -near, 0, near, 1 };
        Vector4 f1 = { -far,  0, far , 1 };
        Vector4 f2 = { +far,  0, far , 1 };
        Vector4 f3 = { +near, 0, near, 1 };

        Vector4 _f0 = ToNdcTest(f0);
        Vector4 _f1 = ToNdcTest(f1);
        Vector4 _f2 = ToNdcTest(f2);
        Vector4 _f3 = ToNdcTest(f3);

        Vector4 __f0 = Vector4Lerp(f0, _f0, t);
        Vector4 __f1 = Vector4Lerp(f1, _f1, t);
        Vector4 __f2 = Vector4Lerp(f2, _f2, t);
        Vector4 __f3 = Vector4Lerp(f3, _f3, t);

        __f0 *= view;
        __f1 *= view;
        __f2 *= view;
        __f3 *= view;

        BitmapDrawLineNdcScaled(bitmap, __f0, __f1, COLOR_GREEN);
        BitmapDrawLineNdcScaled(bitmap, __f1, __f2, COLOR_GREEN);
        BitmapDrawLineNdcScaled(bitmap, __f2, __f3, COLOR_GREEN);
        BitmapDrawLineNdcScaled(bitmap, __f3, __f0, COLOR_GREEN);
    }
}
void DrawLine(Bitmap* bitmap, Vector3 p0, Vector3 p1)
{
    Vector4 f0 = { p0.x, p0.y, p0.z, 1 };
    Vector4 f1 = { p1.x, p1.y, p1.z, 1 };

    Vector4 _f0 = f0 * proj;
    Vector4 _f1 = f1 * proj;

    _f0 /= _f0.w;
    _f1 /= _f1.w;

    Vector4 __f0 = Vector4Lerp(f0, _f0, t);
    Vector4 __f1 = Vector4Lerp(f1, _f1, t);
    // Vector4 __f0 = f0;
    // Vector4 __f1 = f1;

    __f0 *= view;
    __f1 *= view;

    BitmapDrawLineNdcScaled(bitmap, __f0, __f1, COLOR_RED);
    BitmapDrawPointNdcScaled(bitmap, __f0, COLOR_RED);
    BitmapDrawPointNdcScaled(bitmap, __f1, COLOR_RED);
}
void DrawLineClipped(Bitmap* bitmap, Vector3 p0, Vector3 p1)
{
    Vector4 f0 = { p0.x, p0.y, p0.z, 1 };
    Vector4 f1 = { p1.x, p1.y, p1.z, 1 };

    Vector4 _f0 = f0 * proj;
    Vector4 _f1 = f1 * proj;

    if (ClipLineWClipSpace      (&_f0, &_f1)) return;
    if (ClipLineBackClipSpace   (&_f0, &_f1)) return;
    if (ClipLineFrontClipSpace  (&_f0, &_f1)) return;
    if (ClipLineLeftClipSpace   (&_f0, &_f1)) return;
    if (ClipLineRightClipSpace  (&_f0, &_f1)) return;
    if (ClipLineDownClipSpace   (&_f0, &_f1)) return;
    if (ClipLineUpClipSpace     (&_f0, &_f1)) return;

    _f0 /= _f0.w;
    _f1 /= _f1.w;

    Vector4 __f0 = Vector4Lerp(f0, _f0, t);
    Vector4 __f1 = Vector4Lerp(f1, _f1, t);

    __f0 *= view;
    __f1 *= view;

    BitmapDrawLineNdcScaled(bitmap, __f0, __f1, COLOR_GREEN);
    BitmapDrawPointNdcScaled(bitmap, __f0, COLOR_GREEN);
    BitmapDrawPointNdcScaled(bitmap, __f1, COLOR_GREEN);
}
void Draw(Bitmap* bitmap, long time)
{
    BitmapReset(bitmap);
    BitmapFillCross(bitmap, COLOR_WHITE);
    DrawFrustum(bitmap);

    {
        // Vector3 p0 = {  8,  0,  4 };
        // Vector3 p1 = {  8,  0,  2 };
        // Vector3 p2 = { -6,  0,  2 };
        // Vector3 p3 = { -6,  0,  4 };

        Vector3 p0 = {  1,  0,  8 };
        Vector3 p1 = {  1,  0, -2 };
        Vector3 p2 = { -1,  0, -4 };
        Vector3 p3 = { -1,  0,  8 };

        // Vector3 p0 = {  6,  0,  4 };
        // Vector3 p1 = {  1,  0, -2 };
        // Vector3 p2 = { -1,  0, -2 };
        // Vector3 p3 = { -6,  0,  4 };

        DrawLine(bitmap, p0, p1);
        DrawLine(bitmap, p1, p2);
        DrawLine(bitmap, p2, p3);
        DrawLine(bitmap, p3, p0);

        DrawLineClipped(bitmap, p0, p1);
        DrawLineClipped(bitmap, p1, p2);
        DrawLineClipped(bitmap, p2, p3);
        DrawLineClipped(bitmap, p3, p0);
    }
}

int main()
{
    auto size = 511;

    Bitmap bitmap = BitmapCreate(size, size);
    auto window = make_unique<Window>(700, 100, size, size);

    while (window->Exists())
    {
        FixedTimeStart();

        t = MathPingPong((float)clock() / 1000, 3) - 1; t = MathClampFloat(t, 0, 1);
        Draw(&bitmap, GetTime());
        window->SetPixels(bitmap.pixels, bitmap.width, bitmap.height);
        window->Update();

        FixedTimeEnd();
    }

    return 0;
}
