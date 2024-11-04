#pragma once

#include "RaylibWrap.h"

static int _width;
static int _height;

void CreateWindow(int width, int height, const char* title)
{
    _width = width;
    _height = height;

    // TODO
    // FLAG_VSYNC_HINT seems to work
    // but, creates enforses target framerate and brakes main loop
    // SetConfigFlags(ConfigFlags::FLAG_VSYNC_HINT);

    Ray_InitWindow(width, height, title);
	Ray_rlDisableBackfaceCulling();
    Ray_HideCursor();

    // Fullscreen
    // auto monitor = Raylib::GetCurrentMonitor();
    // auto width = Raylib::GetMonitorWidth(monitor);
    // auto height = Raylib::GetMonitorHeight(monitor);
    // Raylib::SetWindowSize(width, height);
    // Raylib::ToggleFullscreen();
}

void DrawBox(Vector3 position, Vector3 rotation, Vector3 halfs, Ray_Color color, Ray_Color colorWire)
{
    Vector3 v0 = { -halfs.x, -halfs.y, -halfs.z };
    Vector3 v1 = { -halfs.x, -halfs.y,  halfs.z };
    Vector3 v2 = { -halfs.x,  halfs.y, -halfs.z };
    Vector3 v3 = { -halfs.x,  halfs.y,  halfs.z };
    Vector3 v4 = {  halfs.x, -halfs.y, -halfs.z };
    Vector3 v5 = {  halfs.x, -halfs.y,  halfs.z };
    Vector3 v6 = {  halfs.x,  halfs.y, -halfs.z };
    Vector3 v7 = {  halfs.x,  halfs.y,  halfs.z };

    auto rotMat = MatrixRotate(rotation);

    v0 *= rotMat;
    v1 *= rotMat;
    v2 *= rotMat;
    v3 *= rotMat;
    v4 *= rotMat;
    v5 *= rotMat;
    v6 *= rotMat;
    v7 *= rotMat;

    v0 += position;
    v1 += position;
    v2 += position;
    v3 += position;
    v4 += position;
    v5 += position;
    v6 += position;
    v7 += position;

    Ray_Vector3 _v0 = (Ray_Vector3){ v0.x, v0.y, v0.z };
    Ray_Vector3 _v1 = (Ray_Vector3){ v1.x, v1.y, v1.z };
    Ray_Vector3 _v2 = (Ray_Vector3){ v2.x, v2.y, v2.z };
    Ray_Vector3 _v3 = (Ray_Vector3){ v3.x, v3.y, v3.z };
    Ray_Vector3 _v4 = (Ray_Vector3){ v4.x, v4.y, v4.z };
    Ray_Vector3 _v5 = (Ray_Vector3){ v5.x, v5.y, v5.z };
    Ray_Vector3 _v6 = (Ray_Vector3){ v6.x, v6.y, v6.z };
    Ray_Vector3 _v7 = (Ray_Vector3){ v7.x, v7.y, v7.z };

    Ray_DrawTriangle3D(_v1, _v3, _v2, color);
    Ray_DrawTriangle3D(_v1, _v2, _v0, color);
    Ray_DrawTriangle3D(_v4, _v6, _v7, color);
    Ray_DrawTriangle3D(_v4, _v7, _v5, color);
    Ray_DrawTriangle3D(_v0, _v2, _v6, color);
    Ray_DrawTriangle3D(_v0, _v6, _v4, color);
    Ray_DrawTriangle3D(_v2, _v3, _v7, color);
    Ray_DrawTriangle3D(_v2, _v7, _v6, color);
    Ray_DrawTriangle3D(_v1, _v0, _v4, color);
    Ray_DrawTriangle3D(_v1, _v4, _v5, color);
    Ray_DrawTriangle3D(_v5, _v7, _v3, color);
    Ray_DrawTriangle3D(_v5, _v3, _v1, color);

    Ray_DrawLine3D(_v0, _v1, colorWire);
    Ray_DrawLine3D(_v1, _v5, colorWire);
    Ray_DrawLine3D(_v5, _v4, colorWire);
    Ray_DrawLine3D(_v4, _v0, colorWire);
    Ray_DrawLine3D(_v2, _v3, colorWire);
    Ray_DrawLine3D(_v3, _v7, colorWire);
    Ray_DrawLine3D(_v7, _v6, colorWire);
    Ray_DrawLine3D(_v6, _v2, colorWire);
    Ray_DrawLine3D(_v0, _v2, colorWire);
    Ray_DrawLine3D(_v4, _v6, colorWire);
    Ray_DrawLine3D(_v1, _v3, colorWire);
    Ray_DrawLine3D(_v5, _v7, colorWire);
}
void DrawBoxWire(Vector3 position, Vector3 rotation, Vector3 halfs, Ray_Color color)
{
    Vector3 v0 = { -halfs.x, -halfs.y, -halfs.z };
    Vector3 v1 = { -halfs.x, -halfs.y,  halfs.z };
    Vector3 v2 = { -halfs.x,  halfs.y, -halfs.z };
    Vector3 v3 = { -halfs.x,  halfs.y,  halfs.z };
    Vector3 v4 = {  halfs.x, -halfs.y, -halfs.z };
    Vector3 v5 = {  halfs.x, -halfs.y,  halfs.z };
    Vector3 v6 = {  halfs.x,  halfs.y, -halfs.z };
    Vector3 v7 = {  halfs.x,  halfs.y,  halfs.z };

    auto rotMat = MatrixRotate(rotation);

    v0 *= rotMat;
    v1 *= rotMat;
    v2 *= rotMat;
    v3 *= rotMat;
    v4 *= rotMat;
    v5 *= rotMat;
    v6 *= rotMat;
    v7 *= rotMat;

    v0 += position;
    v1 += position;
    v2 += position;
    v3 += position;
    v4 += position;
    v5 += position;
    v6 += position;
    v7 += position;

    Ray_Vector3 _v0 = (Ray_Vector3){ v0.x, v0.y, v0.z };
    Ray_Vector3 _v1 = (Ray_Vector3){ v1.x, v1.y, v1.z };
    Ray_Vector3 _v2 = (Ray_Vector3){ v2.x, v2.y, v2.z };
    Ray_Vector3 _v3 = (Ray_Vector3){ v3.x, v3.y, v3.z };
    Ray_Vector3 _v4 = (Ray_Vector3){ v4.x, v4.y, v4.z };
    Ray_Vector3 _v5 = (Ray_Vector3){ v5.x, v5.y, v5.z };
    Ray_Vector3 _v6 = (Ray_Vector3){ v6.x, v6.y, v6.z };
    Ray_Vector3 _v7 = (Ray_Vector3){ v7.x, v7.y, v7.z };

    Ray_DrawLine3D(_v0, _v1, color);
    Ray_DrawLine3D(_v1, _v5, color);
    Ray_DrawLine3D(_v5, _v4, color);
    Ray_DrawLine3D(_v4, _v0, color);
    Ray_DrawLine3D(_v2, _v3, color);
    Ray_DrawLine3D(_v3, _v7, color);
    Ray_DrawLine3D(_v7, _v6, color);
    Ray_DrawLine3D(_v6, _v2, color);
    Ray_DrawLine3D(_v0, _v2, color);
    Ray_DrawLine3D(_v4, _v6, color);
    Ray_DrawLine3D(_v1, _v3, color);
    Ray_DrawLine3D(_v5, _v7, color);
}
void DrawBoxTest(Vector3 position, Vector3 rotation, Vector3 halfs, Vector3 offsetPosition, Ray_Color color, Ray_Color colorWire)
{
    Vector3 v0 = { -halfs.x, -halfs.y, -halfs.z };
    Vector3 v1 = { -halfs.x, -halfs.y,  halfs.z };
    Vector3 v2 = { -halfs.x,  halfs.y, -halfs.z };
    Vector3 v3 = { -halfs.x,  halfs.y,  halfs.z };
    Vector3 v4 = {  halfs.x, -halfs.y, -halfs.z };
    Vector3 v5 = {  halfs.x, -halfs.y,  halfs.z };
    Vector3 v6 = {  halfs.x,  halfs.y, -halfs.z };
    Vector3 v7 = {  halfs.x,  halfs.y,  halfs.z };

    v0 += offsetPosition;
    v1 += offsetPosition;
    v2 += offsetPosition;
    v3 += offsetPosition;
    v4 += offsetPosition;
    v5 += offsetPosition;
    v6 += offsetPosition;
    v7 += offsetPosition;

    auto rotMat = MatrixRotate(rotation);

    v0 *= rotMat;
    v1 *= rotMat;
    v2 *= rotMat;
    v3 *= rotMat;
    v4 *= rotMat;
    v5 *= rotMat;
    v6 *= rotMat;
    v7 *= rotMat;

    v0 += position;
    v1 += position;
    v2 += position;
    v3 += position;
    v4 += position;
    v5 += position;
    v6 += position;
    v7 += position;

    Ray_Vector3 _v0 = (Ray_Vector3){ v0.x, v0.y, v0.z };
    Ray_Vector3 _v1 = (Ray_Vector3){ v1.x, v1.y, v1.z };
    Ray_Vector3 _v2 = (Ray_Vector3){ v2.x, v2.y, v2.z };
    Ray_Vector3 _v3 = (Ray_Vector3){ v3.x, v3.y, v3.z };
    Ray_Vector3 _v4 = (Ray_Vector3){ v4.x, v4.y, v4.z };
    Ray_Vector3 _v5 = (Ray_Vector3){ v5.x, v5.y, v5.z };
    Ray_Vector3 _v6 = (Ray_Vector3){ v6.x, v6.y, v6.z };
    Ray_Vector3 _v7 = (Ray_Vector3){ v7.x, v7.y, v7.z };

    Ray_DrawTriangle3D(_v1, _v3, _v2, color);
    Ray_DrawTriangle3D(_v1, _v2, _v0, color);
    Ray_DrawTriangle3D(_v4, _v6, _v7, color);
    Ray_DrawTriangle3D(_v4, _v7, _v5, color);
    Ray_DrawTriangle3D(_v0, _v2, _v6, color);
    Ray_DrawTriangle3D(_v0, _v6, _v4, color);
    Ray_DrawTriangle3D(_v2, _v3, _v7, color);
    Ray_DrawTriangle3D(_v2, _v7, _v6, color);
    Ray_DrawTriangle3D(_v1, _v0, _v4, color);
    Ray_DrawTriangle3D(_v1, _v4, _v5, color);
    Ray_DrawTriangle3D(_v5, _v7, _v3, color);
    Ray_DrawTriangle3D(_v5, _v3, _v1, color);

    Ray_DrawLine3D(_v0, _v1, colorWire);
    Ray_DrawLine3D(_v1, _v5, colorWire);
    Ray_DrawLine3D(_v5, _v4, colorWire);
    Ray_DrawLine3D(_v4, _v0, colorWire);
    Ray_DrawLine3D(_v2, _v3, colorWire);
    Ray_DrawLine3D(_v3, _v7, colorWire);
    Ray_DrawLine3D(_v7, _v6, colorWire);
    Ray_DrawLine3D(_v6, _v2, colorWire);
    Ray_DrawLine3D(_v0, _v2, colorWire);
    Ray_DrawLine3D(_v4, _v6, colorWire);
    Ray_DrawLine3D(_v1, _v3, colorWire);
    Ray_DrawLine3D(_v5, _v7, colorWire);
}
void DrawBox(Vector3 position, Vector3 rotation, Vector3 halfs, Ray_Color color)
{
    Vector3 v0 = { -halfs.x, -halfs.y, -halfs.z };
    Vector3 v1 = { -halfs.x, -halfs.y,  halfs.z };
    Vector3 v2 = { -halfs.x,  halfs.y, -halfs.z };
    Vector3 v3 = { -halfs.x,  halfs.y,  halfs.z };
    Vector3 v4 = {  halfs.x, -halfs.y, -halfs.z };
    Vector3 v5 = {  halfs.x, -halfs.y,  halfs.z };
    Vector3 v6 = {  halfs.x,  halfs.y, -halfs.z };
    Vector3 v7 = {  halfs.x,  halfs.y,  halfs.z };

    auto rotMat = MatrixRotate(rotation);

    v0 *= rotMat;
    v1 *= rotMat;
    v2 *= rotMat;
    v3 *= rotMat;
    v4 *= rotMat;
    v5 *= rotMat;
    v6 *= rotMat;
    v7 *= rotMat;

    v0 += position;
    v1 += position;
    v2 += position;
    v3 += position;
    v4 += position;
    v5 += position;
    v6 += position;

    Ray_Vector3 _v0 = (Ray_Vector3){ v0.x, v0.y, v0.z };
    Ray_Vector3 _v1 = (Ray_Vector3){ v1.x, v1.y, v1.z };
    Ray_Vector3 _v2 = (Ray_Vector3){ v2.x, v2.y, v2.z };
    Ray_Vector3 _v3 = (Ray_Vector3){ v3.x, v3.y, v3.z };
    Ray_Vector3 _v4 = (Ray_Vector3){ v4.x, v4.y, v4.z };
    Ray_Vector3 _v5 = (Ray_Vector3){ v5.x, v5.y, v5.z };
    Ray_Vector3 _v6 = (Ray_Vector3){ v6.x, v6.y, v6.z };
    Ray_Vector3 _v7 = (Ray_Vector3){ v7.x, v7.y, v7.z };

    Ray_DrawTriangle3D(_v1, _v3, _v2, color);
    Ray_DrawTriangle3D(_v1, _v2, _v0, color);
    Ray_DrawTriangle3D(_v4, _v6, _v7, color);
    Ray_DrawTriangle3D(_v4, _v7, _v5, color);
    Ray_DrawTriangle3D(_v0, _v2, _v6, color);
    Ray_DrawTriangle3D(_v0, _v6, _v4, color);
    Ray_DrawTriangle3D(_v2, _v3, _v7, color);
    Ray_DrawTriangle3D(_v2, _v7, _v6, color);
    Ray_DrawTriangle3D(_v1, _v0, _v4, color);
    Ray_DrawTriangle3D(_v1, _v4, _v5, color);
    Ray_DrawTriangle3D(_v5, _v7, _v3, color);
    Ray_DrawTriangle3D(_v5, _v3, _v1, color);
}
void DrawAxis(Vector3 position, Vector3 rotation, float scale)
{
    auto origin = Vector3Zero();
    auto right = Vector3Right();
    auto up = Vector3Up();
    auto forward = Vector3Forward();

    right   *= scale;
    up      *= scale;
    forward *= scale;

    auto rotMat = MatrixRotate(rotation);

    right   *= rotMat;
    up      *= rotMat;
    forward *= rotMat;

    origin  += position;
    right   += position;
    up      += position;
    forward += position;

    Ray_Vector3 _origin = { origin.x, origin.y, origin.z };
    Ray_Vector3 _right = { right.x, right.y, right.z };
    Ray_Vector3 _up = { up.x, up.y, up.z };
    Ray_Vector3 _forward = { forward.x, forward.y, forward.z };

    Ray_DrawLine3D(_origin, _right,   RAY_RED);
    Ray_DrawLine3D(_origin, _up,      RAY_GREEN);
    Ray_DrawLine3D(_origin, _forward, RAY_BLUE);
}
void DrawCube(Vector3 position, Vector3 size, Ray_Color color)
{
    Ray_Vector3 _position = { position.x, position.y, position.z };
    Ray_Vector3 _size = { size.x, size.y, size.z };
    Ray_DrawCubeV(_position, _size, color);
}
void DrawBound(const Bound& bound, Ray_Color color)
{
    auto center = BoundCenter(&bound);
    auto size = BoundSize(&bound);
    DrawCube(center, size, RAY_WHITE);
}
void DrawSphere(Vector3 position, float radius, Ray_Color color)
{
    Ray_Vector3 _position = { position.x, position.y, position.z };
    Ray_DrawSphere(_position, radius, color);
}

