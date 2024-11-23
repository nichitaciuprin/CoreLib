#pragma once

#include "float.h"
#include "assert.h"

#include "Color.h"
#include "Clipping.h"
#include "Models.h"

typedef struct Bitmap
{
    uint32_t* pixels;
    float* zbuffer;
    int width;
    int height;
    int maxX;
    int maxY;
    int pixelsSize;
    int zbufferSize;
}
Bitmap;

Bitmap BitmapCreate(int width, int height)
{
    Bitmap instance;

    assert(width > 0);
    assert(height > 0);

    instance.width = width;
    instance.height = height;

    instance.maxX = width - 1;
    instance.maxY = height - 1;

    int size = width * height;

    instance.pixelsSize = size;
    instance.zbufferSize = size;

    instance.pixels = (uint32_t*)malloc(sizeof(uint32_t) * size);
    instance.zbuffer = (float*)malloc(sizeof(float) * size);

    return instance;
}
void BitmapDestroy(Bitmap* instance)
{
    free(instance->pixels);
    free(instance->zbuffer);
}

void BitmapReset(Bitmap* instance)
{
    memset((void*)instance->pixels, 0, instance->zbufferSize * sizeof(uint32_t));

    // can we, somehow, do memset here?
    for (int i = 0; i < instance->zbufferSize; i++)
        instance->zbuffer[i] = FLT_MAX;
}

void BitmapSetPixel(Bitmap* instance, int x, int y, Color color)
{
    assert(0 <= x && x < instance->width);
    assert(0 <= y && y < instance->height);

    int i = x + y * instance->width;

    instance->pixels[i] = color;
}
void BitmapSetPixelZ(Bitmap* instance, int x, int y, float z, Color color)
{
    assert(0 <= x && x < instance->width);
    assert(0 <= y && y < instance->height);

    int i = x + y * instance->width;

    if (instance->zbuffer[i] < z) return;
    instance->zbuffer[i] = z;

    instance->pixels[i] = color;
}

void BitmapDrawLineHorizontal(Bitmap* instance, int y, int xl, int xr, float zl, float zr, Color color)
{
    int count = xr - xl;
    float diff = zr - zl;
    float offset = diff / count;

    for (int i = 0; i < count + 1; i++)
    {
        int x = xl + i;
        BitmapSetPixelZ(instance, x, y, zl, color);
        zl += offset;
    }
}

void BitmapFillAll(Bitmap* instance, Color color)
{
    for (int i = 0; i < instance->pixelsSize; i++)
        instance->pixels[i] = color;
}
void BitmapFillBorder(Bitmap* instance, Color color)
{
    int x = instance->maxX;
    int y = instance->maxY;
    for (int i = 0; i < instance->width;  i++) BitmapSetPixel(instance, i, 0, color);
    for (int i = 0; i < instance->width;  i++) BitmapSetPixel(instance, i, y, color);
    for (int i = 0; i < instance->height; i++) BitmapSetPixel(instance, 0, i, color);
    for (int i = 0; i < instance->height; i++) BitmapSetPixel(instance, x, i, color);
}
void BitmapFillCross(Bitmap* instance, Color color)
{
    int centerX = instance->width / 2;
    int centerY = instance->height / 2;
    for (int i = 0; i < instance->width;  i++) BitmapSetPixel(instance, i, centerY, color);
    for (int i = 0; i < instance->height; i++) BitmapSetPixel(instance, centerX, i, color);
}
void BitmapFillSqare(Bitmap* instance, Color color)
{
    int xl = instance->width / 4;
    int xr = instance->width / 4 * 3;
    int yl = instance->height / 4;
    int yr = instance->height / 4 * 3;
    for (int i = xl; i < xr; i++) BitmapSetPixel(instance, i, yl, color);
    for (int i = xl; i < xr; i++) BitmapSetPixel(instance, i, yr, color);
    for (int i = yl; i < yr; i++) BitmapSetPixel(instance, xl, i, color);
    for (int i = yl; i < yr; i++) BitmapSetPixel(instance, xr, i, color);
}

