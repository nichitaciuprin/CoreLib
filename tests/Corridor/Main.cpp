#include "BaseExt.h"
#include "SysHelper.h"
#include "HelperExt.h"
#include "Bitmap.h"
#include "Window.h"

void main2()
{
    auto width = 400;
    auto height = 400;

    auto bitmap = make_unique<Bitmap>(width, height);
    auto window = make_unique<Window>(700, 100, width, height);

    while (window->Exists())
    {
        bitmap->Reset();

        auto time = (float)clock() / 1000;
        Camera camera = { Vector3Zero(), time, 0 };
        auto view = MatrixView3(&camera);
        {
            Vector3 position = { 0, 0, 0 };
            Vector3 rotation = { 0, 0, 0 };
            Vector3 scale = { 1, 1, 4 };
            auto world = MatrixWorld2(position, rotation, scale);
            bitmap->DrawCubeWireframe(world * view, COLOR_RED);
        }

        bitmap->FillBorder(COLOR_GREEN);
        window->SetPixels(bitmap->pixels, bitmap->Width(), bitmap->Height());
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