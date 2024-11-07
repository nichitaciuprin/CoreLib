#include "BaseExt.h"
#include "SysHelper.h"
#include "Helper.h"
#include "Bitmap.h"
#include "Window.h"

int main()
{
    auto width = 400;
    auto height = 400;

    auto bitmap = make_unique<Bitmap>(width, height);
    auto window = make_unique<Window>(700, 100, width, height);

    while (window->Exists())
    {
        bitmap->Fill(COLOR_BLACK);

        Camera camera = { 0, 0, 0 };
        auto view = MatrixView3(&camera);

        {
            auto time = (float)clock() / 400;
            Vector3 position = { 0, 0, 2 };
            Vector3 rotation = { 0, time, 0 };
            Vector3 scale = { 1, 1, 1 };
            auto world = MatrixWorld2(position, rotation, scale);
            bitmap->DrawCubeColored(world * view);
        }
        {
            Vector3 position = { 0.5f, 0.5f, 2 };
            Vector3 rotation = { 0, 0, 0 };
            Vector3 scale = { 1, 1, 1 };
            auto world = MatrixWorld2(position, rotation, scale);
            bitmap->DrawCubeColored(world * view);
        }

        bitmap->DrawBorder(COLOR_GREEN);
        window->SetPixels(bitmap->pixels.data(), bitmap->Width(), bitmap->Height());
        window->Update();
    }

    return 0;
}
