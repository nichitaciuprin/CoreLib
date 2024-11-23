#include "BaseExt.h"
#include "HelperExt.h"
#include "BitmapClass.h"
#include "Window.h"
#include "Subgen1.h"

void DrawPixelSignal(BitmapClass& bitmap, Vector3 point)
{
    static long timer = 0;
    static bool draw = false;

    if (timer > 0)
        timer--;

    if (timer <= 0)
    {
        timer = 500;
        draw = !draw;
    }

    if (draw) bitmap.SetPixel(point.x, point.y, COLOR_GREEN);
}

void main2()
{
    auto width = 40;
    auto height = 40;

    auto scale = 10;

    auto bitmap = make_unique<BitmapClass>(width, height);
    auto window = make_unique<Window>(700, 100, width * scale, height * scale);

    while (window->Exists())
    {
        bitmap->Reset();

        float zFar = 0;
        float zClose = 0;

        // Vector3 p0 = { 20,  2, zFar };
        // Vector3 p1 = { 35, 20, zClose };
        // Vector3 p2 = {  5, 35, zClose };

        Vector3 p0 = { 20,  2, zFar };
        Vector3 p1 = {  5, 20, zClose };
        Vector3 p2 = { 35, 35, zClose };

        bitmap->DrawLineScreenSpace(p2, p0, COLOR_RED);
        bitmap->DrawLineScreenSpace(p1, p0, COLOR_RED);
        bitmap->DrawLineScreenSpace(p2, p1, COLOR_RED);

        bitmap->DrawLineScreenSpace(p0, p2, COLOR_BLUE);
        bitmap->DrawLineScreenSpace(p0, p1, COLOR_BLUE);
        bitmap->DrawLineScreenSpace(p1, p2, COLOR_BLUE);

        DrawPixelSignal(*bitmap, p0);
        DrawPixelSignal(*bitmap, p1);
        DrawPixelSignal(*bitmap, p2);

        window->SetPixelsScaled(bitmap->pixels, bitmap->Width(), bitmap->Height(), scale);

        window->Update();
    }
}

int main()
{
    try
    {
        main2();
    }
    catch (const exception& e)
    {
        cerr << e.what() << endl;
    }

    return 0;
}