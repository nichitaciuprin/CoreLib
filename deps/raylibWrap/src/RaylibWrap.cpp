/*
this code does 2 things:
1. Limits raylib headers
2. Adds prefix to all names
3. Inverts x axis. I have no idea why its inverted in raylib
*/

#include <RaylibWrap.h>

#include <raylib.h>
#include <raymath.h>
#include <rlgl.h>

#include <stdio.h>

inline static Color ToColor(Ray_Color v) { return (Color){ v.r, v.g, v.b, v.a }; }
inline static Vector2 ToVector2(Ray_Vector2 v) { return (Vector2){ v.x, v.y }; }
inline static Vector3 ToVector3(Ray_Vector3 v) { return (Vector3){ v.x, v.y, v.z }; }
inline static Camera3D ToCamera3D(Ray_Camera3D v)
{
    Camera3D result;
    result.position = ToVector3(v.position);
    result.target = ToVector3(v.target);
    result.up = ToVector3(v.up);
    result.fovy = v.fovy;
    result.projection = v.projection;
    return result;
}

void Ray_InitWindow(int width, int height, const char* title)
{
    InitWindow(width, height, title);
}
void Ray_CloseWindow()
{
    CloseWindow();
}
bool Ray_WindowShouldClose()
{
    return WindowShouldClose();
}
void Ray_HideCursor()
{
    HideCursor();
}
void Ray_rlDisableBackfaceCulling()
{
    rlDisableBackfaceCulling();
}
void Ray_PollInputEvents()
{
    PollInputEvents();
}

void Ray_DrawFPS(int posX, int posY)
{
    DrawFPS(posX, posY);
}
void Ray_DrawText(const char* text, int posX, int posY, int fontSize, Ray_Color color)
{
    Color _color = ToColor(color);
    DrawText(text, posX, posY, fontSize, _color);
}

Ray_Vector2 Ray_GetMouseDelta()
{
    Vector2 result = GetMouseDelta();
    return (Ray_Vector2){ result.x, result.y };
}
void Ray_SetMousePosition(int x, int y)
{
    SetMousePosition(x, y);
}

void Ray_DrawTriangle3D(Ray_Vector3 v1, Ray_Vector3 v2, Ray_Vector3 v3, Ray_Color color)
{
    v1.x = -v1.x;
    v2.x = -v2.x;
    v3.x = -v3.x;
    Color _color = ToColor(color);
    Vector3 _v1 = ToVector3(v1);
    Vector3 _v2 = ToVector3(v2);
    Vector3 _v3 = ToVector3(v3);
    DrawTriangle3D(_v1, _v2, _v3, _color);
}
void Ray_DrawLine3D(Ray_Vector3 v1, Ray_Vector3 v2, Ray_Color color)
{
    v1.x = -v1.x;
    v2.x = -v2.x;
    Color _color = ToColor(color);
    Vector3 _v1 = ToVector3(v1);
    Vector3 _v2 = ToVector3(v2);
    DrawLine3D(_v1, _v2, _color);
}
void Ray_DrawPlane(Ray_Vector3 position, Ray_Vector2 size, Ray_Color color)
{
    position.x = -position.x;
    size.x = -size.x; // TODO remove invert?
    Color _color = ToColor(color);
    Vector3 _position = ToVector3(position);
    Vector2 _size = ToVector2(size);
    DrawPlane(_position, _size, _color);
}
void Ray_DrawSphere(Ray_Vector3 position, float radius, Ray_Color color)
{
    position.x = -position.x;
    Color _color = ToColor(color);
    Vector3 _position = ToVector3(position);
    DrawSphere(_position, radius, _color);
}
void Ray_DrawSphereWires(Ray_Vector3 position, float radius, Ray_Color color)
{
    position.x = -position.x;
    Color _color = ToColor(color);
    Vector3 _position = ToVector3(position);
    DrawSphereWires(_position, radius, 2, 6, _color);
}
void Ray_DrawCubeV(Ray_Vector3 position, Ray_Vector3 size, Ray_Color color)
{
    position.x = -position.x;
    size.x = -size.x; // TODO remove invert?
    Color _color = ToColor(color);
    Vector3 _position = ToVector3(position);
    Vector3 _size = ToVector3(size);
    DrawCubeV(_position, _size, _color);
}
void Ray_DrawCylinder(Ray_Vector3 position, float radius, float height, Ray_Color color)
{
    position.x = -position.x;
    Color _color = ToColor(color);
    Vector3 _position = ToVector3(position);
    DrawCylinder(_position, radius, radius, height, 10, _color);
}

void Ray_ClearBackground(Ray_Color color)
{
    Color _color = ToColor(color);
    ClearBackground(_color);
}
void Ray_BeginDrawing()
{
    BeginDrawing();
}
void Ray_EndDrawing()
{
    EndDrawing();
}
void Ray_BeginMode3D(Ray_Camera3D camera)
{
    camera.position.x = -camera.position.x;
    camera.target.x = -camera.target.x;
    camera.up.x = -camera.up.x;
    Camera3D _camera = ToCamera3D(camera);
    BeginMode3D(_camera);
}
void Ray_EndMode3D()
{
    EndMode3D();
}

bool Ray_IsKeyPressed(int key)
{
    return IsKeyPressed(key);
}
bool Ray_IsKeyDown(int key)
{
    return IsKeyDown(key);
}
