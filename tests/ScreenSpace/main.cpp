#include "BaseExt.h"
#include "HelperExt.h"
#include "BitmapClass.h"
#include "Window.h"
#include "Subgen1.h"
#include "Print.h"

Vector3 p0;
Vector3 p1;
Vector3 p2;

Subgen subgen = SubgenCreate(0);

void DrawLineScreenSpaceOld(Bitmap* bitmap, Vector3 v0, Vector3 v1, Color color)
{
    BitmapDrawLineScreenSpaceV1(bitmap, v0, v1, color);
}
void DrawLineScreenSpaceNew(Bitmap* bitmap, Vector3 v0, Vector3 v1, Color color)
{
    static long DrawLineScreenSpaceNew_timer = 0;
    static bool DrawLineScreenSpaceNew_trigger = false;

    if (DrawLineScreenSpaceNew_timer > 0)
        DrawLineScreenSpaceNew_timer--;

    if (DrawLineScreenSpaceNew_timer <= 0)
    {
        DrawLineScreenSpaceNew_timer = 1000;
        DrawLineScreenSpaceNew_trigger = !DrawLineScreenSpaceNew_trigger;
    }

    if (!DrawLineScreenSpaceNew_trigger) return;

    BitmapDrawLineScreenSpaceV3(bitmap, v0, v1, color);
}

void DrawTriangleWireframeScreenspaceOld(Bitmap* bitmap, Vector3 v0, Vector3 v1, Vector3 v2, Color color)
{
    BitmapDrawTriangleWireframeScreenspaceV1(bitmap, v0, v1, v2, color);
}
void DrawTriangleWireframeScreenspaceNew(Bitmap* bitmap, Vector3 v0, Vector3 v1, Vector3 v2, Color color)
{
    static long DrawTriangleScreenSpaceNew_timer = 0;
    static bool DrawTriangleScreenSpaceNew_draw = false;

    if (DrawTriangleScreenSpaceNew_timer > 0)
        DrawTriangleScreenSpaceNew_timer--;

    if (DrawTriangleScreenSpaceNew_timer <= 0)
    {
        DrawTriangleScreenSpaceNew_timer = 500;
        DrawTriangleScreenSpaceNew_draw = !DrawTriangleScreenSpaceNew_draw;
    }

    if (!DrawTriangleScreenSpaceNew_draw) return;

    BitmapDrawTriangleWireframeScreenspaceV2(bitmap, v0, v1, v2, color);
}

void Randomise()
{
    static long Randomise_timer = 0;
    Randomise_timer--;
    if (Randomise_timer > 0) return;
    Randomise_timer = 2000;
    // Randomise_timer = 4000;

    auto width = 40;
    auto height = 40;

    auto maxx = width-1;
    auto maxy = height-1;

    float zFar = 0;
    float zClose = 0;

    static int callcount = 0;

    callcount++;

    p0 = { SubgenRange(&subgen, 0, maxx), SubgenRange(&subgen, 0, maxy), zFar   };
    p1 = { SubgenRange(&subgen, 0, maxx), SubgenRange(&subgen, 0, maxy), zClose };
    p2 = { SubgenRange(&subgen, 0, maxx), SubgenRange(&subgen, 0, maxy), zClose };

    // PrintVector3(p0); cout << endl;
    // PrintVector3(p1); cout << endl;
    // PrintVector3(p2); cout << endl;
}

int main()
{
    auto width = 40;
    auto height = 40;

    auto maxx = width-1;
    auto maxy = height-1;

    auto scale = 10;

    auto bitmap = BitmapCreate(width, height);
    auto window = make_unique<Window>(700, 100, width * scale, height * scale);

    Subgen subgen = SubgenCreate(0);

    float zFar = 0;
    float zClose = 0;

    while (window->Exists())
    {
        BitmapReset(&bitmap);

        {
            Randomise();
        }

        // common
        {
            // p0 = { 20, 15, zFar };
            // p1 = { 5, 20, zClose };
            // p2 = { 35,  20, zClose };

            // p0 = { 20, 15, zFar };
            // p1 = { 5, 20, zClose };
            // p2 = { 35, 35, zClose };

            // p0 = { 20,  5, zFar };
            // p1 = { 35, 20, zClose };
            // p2 = {  5, 35, zClose };

            // p0 = { 25, 36, 0 };
            // p1 = { 38, 1,  0 };
            // p2 = { 5, 10, 0 };

            // p0 = { 20, 10, zFar };
            // p1 = { 35, 35, zClose };
            // p2 = { 5,  20, zClose };

            // p0 = { 20, 10, zFar };
            // p1 = { 5, 35, zClose };
            // p2 = { 35,  20, zClose };

            // p0 = { 20, 15, zFar };
            // p1 = { 38, 20, zClose };
            // p2 = { 1,  35, zClose };
        }

        // squared
        // {
        //     p0 = { 20,  2, zFar };
        //     p1 = { 20, 20, zClose };
        //     p2 = { 35, 2, zClose };

        //     p0 = { 20,  5, zFar };
        //     p1 = { 35, 20, zClose };
        //     p2 = { 20, 35, zClose };
        // }

        // p0 = { 29, 6, zFar };
        // p1 = { 6, 2, zClose };
        // p2 = { 4, 19, zClose };

        // Vector3 p0 = { 2, 5, zFar };
        // Vector3 p1 = { 35, 15, zClose };
        // Vector3 p2 = { 5, 20, zClose };

        // Vector3 p0 = { 20, 5, zFar };
        // Vector3 p1 = { 35, 15, zClose };
        // Vector3 p2 = { 5, 20, zClose };

        {
            DrawTriangleWireframeScreenspaceOld(&bitmap, p0, p1, p2, COLOR_GREEN);
            DrawTriangleWireframeScreenspaceNew(&bitmap, p0, p1, p2, COLOR_RED);
        }

        {
            // DrawLineScreenSpaceOld(&bitmap, p0, p2, COLOR_GREEN);
            // DrawLineScreenSpaceOld(&bitmap, p0, p1, COLOR_GREEN);
            // DrawLineScreenSpaceOld(&bitmap, p1, p2, COLOR_GREEN);

            // DrawLineScreenSpaceNew(&bitmap, p0, p2, COLOR_RED);
            // DrawLineScreenSpaceNew(&bitmap, p0, p1, COLOR_RED);
            // DrawLineScreenSpaceNew(&bitmap, p1, p2, COLOR_RED);
        }

        // BitmapDrawLineScreenSpaceV2(bitmap, v0, v1, COLOR_WHITE);

        // DrawPixelSignal(*bitmap, p0);
        // DrawPixelSignal(*bitmap, p1);
        // DrawPixelSignal(*bitmap, p2);

        window->SetPixelsScaled(bitmap.pixels, bitmap.width, bitmap.height, scale);

        window->Update();
    }
}
