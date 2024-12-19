#include "SysWindow.h"
#include "BaseMath.h"
#include "Bitmap.h"
#include "stdio.h"

SysWindow* _DebugWindow = NULL;

bool DebugWindowClosed()
{
    if (_DebugWindow == NULL) return true;
    return !SysWindowExists(_DebugWindow);
}
void DebugWindowDisplay(Bitmap* bitmap, Camera* camera)
{
    if (_DebugWindow == NULL)
        _DebugWindow = SysWindowCreate(700, 100, bitmap->width, bitmap->height);

    SysWindowSetPixels(_DebugWindow, bitmap->pixels, bitmap->width, bitmap->height);

    bool left = SysWindowKeyDownLEFT(_DebugWindow);
    bool up = SysWindowKeyDownUP(_DebugWindow);
    bool down = SysWindowKeyDownDOWN(_DebugWindow);
    bool right = SysWindowKeyDownRIGHT(_DebugWindow);

    bool w = SysWindowKeyDownW(_DebugWindow);
    bool a = SysWindowKeyDownA(_DebugWindow);
    bool s = SysWindowKeyDownS(_DebugWindow);
    bool d = SysWindowKeyDownD(_DebugWindow);
    bool e = SysWindowKeyDownE(_DebugWindow);
    bool q = SysWindowKeyDownQ(_DebugWindow);

    CameraUpdateRotation(camera, 0.0230f, left, up, down, right);
    CameraUpdatePosition(camera, 0.0020f, w, a, s, d, e, q);

    SysWindowUpdate(_DebugWindow);
}
