#include "SysHelper.h"
#include "BaseExt.h"
#include "HelperExt.h"
#include "Bitmap.h"
#include "Window.h"

void Draw(Bitmap& bitmap, Camera camera, long time)
{
    bitmap.Reset();

    auto view = MatrixView3(&camera);

    {
        Vector3 p0 = { -1, 0,  2 }; p0 *= view;
        Vector3 p1 = { -1, 0, 95 }; p1 *= view;
        Vector3 p2 = {  1, 0, 95 }; p2 *= view;
        Vector3 p3 = {  1, 0,  2 }; p3 *= view;
        bitmap.DrawPoligon1(p0, p1, p2, p3, COLOR_WHITE);
    }
    {
        float size = 5;
        Vector3 p0 = { -size, 0, -size + 100 }; p0 *= view;
        Vector3 p1 = { -size, 0,  size + 100 }; p1 *= view;
        Vector3 p2 = {  size, 0,  size + 100 }; p2 *= view;
        Vector3 p3 = {  size, 0, -size + 100 }; p3 *= view;
        bitmap.DrawPoligon1(p0, p1, p2, p3, COLOR_WHITE);
    }

    // TODO fix this
    // bitmap->ApplyBlackWhiteColorDepth();

    {
        auto time2 = (float)time / 600;
        Vector3 position = { 0, 0.5f, 100 };
        Vector3 rotation = { 0, time2, 0 };
        Vector3 scale = { 1, 1, 1 };
        auto world = MatrixWorld2(position, rotation, scale);
        bitmap.DrawCubeColored(world * view);
    }
    {
        auto time2 = (float)time / 300;
        Vector3 position = { 0, 1.5f, 100 };
        Vector3 rotation = { 0, time2, 0 };
        Vector3 scale = { 1, 1, 1 };
        auto world = MatrixWorld2(position, rotation, scale);
        bitmap.DrawCubeColored(world * view);
    }

    {
        float size = 5;
        Vector3 p0 = { -size, 0, -size }; p0 *= view;
        Vector3 p1 = { -size, 0,  size }; p1 *= view;
        Vector3 p2 = {  size, 0,  size }; p2 *= view;
        Vector3 p3 = {  size, 0, -size }; p3 *= view;
        bitmap.DrawPoligon1(p0, p1, p2, p3, COLOR_WHITE);
    }
    {
        auto time2 = (float)time / 300;
        Vector3 position = { 0, 1, 0 };
        Vector3 rotation = { 0, time2, 0 };
        Vector3 scale = { 1, 1, 1 };
        auto world = MatrixWorld2(position, rotation, scale);
        bitmap.DrawCubeColored(world * view);
    }
}

int main()
{
    auto size = 512;

    auto bitmap = make_unique<Bitmap>(size, size);
    auto window = make_unique<Window>(700, 100, size, size);

    Camera camera = { 0, 1.70f, -10 };

    while (window->Exists())
    {
        FixedTimeStart();

        UpdateCameraRotation(&camera, 0.0230f, window->KeyDown_LEFT(), window->KeyDown_UP(), window->KeyDown_DOWN(), window->KeyDown_RIGHT());
        UpdateCameraPosition(&camera, 0.0080f, window->KeyDown_W(), window->KeyDown_A(), window->KeyDown_S(), window->KeyDown_D(), window->KeyDown_E(), window->KeyDown_Q());

        Draw(*bitmap, camera, GetTime());

        window->SetPixels(bitmap->pixels, bitmap->Width(), bitmap->Height());

        window->Update();

        FixedTimeEnd();
    }

    return 0;
}
