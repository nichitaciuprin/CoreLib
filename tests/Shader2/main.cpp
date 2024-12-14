#include "SysHelper.h"
#include "SysWindow.h"
#include "HelperExt.h"
#include "Bitmap.h"
#include "BitmapResize.h"
#include "BaseExt.h"

#define MAX_STEPS 100
#define MAX_DIST 100.0
#define SURF_DIST 0.01

Camera camera = { 0, 1.70f, -10 };
float iTime = 0;

float GetDist(Vector3 p)
{
	Vector3 sphere1 = { 0, 1, 6 }; float radius1 = 1.0;
    Vector3 sphere2 = { 3, 2, 6 }; float radius2 = 1.0;
    float sphereDist1 = Vector3Length(p - sphere1) - radius1;
    float sphereDist2 = Vector3Length(p - sphere2) - radius2;
    float planeDist = p.y;
    float d;
    d = planeDist;
    d = MathMinFloat(d, sphereDist1);
    d = MathMinFloat(d, sphereDist2);
    return d;
}
float RayMarch(Vector3 ro, Vector3 rd)
{
	float dO = 0.0;

    for (int i = 0; i < MAX_STEPS; i++)
    {
    	Vector3 p = ro + rd * dO;
        float dS = GetDist(p);
        dO += dS;
        if(dO > MAX_DIST) break;
        if(dS < SURF_DIST) break;
    }

    return dO;
}
Vector3 GetNormal(Vector3 p)
{
    float offset = 0.01f;

    Vector3 p0 = p;
    Vector3 p1 = p; p1.x -= offset;
    Vector3 p2 = p; p2.y -= offset;
    Vector3 p3 = p; p3.z -= offset;

	float d0 = GetDist(p0);
    float d1 = GetDist(p1);
    float d2 = GetDist(p2);
    float d3 = GetDist(p3);

    float x = d0 - d1;
    float y = d0 - d2;
    float z = d0 - d3;

    Vector3 result = { x, y, z };

    result = Vector3Normalize(result);

    return result;
}
float GetLight(Vector3 p)
{
    Vector3 lightPos = { 0, 5, 6 };

    Vector3 offset = { MathSin(iTime), 0, MathCos(iTime) };
    offset *= 2;

    lightPos += offset;

    // lightPos.xz += vec2(sin(iTime), cos(iTime)) * 2.0;

    Vector3 dirToLight = Vector3Normalize(lightPos - p);
    Vector3 surfaceNomal = GetNormal(p);
    float lightFraction = MathClampFloat(Vector3Dot(surfaceNomal, dirToLight), 0.0, 1.0);

    // adds shadows
    float d = RayMarch(p + surfaceNomal * SURF_DIST * 2.0, dirToLight);
    bool rayhit = d < Vector3Length(lightPos - p);
    if (rayhit)
        lightFraction *= 0.1;
        // lightFraction = 0.0;

    return lightFraction;
}

void DrawPixel(Bitmap* bitmap, int x, int y)
{
    float width = bitmap->width;
    float height = bitmap->height;

    float xf = ((float)x - width / 2) / height;
    float yf = ((float)y - height / 2) / height;

    yf = -yf;

    // Vector3 ro = { 0, 1, 0 };
    Vector3 ro = camera.position;

    Vector3 rd = Vector3Normalize({ xf, yf, 1 });

    float d = RayMarch(ro, rd);
    Vector3 p = ro + rd * d;
    float diff = GetLight(p);

    Color color = ColorCreateBwFloat(diff);

    BitmapSetPixel(bitmap, x, y, color);
}
void Draw(Bitmap* bitmap, Camera camera)
{
    for (int y = 0; y < bitmap->height; y++)
    for (int x = 0; x < bitmap->width;  x++)
        DrawPixel(bitmap, x, y);

    // cout << "DONE" << endl;
}

int main()
{
    auto size = 100;
    auto scale = 2;

    Bitmap bitmap = BitmapCreate(size, size);
    auto window = SysWindow_Create(700, 100, size*scale, size*scale);

    // Camera camera = { 0, 1.70f, -10 };

    while (SysWindow_Exists(window))
    {
        FixedTimeStart();

        iTime = ((float)GetTime() / 1000);

        auto left = SysWindow_KeyDown_LEFT(window);
        auto up = SysWindow_KeyDown_UP(window);
        auto down = SysWindow_KeyDown_DOWN(window);
        auto right = SysWindow_KeyDown_RIGHT(window);

        auto w = SysWindow_KeyDown_W(window);
        auto a = SysWindow_KeyDown_A(window);
        auto s = SysWindow_KeyDown_S(window);
        auto d = SysWindow_KeyDown_D(window);
        auto e = SysWindow_KeyDown_E(window);
        auto q = SysWindow_KeyDown_Q(window);

        CameraUpdateRotation(&camera, 0.0230f, left, up, down, right);
        CameraUpdatePosition(&camera, 0.0080f, w, a, s, d, e, q);

        Draw(&bitmap, camera);

        SysWindow_SetPixelsScaled(window, bitmap.pixels, bitmap.width, bitmap.height, scale);
        SysWindow_Update(window);

        FixedTimeEnd();
    }

    return 0;
}