Vector2 GetMouseDelta()
{
    Ray_Vector2 result = Ray_GetMouseDelta();
    return (Vector2){ result.x, result.y };
}

Vector2 GetWasdInput()
{
    int x = 0;
    int y = 0;
    if (Ray_IsKeyDown(RAY_KEY_W)) y++;
    if (Ray_IsKeyDown(RAY_KEY_A)) x--;
    if (Ray_IsKeyDown(RAY_KEY_S)) y--;
    if (Ray_IsKeyDown(RAY_KEY_D)) x++;
    Vector2 result = Vector2Normalize({ (float)x, (float)y });
    return (Vector2){ result.x, result.y };
}
Vector2 GetArrowInput()
{
    int x = 0;
    int y = 0;
    if (Ray_IsKeyDown(RAY_KEY_UP))    y++;
    if (Ray_IsKeyDown(RAY_KEY_LEFT))  x--;
    if (Ray_IsKeyDown(RAY_KEY_DOWN))  y--;
    if (Ray_IsKeyDown(RAY_KEY_RIGHT)) x++;
    Vector2 result = Vector2Normalize({ (float)x, (float)y });
    return (Vector2){ result.x, result.y };
}
Vector2 GetMouseInput()
{
    auto sensitivity = 0.005f;
    auto delta = GetMouseDelta();
    auto deltaX = delta.x * sensitivity;
    auto deltaY = delta.y * sensitivity;

    // moving mouse right creates negative Y
    // maybe its done to simplify camera rotation
    // but I dont like it
    deltaY = -deltaY;

    return (Vector2){ deltaX, deltaY };
}

