#include "BaseExt.h"
#include "BaseMath.hpp"
#include "BitmapClass.h"
#include "Window.h"

void main2()
{
    auto width = 10;
    auto height = 10;

    auto scale = 40;

    auto bitmap = make_unique<BitmapClass>(width, height);
    auto window = make_unique<Window>(700, 100, width * scale, height * scale);

    while (window->Exists())
    {
        bitmap->Reset();

        float zFar = 0;
        float zClose = -10;

        {
            Vector3 p0 = { 1, 2, zFar };
            Vector3 p1 = { 8, 2, zClose };
            bitmap->DrawLineScreenSpace(p0, p1, COLOR_RED);
        }
        {
            Vector3 p0 = { 7, 1, zFar };
            Vector3 p1 = { 7, 8, zClose };
            bitmap->DrawLineScreenSpace(p0, p1, COLOR_GREEN);
        }
        {
            Vector3 p1 = { 8, 7, zFar };
            Vector3 p0 = { 1, 7, zClose };
            bitmap->DrawLineScreenSpace(p0, p1, COLOR_BLUE);
        }
        {
            Vector3 p1 = { 2, 8, zFar };
            Vector3 p0 = { 2, 1, zClose };
            bitmap->DrawLineScreenSpace(p0, p1, COLOR_YELLOW);
        }

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