#include "BaseLang.hpp"
#include "SysHelper.h"
#include "BaseMath.h"
#include "Bitmap.hpp"
#include "Window.h"

int main()
{
    auto width = 400;
    auto height = 400;

    auto bitmap = make_unique<BitmapClass>(width, height);
    auto window = make_unique<Window>(700, 100, width, height);

    while (window->Exists())
    {
        bitmap->Reset();

        Vector3 p0;
        Vector3 p1;
        Vector3 p2;
        Vector3 p3;

        // MAIN
        {
            p0 = { 250,  50 };
            p1 = { 200, 100 };
            p2 = { 300, 150 };
            bitmap->DrawTriangleScreenspace(p0, p1, p2, COLOR_RED);

            p0 = { 150,  50 };
            p1 = { 200, 100 };
            p2 = { 100,  150 };
            bitmap->DrawTriangleScreenspace(p0, p1, p2, COLOR_GREEN);
        }

        // SQUARES
        {
            p0 = {  0,  0 };
            p1 = { 25,  0 };
            p2 = { 25, 25 };
            p3 = {  0, 25 };
            bitmap->DrawTriangleScreenspace(p2, p3, p0, COLOR_RED);
            bitmap->DrawTriangleScreenspace(p0, p1, p2, COLOR_GREEN);

            p0 = {  0 + 50,  0 };
            p1 = { 25 + 50,  0 };
            p2 = { 25 + 50, 25 };
            p3 = {  0 + 50, 25 };
            bitmap->DrawTriangleScreenspace(p0, p3, p2, COLOR_BLUE);
            bitmap->DrawTriangleScreenspace(p1, p0, p2, COLOR_YELLOW);
        }

        // MALTA CROSS
        {
            p0 = { 200, 250 };

            p1 = { 150, 250 };
            p2 = { 100, 200 }; bitmap->DrawTriangleScreenspace(p0, p1, p2, COLOR_RED);
            p2 = { 100, 300 }; bitmap->DrawTriangleScreenspace(p2, p0, p1, COLOR_RED);

            p1 = { 250, 250 };
            p2 = { 300, 300 }; bitmap->DrawTriangleScreenspace(p1, p0, p2, COLOR_GREEN);
            p2 = { 300, 200 }; bitmap->DrawTriangleScreenspace(p1, p2, p0, COLOR_GREEN);

            p1 = { 200, 300 };
            p2 = { 150, 350 }; bitmap->DrawTriangleScreenspace(p0, p1, p2, COLOR_BLUE);
            p2 = { 250, 350 }; bitmap->DrawTriangleScreenspace(p0, p2, p1, COLOR_BLUE);

            p1 = { 200, 200 };
            p2 = { 150, 150 }; bitmap->DrawTriangleScreenspace(p0, p1, p2, COLOR_MAGENTA);
            p2 = { 250, 150 }; bitmap->DrawTriangleScreenspace(p0, p1, p2, COLOR_MAGENTA);
        }

        // ROMB
        {
            p1 = { 100,  50 };
            p2 = {  25, 125 };
            p0 = {  50,  75 }; bitmap->DrawTriangleScreenspace(p0, p1, p2, COLOR_ORANGE);
            p0 = {  75, 100 }; bitmap->DrawTriangleScreenspace(p0, p1, p2, COLOR_ORANGE);
        }

        bitmap->FillBorder(COLOR_GREEN);
        window->SetPixels(bitmap->pixels, bitmap->Width(), bitmap->Height());
        window->Update();
    }

    return 0;
}