void BitmapApplyFade(Bitmap* instance)
{
    for (int i = 0; i < instance->pixelsSize; i++)
    {
        float depthLength = 100;
        float factor = MathClampFloat(instance->zbuffer[i], 0.0f, depthLength);
        factor /= depthLength;
        factor = 1 - factor;
        int byte = (int)(factor * 255);

        uint32_t color = 0;
        color += byte; color = color << 8;
        color += byte; color = color << 8;
        color += byte; color = color << 8;
        color += byte;

        instance->pixels[i] = color;
    }
}
void BitmapApplyPerspective(Vector3* v)
{
    if (v->z == 0) return;
    v->x /= v->z;
    v->y /= v->z;
}
void BitmapToScreenSpace(Bitmap* instance, Vector3* v)
{
    v->y = -v->y;
    v->x += 1.0f;
    v->y += 1.0f;
    v->x /= 2.0f;
    v->y /= 2.0f;
    v->x = instance->maxX * v->x;
    v->y = instance->maxY * v->y;
}

float GetArea(Vector3 v1, Vector3 v2, Vector3 v3)
{
    int r1 = (int)v1.x * ((int)v2.y - (int)v3.y);
    int r2 = (int)v2.x * ((int)v3.y - (int)v1.y);
    int r3 = (int)v3.x * ((int)v1.y - (int)v2.y);
    return abs((r1 + r2 + r3) / 2.0f);
}
bool IsInside(Vector3 v1, Vector3 v2, Vector3 v3, Vector3 p)
{
    float A0 = GetArea(v1, v2, v3);
    float A1 = GetArea( p, v2, v3);
    float A2 = GetArea(v1,  p, v3);
    float A3 = GetArea(v1, v2,  p);
    return A0 == (A1 + A2 + A3);
}
float GetDepth(Vector3 p1, Vector3 p2, Vector3 p3, float x, float y)
{
    // Barycentric coordinates
    float det = (p2.y - p3.y) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.y - p3.y);
    float l1 = ((p2.y - p3.y) * (x - p3.x) + (p3.x - p2.x) * (y - p3.y)) / det;
    float l2 = ((p3.y - p1.y) * (x - p3.x) + (p1.x - p3.x) * (y - p3.y)) / det;
    float l3 = 1.0f - l1 - l2;
    return l1 * p1.z + l2 * p2.z + l3 * p3.z;
}

void BitmapDrawLineScreenSpaceV1(Bitmap* instance, Vector3 v0, Vector3 v1, Color color)
{
    int x0 = (int)v0.x;
    int y0 = (int)v0.y;

    int x1 = (int)v1.x;
    int y1 = (int)v1.y;

    int dx =  abs(x1 - x0);
    int dy = -abs(y1 - y0);

    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;

    int err = dx + dy;
    int e2;

    while (true)
    {
        BitmapSetPixel(instance, x0, y0, color);
        if (x0 == x1 && y0 == y1) break;
        e2 = 2 * err;
        if (e2 >= dy) { err += dy; x0 += sx; }
        if (e2 <= dx) { err += dx; y0 += sy; }
    }
}
void BitmapDrawLineScreenSpaceV2(Bitmap* instance, Vector3 v0, Vector3 v1, Color color)
{
    int x0 = (int)v0.x;
    int y0 = (int)v0.y;

    int x1 = (int)v1.x;
    int y1 = (int)v1.y;

    int dx, sx;
    if (x0 < x1) { dx = x1 - x0; sx =  1; }
    else         { dx = x0 - x1; sx = -1; }

    int dy, sy;
    if (y0 < y1) { dy = y1 - y0; sy =  1; }
    else         { dy = y0 - y1; sy = -1; }

    int max; int* axis1; int val1;
    int min; int* axis2; int val2;
    if (dx > dy) { max = dx; axis1 = &y0; val1 = sy; min = dy; axis2 = &x0; val2 = sx; }
    else         { max = dy; axis1 = &x0; val1 = sx; min = dx; axis2 = &y0; val2 = sy; }

    int err = max / 2 - min;

    float offset = (v1.z - v0.z) / max;
    float z = v0.z;

    for (int i = 0; i < max; i++)
    {
        BitmapSetPixelZ(instance, x0, y0, z, color);
        if (err < 0) { err += max; (*axis1) += val1; }
                     { err -= min; (*axis2) += val2; }
        z += offset;
    }

    BitmapSetPixelZ(instance, x0, y0, z, color);
}
void BitmapDrawLineScreenSpace(Bitmap* instance, Vector3 v0, Vector3 v1, Color color)
{
    BitmapDrawLineScreenSpaceV2(instance, v0, v1, color);
}
void BitmapDrawLineNdc(Bitmap* instance, Vector3 v0, Vector3 v1, Color color)
{
    // REMOVE
    if (ClipLineLeft   (&v0, &v1)) return;
    if (ClipLineRight  (&v0, &v1)) return;
    if (ClipLineDown   (&v0, &v1)) return;
    if (ClipLineUp     (&v0, &v1)) return;

    BitmapToScreenSpace(instance, &v0);
    BitmapToScreenSpace(instance, &v1);
    BitmapDrawLineScreenSpace(instance, v0, v1, color);
}

