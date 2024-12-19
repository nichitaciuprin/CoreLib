#include "SysHelper.h"
#include "WindowDebug.h"

int main()
{
    Bitmap bitmap = BitmapCreate(512, 512);

    BitmapSetPerspective(&bitmap, 512, 512, 0.1f, 1000.0f);

    Camera camera;
    camera.position = (Vector3){ 0, 1.70f, -10 };
    camera.yaw = 0;
    camera.pitch = 0;

    while (true)
    {
        SysHelperFixedTimeStart();

        BitmapReset(&bitmap);
        BitmapSetView(&bitmap, &camera);

        Vector3 v0 = { +5, 0, +5 };
        Vector3 v1 = { +5, 0, -5 };
        Vector3 v2 = { -5, 0, -5 };
        Vector3 v3 = { -5, 0, +5 };
        BitmapDrawPoligon(&bitmap, v0, v1, v2, v3, COLOR_WHITE);

        Vector3 p0 = { 0, 0.5f, 0 };
        BitmapDrawCubeColored(&bitmap, p0, Vector3Zero(), Vector3One());

        float time = (float)SysHelperGetTime() / 1000;
        float x = MathSin(time) * 4;
        float z = MathCos(time) * 4;
        Vector3 lightPosition = { x, 5, z };
        BitmapApplyLightAndShadows(&bitmap, lightPosition);
        BitmapDrawCube(&bitmap, lightPosition, Vector3Zero(), Vector3One(), COLOR_WHITE);

        DebugWindowDisplay(&bitmap, &camera);
        if (DebugWindowClosed()) break;

        SysHelperFixedTimeEnd();
    }

    return 0;
}
