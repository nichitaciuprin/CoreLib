#include "SysHelper.h"
#include "BaseExt.h"
#include "HelperExt.h"
#include "BitmapClass.h"
#include "Window.h"

void DrawCube(Bitmap* bitmap, Matrix view, Vector3 position, float time)
{
    Vector3 rotation = { 0, time, 0 };
    Vector3 scale = { 1, 1, 1 };

    auto world = MatrixWorld2(position, rotation, scale);
    auto mvp = world * view;

    BitmapDrawCubeColored(bitmap, mvp);
}
void DrawPlane(Bitmap* bitmap, Matrix view, Vector3 position)
{
    float size = 5;

    Vector3 p0 = { +size, 0, +size }; p0 += position; p0 *= view;
    Vector3 p1 = { +size, 0, -size }; p1 += position; p1 *= view;
    Vector3 p2 = { -size, 0, -size }; p2 += position; p2 *= view;
    Vector3 p3 = { -size, 0, +size }; p3 += position; p3 *= view;

    BitmapDrawPoligon(bitmap, p0, p1, p2, p3, COLOR_WHITE);
}
void Draw(Bitmap* bitmap, Camera camera)
{
    float time = GetTime();

    BitmapReset(bitmap);

    auto view = MatrixView3(&camera);

    DrawPlane(bitmap, view, { 0, 0, 0 });
    DrawPlane(bitmap, view, { 0, 0, 100 });
    DrawCube(bitmap, view, { 0, 0.5f, 0 }, (float)time / 3000);
    DrawCube(bitmap, view, { 0, 0.5f, 100 }, (float)time / 600);
    DrawCube(bitmap, view, { 0, 1.5f, 100 }, (float)time / 300);

    // bridge
    {
        Vector3 p0 = { -1, 0,  2 }; p0 *= view;
        Vector3 p1 = { -1, 0, 95 }; p1 *= view;
        Vector3 p2 = {  1, 0, 95 }; p2 *= view;
        Vector3 p3 = {  1, 0,  2 }; p3 *= view;
        BitmapDrawPoligon(bitmap, p0, p1, p2, p3, COLOR_WHITE);
    }

    // TODO fix this
    // bitmap->ApplyBlackWhiteColorDepth();
}

int main()
{
    auto size = 512;

    Bitmap bitmap = BitmapCreate(size, size);
    auto window = make_unique<Window>(700, 100, size, size);

    Camera camera = { 0, 1.70f, -10 };

    while (window->Exists())
    {
        FixedTimeStart();

        auto left = window->KeyDown_LEFT();
        auto up = window->KeyDown_UP();
        auto down = window->KeyDown_DOWN();
        auto right = window->KeyDown_RIGHT();

        auto w = window->KeyDown_W();
        auto a = window->KeyDown_A();
        auto s = window->KeyDown_S();
        auto d = window->KeyDown_D();
        auto e = window->KeyDown_E();
        auto q = window->KeyDown_Q();

        UpdateCameraRotation(&camera, 0.0230f, left, up, down, right);
        UpdateCameraPosition(&camera, 0.0080f, w, a, s, d, e, q);

        Draw(&bitmap, camera);

        window->SetPixels(bitmap.pixels, bitmap.width, bitmap.height);
        window->Update();

        FixedTimeEnd();
    }

    return 0;
}