void BitmapDrawTriangleScreenspaceV1(Bitmap* instance, Vector3 v0, Vector3 v1, Vector3 v2, Color color)
{
    int maxX = MathMaxFloat(v0.x, MathMaxFloat(v1.x, v2.x));
    int minX = MathMinFloat(v0.x, MathMinFloat(v1.x, v2.x));
    int maxY = MathMaxFloat(v0.y, MathMaxFloat(v1.y, v2.y));
    int minY = MathMinFloat(v0.y, MathMinFloat(v1.y, v2.y));

    for (int x = minX; x <= maxX; x++)
    for (int y = minY; y <= maxY; y++)
    {
        Vector3 v = { (float)x, (float)y, 0 };
        if (!IsInside(v0, v1, v2, v)) continue;
        float z = GetDepth(v0, v1, v2, x, y);
        BitmapSetPixelZ(instance, x, y, z, color);
    }
}
void BitmapDrawTriangleScreenspaceV2(Bitmap* instance, Vector3 v0, Vector3 v1, Vector3 v2, Color color)
{
    // TODO not accurate, improve

    // p0 is top
    // p1 is middle
    // p2 is bottom
    if (v0.y > v1.y) swap(v0, v1);
    if (v1.y > v2.y) swap(v1, v2);
    if (v0.y > v1.y) swap(v0, v1);

    int p0x = (int)v0.x;
    int p1x = (int)v1.x;
    int p2x = (int)v2.x;

    int p0y = (int)v0.y;
    int p1y = (int)v1.y;
    int p2y = (int)v2.y;

    int dx1 = p2x - p0x;
    int dx2 = p1x - p0x;
    int dx3 = p2x - p1x;
    int dy1 = p2y - p0y;
    int dy2 = p1y - p0y;
    int dy3 = p2y - p1y;
    int dir1 = MathSignInt(dx1);
    int dir2 = MathSignInt(dx2);
    int dir3 = MathSignInt(dx3);
    int dx1abs = MathAbsInt(dx1);
    int dx2abs = MathAbsInt(dx2);
    int dx3abs = MathAbsInt(dx3);
    int err1 = dy1 / 2 - dx1abs;
    int err2 = dy2 / 2 - dx2abs;
    int err3 = dy3 / 2 - dx3abs;

    // TODO check for 0 division?
    float offset1 = (v2.z - v0.z) / dy1;
    float offset2 = (v1.z - v0.z) / dy2;
    float offset3 = (v2.z - v1.z) / dy3;

    int y = p0y;

    int x1 = p0x;
    float z1 = v0.z;

    int x2;
    float z2;
    if (dy2 > 0) { x2 = p0x; z2 = v0.z; }
    else         { x2 = p1x; z2 = v1.z; }

    int cross = dx1 * dy2 - dy1 * dx2;

    int* xl; int* xr; float* zl; float* zr;
    if (cross < 0) { xl = &x1; xr = &x2; zl = &z1; zr = &z2; }
    else           { xl = &x2; xr = &x1; zl = &z2; zr = &z1; }

    for (int i = 0; i < dy2; i++)
    {
        while (err1 < 0) { err1 += dy1; x1 += dir1; }
        while (err2 < 0) { err2 += dy2; x2 += dir2; }
        BitmapDrawLineHorizontal(instance, y, *xl, *xr, *zl, *zr, color);
        y++;
        err1 -= dx1abs;
        err2 -= dx2abs;
        z1 += offset1;
        z2 += offset2;
    }
    for (int i = 0; i < dy3; i++)
    {
        while (err1 < 0) { err1 += dy1; x1 += dir1; }
        while (err3 < 0) { err3 += dy3; x2 += dir3; }
        BitmapDrawLineHorizontal(instance, y, *xl, *xr, *zl, *zr, color);
        y++;
        err1 -= dx1abs;
        err3 -= dx3abs;
        z1 += offset1;
        z2 += offset3;
    }
    BitmapDrawLineHorizontal(instance, y, *xl, *xr, *zl, *zr, color);
}
void BitmapDrawTriangleScreenspace(Bitmap* instance, Vector3 v0, Vector3 v1, Vector3 v2, Color color)
{
    BitmapDrawTriangleScreenspaceV1(instance, v0, v1, v2, color);
}
void BitmapDrawTriangleNdc(Bitmap* instance, Vector3 v0, Vector3 v1, Vector3 v2, Color color)
{
    // vertex must be in this range
    // -1 <= x <= 1
    // -1 <= y <= 1
    //  0 <= z <= inf

    assert(-1 <= v0.x && v0.x <= 1);
    assert(-1 <= v1.x && v1.x <= 1);
    assert(-1 <= v2.x && v2.x <= 1);

    assert(-1 <= v0.y && v0.y <= 1);
    assert(-1 <= v1.y && v1.y <= 1);
    assert(-1 <= v2.y && v2.y <= 1);

    BitmapToScreenSpace(instance, &v0);
    BitmapToScreenSpace(instance, &v1);
    BitmapToScreenSpace(instance, &v2);

    BitmapDrawTriangleScreenspace(instance, v0, v1, v2, color);
}

