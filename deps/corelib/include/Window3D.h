#include "SysWindow.h"
#include "BaseMath.h"
#include "Bitmap.h"
#include "BitmapResize.h"

Bitmap _Window3DBitmap;
SysWindow* _Window3DWindow;
Camera _Window3DCamera;

void Window3DInit(int x, int y, int clientWidth, int clientHeight)
{
    _Window3DBitmap = BitmapCreate(clientWidth, clientHeight);
    _Window3DWindow = SysWindowCreate(700, 100, clientWidth, clientHeight);
    _Window3DCamera = (Camera){};
    BitmapSetPerspective(&_Window3DBitmap, clientWidth, clientHeight, 0.1f, 1000.0f);
}
void Window3DSetCamera(Camera camera)
{
    _Window3DCamera = camera;
}
bool Window3DExists()
{
    return SysWindowExists(_Window3DWindow);
}
void Window3DDrawStart()
{
    AdaptBitmapToWindow(&_Window3DBitmap, _Window3DWindow);

    bool left = SysWindowKeyDownLEFT(_Window3DWindow);
    bool up = SysWindowKeyDownUP(_Window3DWindow);
    bool down = SysWindowKeyDownDOWN(_Window3DWindow);
    bool right = SysWindowKeyDownRIGHT(_Window3DWindow);

    bool w = SysWindowKeyDownW(_Window3DWindow);
    bool a = SysWindowKeyDownA(_Window3DWindow);
    bool s = SysWindowKeyDownS(_Window3DWindow);
    bool d = SysWindowKeyDownD(_Window3DWindow);
    bool e = SysWindowKeyDownE(_Window3DWindow);
    bool q = SysWindowKeyDownQ(_Window3DWindow);

    CameraUpdateRotation(&_Window3DCamera, 0.0230f, left, up, down, right);
    CameraUpdatePosition(&_Window3DCamera, 0.0020f, w, a, s, d, e, q);

    BitmapReset(&_Window3DBitmap);
    BitmapSetView(&_Window3DBitmap, &_Window3DCamera);
}
void Window3DDrawEnd()
{
    SysWindowSetPixels(_Window3DWindow, _Window3DBitmap.pixels, _Window3DBitmap.width, _Window3DBitmap.height);
    SysWindowUpdate(_Window3DWindow);
}
void Window3DDrawPoligon(Vector3 v0, Vector3 v1, Vector3 v2, Vector3 v3, Color color)
{
    BitmapDrawPoligon(&_Window3DBitmap, v0, v1, v2, v3, color);
}
void Window3DDrawCube(Vector3 position, Vector3 rotation, Vector3 scale, Color color)
{
    BitmapDrawCube(&_Window3DBitmap, position, rotation, scale, color);
}
void Window3DDrawCubeColored(Vector3 position, Vector3 rotation, Vector3 scale)
{
    BitmapDrawCubeColored(&_Window3DBitmap, position, rotation, scale);
}
void Window3DApplyLightAndShadows(Vector3 lightPosition)
{
    BitmapApplyLightAndShadows(&_Window3DBitmap, lightPosition);
}
