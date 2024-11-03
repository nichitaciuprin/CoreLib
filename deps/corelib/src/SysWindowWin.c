#include "SysWindow.h"

#include <stdint.h>
#include <assert.h>

#define WIN32_LEAN_AND_MEAN
#ifndef NOMINMAX
#define NOMINMAX
#endif

#include <windef.h>
#include <winuser.h>
#include <wingdi.h>

typedef struct SysWindow
{
    bool keydown_W;
    bool keydown_A;
    bool keydown_S;
    bool keydown_D;
    bool keydown_UP;
    bool keydown_LEFT;
    bool keydown_DOWN;
    bool keydown_RIGHT;
    bool keydown_Q;
    bool keydown_E;

    HWND       _hwnd;
    HDC        _hdc;
    HBITMAP    _hbitmap;
    uint32_t*  _pixels;
    int        _width;
    int        _height;
}
SysWindow;

bool _SysWindow_Registered = 0;
void _SysWindow_InitBitmap(SysWindow* instance)
{
    instance->_hdc = CreateCompatibleDC(0);
}
void _SysWindow_ResetBitmap(SysWindow* instance, int clientWidth, int clientHeight)
{
    BITMAPINFO bitmapinfo = {};
    bitmapinfo.bmiHeader.biSize = sizeof(bitmapinfo.bmiHeader);
    bitmapinfo.bmiHeader.biPlanes = 1;
    bitmapinfo.bmiHeader.biBitCount = 32;
    bitmapinfo.bmiHeader.biCompression = BI_RGB;
    bitmapinfo.bmiHeader.biWidth  = clientWidth;
    bitmapinfo.bmiHeader.biHeight = clientHeight;

    if (instance->_hbitmap)
        DeleteObject(instance->_hbitmap);

    instance->_hbitmap = CreateDIBSection(NULL, &bitmapinfo, DIB_RGB_COLORS, (void**)&instance->_pixels, 0, 0);
    assert(instance->_hbitmap != 0);
    SelectObject(instance->_hdc, instance->_hbitmap);

    instance->_width  = clientWidth;
    instance->_height = clientHeight;
}
void _SysWindow_PaintBitmap(SysWindow* instance)
{
    PAINTSTRUCT paint;

    HDC device_context = BeginPaint(instance->_hwnd, &paint);

    BitBlt(device_context,
            paint.rcPaint.left, paint.rcPaint.top,
            paint.rcPaint.right - paint.rcPaint.left,
            paint.rcPaint.bottom - paint.rcPaint.top,
            instance->_hdc,
            paint.rcPaint.left, paint.rcPaint.top,
            SRCCOPY);

    EndPaint(instance->_hwnd, &paint);
}
LRESULT __stdcall _SysWindow_MessageHandler(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    SysWindow* instance = (SysWindow*)(GetWindowLongPtrA(hwnd, GWLP_USERDATA));

    if (instance == NULL)
        return DefWindowProcA(hwnd, message, wParam, lParam);

    switch(message)
    {
        case WM_QUIT:
        case WM_DESTROY:
        {
            instance->_hwnd = 0;
            break;
        }
        case WM_PAINT:
        {
            _SysWindow_PaintBitmap(instance);
            break;
        }
        case WM_SIZE:
        {
            int clientWidth = LOWORD(lParam);
            int clientHeight = HIWORD(lParam);

            bool sizeChanged =
                instance->_width != clientWidth ||
                instance->_height != clientHeight;

            if (sizeChanged)
                _SysWindow_ResetBitmap(instance, clientWidth, clientHeight);

            break;
        }
        case WM_KEYDOWN:
        case WM_KEYUP:
        {
            bool isDown = (message == WM_KEYDOWN);

            switch (wParam)
            {
                case VK_ESCAPE : { DestroyWindow(hwnd);              break; }
                case 'W'       : { instance->keydown_W     = isDown; break; }
                case 'A'       : { instance->keydown_A     = isDown; break; }
                case 'S'       : { instance->keydown_S     = isDown; break; }
                case 'D'       : { instance->keydown_D     = isDown; break; }
                case 'E'       : { instance->keydown_E     = isDown; break; }
                case 'Q'       : { instance->keydown_Q     = isDown; break; }
                case VK_UP     : { instance->keydown_UP    = isDown; break; }
                case VK_LEFT   : { instance->keydown_LEFT  = isDown; break; }
                case VK_DOWN   : { instance->keydown_DOWN  = isDown; break; }
                case VK_RIGHT  : { instance->keydown_RIGHT = isDown; break; }
                default        : {                                   break; }
            }
            break;
        }
        case WM_GETMINMAXINFO:
        {
            // Sets windows size defaults
            LPMINMAXINFO lpMMI = (LPMINMAXINFO)lParam;
            lpMMI->ptMinTrackSize.x = 10;
            lpMMI->ptMinTrackSize.y = 10;
            break;
        }
        default: return DefWindowProcA(hwnd, message, wParam, lParam);
    }

    return 0;
}
SysWindow* SysWindow_Create(int x, int y, int clientWidth, int clientHeight)
{
    SysWindow* instance = (SysWindow*)malloc(sizeof(SysWindow));

    instance->keydown_W = false;
    instance->keydown_A = false;
    instance->keydown_S = false;
    instance->keydown_D = false;
    instance->keydown_UP = false;
    instance->keydown_LEFT = false;
    instance->keydown_DOWN = false;
    instance->keydown_RIGHT = false;
    instance->keydown_Q = false;
    instance->keydown_E = false;

    instance->_hwnd = 0;

    instance->_hdc = 0;
    instance->_hbitmap = 0;
    instance->_pixels = 0;
    instance->_width = 0;
    instance->_height = 0;

    HINSTANCE hInstance = GetModuleHandleA(0);

    const char* className = "SysWindowClass";

    if (!_SysWindow_Registered)
    {
        _SysWindow_Registered = 1;
        WNDCLASSA window_class = {};
        window_class.lpfnWndProc = _SysWindow_MessageHandler;
        window_class.hInstance = hInstance;
        window_class.lpszClassName = className;
        window_class.hCursor = LoadCursorA(0, IDC_ARROW);
        RegisterClassA(&window_class);
    }

    long lStyle = WS_VISIBLE;

    // Makes default window
    // lStyle += WS_OVERLAPPEDWINDOW;

    RECT rect = { 0, 0, (long)clientWidth, (long)clientHeight };
    AdjustWindowRect(&rect, lStyle, false);
    int windowWidth = rect.right - rect.left;
    int windowHeight = rect.bottom - rect.top;

    _SysWindow_InitBitmap(instance);
    _SysWindow_ResetBitmap(instance, clientWidth, clientHeight);

    instance->_hwnd = CreateWindowExA
    (
        0,
        className, "SysWindow", lStyle,
        (long)x, (long)y, windowWidth, windowHeight,
        NULL, NULL, hInstance, NULL
    );

    assert(instance->_hwnd != NULL);

    SetWindowLongPtrA(instance->_hwnd, GWLP_USERDATA, (int64_t)(instance));

    // Forces window to update style
    // Setting lStyle before CreateWindow() wont work
    SetWindowLongA(instance->_hwnd, GWL_STYLE, lStyle);
    SetWindowPos(instance->_hwnd, NULL, 0,0,0,0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOOWNERZORDER);

    return instance;
}
bool SysWindow_Exists(SysWindow* instance)
{
    return instance->_hwnd != 0;
}
void SysWindow_Destroy(SysWindow* instance)
{
    if (!SysWindow_Exists(instance)) return;
    DestroyWindow(instance->_hwnd);
    instance->_hwnd = 0;
}
void SysWindow_Update(SysWindow* instance)
{
    if (!SysWindow_Exists(instance)) return;

    MSG message = {};

    while (PeekMessageA(&message, NULL, 0, 0, PM_REMOVE))
        DispatchMessageA(&message);

    InvalidateRect(instance->_hwnd, NULL, false);
    UpdateWindow(instance->_hwnd);
}
void SysWindow_SetPixel(SysWindow* instance, int x, int y, uint32_t pixel)
{
    if (!SysWindow_Exists(instance)) return;

    // window bitmap is bottom-up
    y = instance->_height - 1 - y;

    instance->_pixels[x + y * instance->_width] = pixel;
}
void SysWindow_SetPixels(SysWindow* instance, uint32_t* pixels, int width, int height)
{
    if (!SysWindow_Exists(instance)) return;

    // copy from Top-Down bitmap to Bottom-Up bitmap

    for (int y = 0; y < height; y++)
    for (int x = 0; x < width; x++)
    {
        uint32_t pixel = pixels[x + y * width];
        int y2 = height - 1 - y;
        instance->_pixels[x + y2 * width] = pixel;
    }
}
void SysWindow_SetPixelsScaled(SysWindow* instance, uint32_t* pixels, int width, int height, int scale)
{
    if (!SysWindow_Exists(instance)) return;

    for (int y = 0; y < height; y++)
    for (int x = 0; x < width; x++)
    {
        uint32_t pixel = pixels[x + y * width];
        // pixel = PixelToBwPixel(pixel);
        int x2 = x * scale;
        int y2 = y * scale;
        for (int i = 0; i < scale; i++)
        for (int j = 0; j < scale; j++)
            SysWindow_SetPixel(instance, x2+i, y2+j, pixel);
    }
}
void SysWindow_SetPixelsScaled2(SysWindow* instance, uint8_t* pixels, int width, int height, int scale)
{
    if (!SysWindow_Exists(instance)) return;

    for (int y = 0; y < height; y++)
    for (int x = 0; x < width; x++)
    {
        uint32_t pixel = pixels[x + y * width];

        float fraction = (float)pixel / 255;
        pixel = 0x00FFFFFF * fraction;

        int x2 = x * scale;
        int y2 = y * scale;
        for (int i = 0; i < scale; i++)
        for (int j = 0; j < scale; j++)
            SysWindow_SetPixel(instance, x2+i, y2+j, pixel);
    }
}
bool SysWindow_KeyDown_W(SysWindow* instance) { return instance->keydown_W; }
bool SysWindow_KeyDown_A(SysWindow* instance) { return instance->keydown_A; }
bool SysWindow_KeyDown_S(SysWindow* instance) { return instance->keydown_S; }
bool SysWindow_KeyDown_D(SysWindow* instance) { return instance->keydown_D; }
bool SysWindow_KeyDown_E(SysWindow* instance) { return instance->keydown_E; }
bool SysWindow_KeyDown_Q(SysWindow* instance) { return instance->keydown_Q; }
bool SysWindow_KeyDown_UP(SysWindow* instance) { return instance->keydown_UP; }
bool SysWindow_KeyDown_LEFT(SysWindow* instance) { return instance->keydown_LEFT; }
bool SysWindow_KeyDown_DOWN(SysWindow* instance) { return instance->keydown_DOWN; }
bool SysWindow_KeyDown_RIGHT(SysWindow* instance) { return instance->keydown_RIGHT; }
