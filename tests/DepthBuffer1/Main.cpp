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

        {
            float zFar = 10;
            float zClose = 9;
            {
                Vector3 p0 = { -0.2f,  0.6f,  zFar };
                Vector3 p1 = {  0.0f,  0.6f,  zFar };
                Vector3 p2 = {  0.4f, -0.6f,  zClose };
                bitmap->DrawTriangleNdc(p0, p1, p2, COLOR_RED);
            }
            {
                Vector3 p0 = {  0.6f, -0.2f,  zFar };
                Vector3 p1 = {  0.6f, -0.4f,  zFar };
                Vector3 p2 = { -0.8f, -0.2f,  zClose };
                bitmap->DrawTriangleNdc(p0, p1, p2, COLOR_GREEN);
            }
            {
                Vector3 p0 = { -0.4f, -0.4f,  zFar };
                Vector3 p1 = { -0.6f, -0.4f,  zFar };
                Vector3 p2 = {  0.2f,  0.6f,  zClose };
                bitmap->DrawTriangleNdc(p0, p1, p2, COLOR_BLUE);
            }
        }

        bitmap->FillBorder(COLOR_GREEN);
        window->SetPixels(bitmap->pixels, bitmap->Width(), bitmap->Height());
        window->Update();
    }

    return 0;
}
