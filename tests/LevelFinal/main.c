#include "SysHelper.h"
#include "Window3D.h"

int main()
{
    Window3DInit(700, 100, 512, 512);

    Camera camera;
    camera.position = (Vector3){ 0, 1.70f, -10 };
    camera.yaw = 0;
    camera.pitch = 0;

    Window3DSetCamera(camera);

    while (Window3DExists())
    {
        FixedTimeStart();
        Window3DDrawStart();

        Vector3 v0 = { +5, 0, +5 };
        Vector3 v1 = { +5, 0, -5 };
        Vector3 v2 = { -5, 0, -5 };
        Vector3 v3 = { -5, 0, +5 };
        Window3DDrawPoligon(v0, v1, v2, v3, COLOR_WHITE);

        Vector3 p0 = { 0, 0.5f, 0 };
        Window3DDrawCubeColored(p0, Vector3Zero(), Vector3One());

        float time = (float)GetTime() / 1000;
        float x = MathSin(time) * 4;
        float z = MathCos(time) * 4;
        Vector3 lightPosition = { x, 5, z };
        Window3DApplyLightAndShadows(lightPosition);
        Window3DDrawCube(lightPosition, Vector3Zero(), Vector3One(), COLOR_WHITE);

        Window3DDrawEnd();
        FixedTimeEnd();
    }

    return 0;
}
