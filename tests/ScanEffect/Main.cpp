#include "BaseExt.h"
#include "SysHelper.h"
#include "Subgen.h"
#include "BitmapClass.h"
#include "Window.h"

int main()
{
    auto width = 200;
    auto height = 200;

    auto bitmap = make_unique<BitmapClass>(width, height);
    auto window = make_unique<Window>(700, 100, width, height);

    int iteration = 0;

    Subgen subgen = SubgenCreate(0);

    while (window->Exists())
    {
        int i1 = iteration;
        int i2 = SubgenNext(&subgen);
        int pixelCount = width * height;
        i1 %= pixelCount;
        i2 %= pixelCount;
        bitmap->pixels[i1] = SubgenNext(&subgen);
        bitmap->pixels[i2] = 0;
        iteration++;

        bitmap->FillBorder(COLOR_GREEN);
        window->SetPixels(bitmap->pixels.data(), bitmap->Width(), bitmap->Height());
        window->Update();
    }

    return 0;
}
