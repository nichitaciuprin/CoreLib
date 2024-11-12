#include "BaseExt.h"
#include "SysHelper.h"
#include "Helper.h"
#include "BitmapClass.h"
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

        auto time = (float)clock() / 400;
        Camera camera = { 0, 0, 0 };
        auto view = MatrixView3(&camera);
        Vector3 position = { 0, 0, 2 };
        Vector3 rotation = { 0, time, 0 };
        Vector3 scale = { 1, 1, 1 };
        auto world = MatrixWorld2(position, rotation, scale);
        bitmap->DrawCubeWireframe(world * view, COLOR_RED);

        bitmap->FillBorder(COLOR_GREEN);
        window->SetPixels(bitmap->pixels, bitmap->Width(), bitmap->Height());
        window->Update();
    }

    return 0;
}