void RenderAxisCubes()
{
    DrawCube({ 10, 0, 0 }, { 1, 1, 1 }, RAY_RED);
    DrawCube({ 0, 10, 0 }, { 1, 1, 1 }, RAY_GREEN);
    DrawCube({ 0, 0, 10 }, { 1, 1, 1 }, RAY_BLUE);
    DrawCube({ -10, 0, 0 }, { 1, 1, 1 }, RAY_VIOLET);
    DrawCube({ 0, -10, 0 }, { 1, 1, 1 }, RAY_YELLOW);
    DrawCube({ 0, 0, -10 }, { 1, 1, 1 }, RAY_ORANGE);
}
void DrawBoxGreen(const Box& box)
{
    DrawBox(box.position, box.rotation, box.halfExtent, RAY_LIME, RAY_RED);
}
void DrawBoxBlue(const Box& box)
{
    DrawBox(box.position, box.rotation, box.halfExtent, RAY_BLUE, RAY_SKYBLUE);
}

void BeginDrawing(int cpu)
{
    Ray_ClearBackground(RAY_BLACK);

    char msg[7] = "CPU 00";

    if (cpu > 99)
    {
        msg[5] = '9';
        msg[6] = '9';
    }
    else if (cpu > 9)
    {
        snprintf(msg+4, 3, "%d", cpu);
        // itoa(cpu, msg+4, 10);
    }
    else if (cpu > 0)
    {
        snprintf(msg+5, 2, "%d", cpu);
        // itoa(cpu, msg+5, 10);
    }

    Ray_Color color = cpu >= 50 ? RAY_RED : RAY_LIGHTGRAY;
    Ray_DrawText(msg, 110, 0, 20, color);

    Ray_DrawFPS(0, 0);
    Ray_SetMousePosition(_width / 2, _height / 2);
    Ray_BeginDrawing();
}
void EndDrawing()
{
    Ray_EndDrawing();
}
void StartMode3d(Vector3 position, Vector3 target, Vector3 up, float fovy, int projection)
{
    Ray_Vector3 _position = { position.x, position.y, position.z };
    Ray_Vector3 _target = { target.x, target.y, target.z };
    Ray_Vector3 _up = { up.x, up.y, up.z };

    Ray_Camera3D camera3d;

    camera3d.position = _position;
    camera3d.target = _target;
    camera3d.up = _up;
    camera3d.fovy = fovy;
    camera3d.projection = projection;

    Ray_BeginMode3D(camera3d);
}
void StartMode3d(Vector3 position, float yaw, float pitch)
{
    Vector3 up      = { 0, 1, 0 };
    Vector3 forward = { 0, 0, 1 };

    forward = Vector3RotateX(forward, pitch);
    forward = Vector3RotateY(forward, -yaw);
    up = Vector3RotateX(up, pitch);
    up = Vector3RotateY(up, -yaw);

    auto target = Vector3Add(position, forward);
    auto fovy = 90;
    auto projection = 0;

    StartMode3d(position, target, up, fovy, projection);
}
void StartMode3d(const Camera& camera)
{
    StartMode3d(camera.position, camera.yaw, camera.pitch);
}
void EndMode3D()
{
    Ray_EndMode3D();
}