void BitmapDrawLine(Bitmap* instance, Vector3 v0, Vector3 v1, Color color)
{
    if (ClipLineBack   (&v0, &v1)) return;

    BitmapApplyPerspective(&v0);
    BitmapApplyPerspective(&v1);

    if (ClipLineLeft   (&v0, &v1)) return;
    if (ClipLineRight  (&v0, &v1)) return;
    if (ClipLineDown   (&v0, &v1)) return;
    if (ClipLineUp     (&v0, &v1)) return;

    BitmapToScreenSpace(instance, &v0);
    BitmapToScreenSpace(instance, &v1);

    BitmapDrawLineScreenSpace(instance, v0, v1, color);
}
void BitmapDrawTriangle(Bitmap* instance, Vector3 p0, Vector3 p1, Vector3 p2, Color color)
{
    float near = 1.0f;
    float far = 100;

    Matrix mat = MatrixPerspectiveCube(1, 1, near, far);

    int vertexCount = 3;

    Vector3 v0[6];
    Vector3 v1[6];

    v0[0] = { p0.x, p0.y, p0.z };
    v0[1] = { p1.x, p1.y, p1.z };
    v0[2] = { p2.x, p2.y, p2.z };

    ClipPoligonBack   (v0, v1, &vertexCount, 0.1f); if (vertexCount < 3) return; swap(v0, v1);

    for (int i = 0; i < vertexCount; i++)
    {
        Vector4 _v = { v0[i].x, v0[i].y, v0[i].z, 1 };
        _v *= mat;
        if (_v.w == 0) continue;
        _v.x /= _v.w;
        _v.y /= _v.w;
        _v.z /= _v.w;
        v0[i] = { _v.x, _v.y, _v.z };
    }

    // if (!Vector3TriangleIsClockwise(v0[0], v0[1], v0[2])) return;

    ClipPoligonLeft   (v0, v1, &vertexCount, -1.0f); if (vertexCount < 3) return; swap(v0, v1);
    ClipPoligonRight  (v0, v1, &vertexCount, +1.0f); if (vertexCount < 3) return; swap(v0, v1);
    ClipPoligonDown   (v0, v1, &vertexCount, -1.0f); if (vertexCount < 3) return; swap(v0, v1);
    ClipPoligonUp     (v0, v1, &vertexCount, +1.0f); if (vertexCount < 3) return; swap(v0, v1);

    for (int i = 0; i < vertexCount; i++)
        v0[i].z += 1.0f;

    for (int i = 1; i < vertexCount - 1; i++)
        BitmapDrawTriangleNdc(instance, v0[0], v0[i], v0[i+1], color);
}
void BitmapDrawPoligon(Bitmap* instance, Vector3 p0, Vector3 p1, Vector3 p2, Vector3 p3, Color color)
{
    BitmapDrawTriangle(instance, p0, p1, p2, color);
    BitmapDrawTriangle(instance, p2, p3, p0, color);
}
void BitmapDrawCube(Bitmap* instance, Matrix mvp, Color color)
{
    #define DRAW(INDEX, COLOR)                                \
    {                                                         \
        int i0 = ModelCubeIndecesQuad[INDEX][0];              \
        int i1 = ModelCubeIndecesQuad[INDEX][1];              \
        int i2 = ModelCubeIndecesQuad[INDEX][2];              \
        int i3 = ModelCubeIndecesQuad[INDEX][3];              \
        Vector3 p0 = ModelCubeVerteces[i0];                   \
        Vector3 p1 = ModelCubeVerteces[i1];                   \
        Vector3 p2 = ModelCubeVerteces[i2];                   \
        Vector3 p3 = ModelCubeVerteces[i3];                   \
        p0 *= mvp;                                            \
        p1 *= mvp;                                            \
        p2 *= mvp;                                            \
        p3 *= mvp;                                            \
        BitmapDrawPoligon(instance, p0, p1, p2, p3, COLOR);   \
    }                                                         \

    DRAW(0, color)
    DRAW(1, color)
    DRAW(2, color)
    DRAW(3, color)
    DRAW(4, color)
    DRAW(5, color)

    #undef DRAW
}
void BitmapDrawSphere(Bitmap* instance, Matrix mvp, Color color)
{
    abort();
}
void BitmapDrawCubeWireframe(Bitmap* instance, Matrix mvp, Color color)
{
    for (int i = 0; i < 12; i++)
    {
        int i0 = ModelCubeIndecesLine[i][0];
        int i1 = ModelCubeIndecesLine[i][1];
        Vector3 v0 = ModelCubeVerteces[i0];
        Vector3 v1 = ModelCubeVerteces[i1];
        v0 *= mvp;
        v1 *= mvp;
        BitmapDrawLine(instance, v0, v1, color);
    }
}
void BitmapDrawCubeTemp(Bitmap* instance, Vector3 position, Vector3 rotation, Camera camera, Color color)
{
    Vector3 scale = { 1, 1, 1 };
    Matrix world = MatrixWorld2(position, rotation, scale);
    Matrix view = MatrixView3(&camera);
    BitmapDrawCube(instance, world * view, color);
}
void BitmapDrawCubeColored(Bitmap* instance, Matrix modelView)
{
    #define DRAW(INDEX, COLOR)                               \
    {                                                        \
        int i0 = ModelCubeIndecesQuad[INDEX][0];             \
        int i1 = ModelCubeIndecesQuad[INDEX][1];             \
        int i2 = ModelCubeIndecesQuad[INDEX][2];             \
        int i3 = ModelCubeIndecesQuad[INDEX][3];             \
        Vector3 p0 = ModelCubeVerteces[i0];                  \
        Vector3 p1 = ModelCubeVerteces[i1];                  \
        Vector3 p2 = ModelCubeVerteces[i2];                  \
        Vector3 p3 = ModelCubeVerteces[i3];                  \
        p0 *= modelView;                                     \
        p1 *= modelView;                                     \
        p2 *= modelView;                                     \
        p3 *= modelView;                                     \
        BitmapDrawPoligon(instance, p0, p1, p2, p3, COLOR);  \
    }                                                        \

    DRAW(0, COLOR_CYAN)
    DRAW(1, COLOR_GREEN)
    DRAW(2, COLOR_BLUE)
    DRAW(3, COLOR_YELLOW)
    DRAW(4, COLOR_MAGENTA)
    DRAW(5, COLOR_RED)

    #undef DRAW
}
