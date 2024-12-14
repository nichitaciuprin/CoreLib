#pragma once

#include "stdlib.h"
#include "stdint.h"
#include "float.h"
#include "assert.h"
#include "string.h"

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
    Matrix view;
    Matrix proj;
    float near;
    Vector3 verteces[300];
    int vertecesCount = 0;
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

    instance.view = MatrixIdentity();
    instance.proj = MatrixIdentity();

    instance.near = 0;

    return instance;
}
void BitmapDestroy(Bitmap* instance)
{
    free(instance->pixels);
    free(instance->zbuffer);
}
void BitmapResize(Bitmap* instance, int width, int height)
{
    int size = width * height;
    int sizeOld = instance->width * instance->height;

    if (size > sizeOld)
    {
        free(instance->pixels);
        free(instance->zbuffer);
        instance->pixels = (uint32_t*)malloc(sizeof(uint32_t) * size);
        instance->zbuffer = (float*)malloc(sizeof(float) * size);
    }

    instance->width = width;
    instance->height = height;

    instance->maxX = width - 1;
    instance->maxY = height - 1;

    instance->pixelsSize = size;
    instance->zbufferSize = size;
}

void BitmapTrianglesAdd(Bitmap* instance, Vector3 p0, Vector3 p1, Vector3 p2)
{
    int vertecesCount = instance->vertecesCount;
    int traingleCount = vertecesCount / 3;

    if (traingleCount == 300) return;

    Vector3* verteces = instance->verteces;

    verteces[vertecesCount] = p0; vertecesCount++;
    verteces[vertecesCount] = p1; vertecesCount++;
    verteces[vertecesCount] = p2; vertecesCount++;

    instance->vertecesCount = vertecesCount;
}
void BitmapTrianglesClear(Bitmap* instance)
{
    instance->vertecesCount = 0;
}

void BitmapReset(Bitmap* instance)
{
    BitmapTrianglesClear(instance);

    int pixelCount = instance->pixelsSize;

    memset((void*)instance->pixels, 0, pixelCount * sizeof(uint32_t));

    // can we, somehow, do memset here?
    for (int i = 0; i < pixelCount; i++)
        instance->zbuffer[i] = FLT_MAX;
}
void BitmapSetView(Bitmap* instance, Camera* camera)
{
    instance->view = MatrixView3(camera);
}
void BitmapSetPerspective(Bitmap* instance, float width, float height, float near, float far)
{
    assert(width > 0);
    assert(height > 0);
    assert(0 < near && near < far);

    instance->near = near;
    instance->proj = MatrixPerspectiveCube(width, height, near, far);
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
void BitmapSetPixelZScaled(Bitmap* instance, int x, int y, float z, Color color, int scale)
{
    int minx = MathClampInt(x - scale, 0, instance->maxX);
    int maxx = MathClampInt(x + scale, 0, instance->maxX);
    int miny = MathClampInt(y - scale, 0, instance->maxY);
    int maxy = MathClampInt(y + scale, 0, instance->maxY);

    int i = x + y * instance->width;

    if (instance->zbuffer[i] < z) return;

    for (; minx <= maxx; minx++)
    for (; miny <= maxy; miny++)
    {
        int i2 = minx + miny * instance->width;
        instance->zbuffer[i2] = z;
        instance->pixels[i2] = color;
    }
}

void BitmapSetLineZ(Bitmap* instance, int y, int xl, int xr, float zl, float zr, Color color)
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
void BitmapFromScreenSpace(Bitmap* instance, Vector3* v)
{
    v->x /= instance->maxX;
    v->y /= instance->maxY;
    v->x *= 2.0f;
    v->y *= 2.0f;
    v->x -= 1.0f;
    v->y -= 1.0f;
    v->y = -v->y;
}

void BitmapApplyFade(Bitmap* instance)
{
    int pixelCount = instance->pixelsSize;

    float min = 1.0f;
    float max = min + 1.1;

    for (int i = 0; i < pixelCount; i++)
    {
        float z = MathClampFloat(instance->zbuffer[i], min, max);
        float t = 1 - MathInverseLerp(min, max, z);

        uint8_t byte = 255 * t;

        uint32_t color = 0;
        color += byte; color <<= 8;
        color += byte; color <<= 8;
        color += byte; color <<= 8;
        color += byte;

        instance->pixels[i] = color;
    }
}
void BitmapApplyLight(Bitmap* instance, Vector3 lightPosition)
{
    int width = instance->width;
    int height = instance->height;

    Matrix view = instance->view;
    Matrix proj = instance->proj;

    Matrix viewi = MatrixInvert(view);
    Matrix proji = MatrixInvert(proj);

    for (int y = 0; y < height; y++)
    for (int x = 0; x < width; x++)
    {
        int i = x + y * width;
        float z = instance->zbuffer[i];

        if (z == FLT_MAX) continue;

        z -= 1.0f;
        Vector3 p = { (float)x, (float)y, z };
        BitmapFromScreenSpace(instance, &p);

        p = NdcToWorld(p, viewi, proji);

        float t = CalcLight(p, lightPosition);

        instance->pixels[i] = ColorSetLightValueF(instance->pixels[i], t);
    }
}
void BitmapApplyLightAndShadows(Bitmap* instance, Vector3 lightPosition)
{
    int width = instance->width;
    int height = instance->height;

    Matrix view = instance->view;
    Matrix proj = instance->proj;

    Matrix viewi = MatrixInvert(view);
    Matrix proji = MatrixInvert(proj);

    for (int y = 0; y < height; y++)
    for (int x = 0; x < width; x++)
    {
        int i = x + y * width;
        float z = instance->zbuffer[i];

        if (z == FLT_MAX) continue;

        z -= 1.0f;
        Vector3 p = { (float)x, (float)y, z };
        BitmapFromScreenSpace(instance, &p);

        p = NdcToWorld(p, viewi, proji);

        float t = CalcLightAndShadow(p, lightPosition, instance->verteces, instance->vertecesCount);

        instance->pixels[i] = ColorSetLightValueF(instance->pixels[i], t);
    }
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

    float z = v0.z;
    float offset = (v1.z - v0.z) / max;

    for (int i = 0; i < max; i++)
    {
        BitmapSetPixelZ(instance, x0, y0, z, color);

        // TODO optimise
        // {
        //     int size = 2;
        //     for (int duno1 = -size; duno1 < size; duno1++)
        //     for (int duno2 = -size; duno2 < size; duno2++)
        //     {
        //         int _x0 = MathClampInt(x0+duno1, 0, instance->maxX);
        //         int _y0 = MathClampInt(y0+duno2, 0, instance->maxY);
        //         BitmapSetPixelZ(instance, _x0, _y0, z, color);
        //     }
        // }

        if (err < 0) { err += max; (*axis1) += val1; }
                     { err -= min; (*axis2) += val2; }

        z += offset;
    }

    BitmapSetPixelZ(instance, x0, y0, z, color);
}
void BitmapDrawLineScreenSpaceV3(Bitmap* instance, Vector3 v0, Vector3 v1, Color color)
{
    int x0 = (int)v0.x;
    int y0 = (int)v0.y;
    float z0 = v0.z;

    int x1 = (int)v1.x;
    int y1 = (int)v1.y;
    float z1 = v1.z;

    int dx, sx;
    int dy, sy;

    if (x0 < x1) { dx = x1 - x0; sx =  1; }
    else         { dx = x0 - x1; sx = -1; }

    if (y0 < y1) { dy = y1 - y0; sy =  1; }
    else         { dy = y0 - y1; sy = -1; }

    // TODO maybe refactor branching
    if (dx > dy)
    {
        float offset = (z1 - z0) / dx;

        int err = dx - dx / 2;

        for (int i = 0; i < dx; i++)
        {
            // float t = (float)i / dx;
            // float zt = MathLerp(z0, z1, t);

            BitmapSetPixelZ(instance, x0, y0, z0, color);
            // BitmapSetPixelZ(instance, x0, y0, zt, color);

                          { err -= dy; x0 += sx; }
            if (err <= 0) { err += dx; y0 += sy; }

            z0 += offset;
        }

        BitmapSetPixelZ(instance, x0, y0, z1, color);
    }
    else
    {
        float offset = (z1 - z0) / dy;

        int err = dy - dy / 2;

        for (int i = 0; i < dy; i++)
        {
            // float t = (float)i / dy;
            // float zt = MathLerp(z0, z1, t);

            BitmapSetPixelZ(instance, x0, y0, z0, color);
            // BitmapSetPixelZ(instance, x0, y0, zt, color);

                          { err -= dx; y0 += sy; }
            if (err <= 0) { err += dy; x0 += sx; }

            z0 += offset;
        }

        BitmapSetPixelZ(instance, x0, y0, z1, color);
    }
}
void BitmapDrawLineScreenSpace(Bitmap* instance, Vector3 v0, Vector3 v1, Color color)
{
    // BitmapDrawLineScreenSpaceV1(instance, v0, v1, color);
    // BitmapDrawLineScreenSpaceV2(instance, v0, v1, color);
    BitmapDrawLineScreenSpaceV3(instance, v0, v1, color);
}
void BitmapDrawLineNdc(Bitmap* instance, Vector3 v0, Vector3 v1, Color color)
{
    // vertex must be in this range
    // -1 <= x <= 1
    // -1 <= y <= 1
    //  0 <= z <= inf

    assert(-1 <= v0.x && v0.x <= 1);
    assert(-1 <= v1.x && v1.x <= 1);

    assert(-1 <= v0.y && v0.y <= 1);
    assert(-1 <= v1.y && v1.y <= 1);

    BitmapToScreenSpace(instance, &v0);
    BitmapToScreenSpace(instance, &v1);

    BitmapDrawLineScreenSpace(instance, v0, v1, color);
}

void BitmapDrawTriangleWireframeScreenspaceV1(Bitmap* instance, Vector3 v0, Vector3 v1, Vector3 v2, Color color)
{
    // v0 is top
    // v1 is middle
    // v2 is bottom

    if (v0.y > v1.y) SwapVector3(&v0, &v1);
    if (v1.y > v2.y) SwapVector3(&v1, &v2);
    if (v0.y > v1.y) SwapVector3(&v0, &v1);

    BitmapDrawLineScreenSpaceV3(instance, v0, v1, color);
    BitmapDrawLineScreenSpaceV3(instance, v0, v2, color);
    BitmapDrawLineScreenSpaceV3(instance, v1, v2, color);
}

bool BitmapDrawLineStep(int* x0, int* y0, int* x1, int* y1, int* err, int dx, int dy, int sx, int sy, int* x)
{
    while (true)
    {
        if (*x0 == *x1 && *y0 == *y1) { *x = *x0; return true; }
        int e2 = 2 * (*err); *x = *x0;
        if (e2 >= dy) { *err += dy; *x0 += sx; }
        if (e2 <= dx) { *err += dx; *y0 += sy; return false; }
    }
}
void BitmapDrawTriangleWireframeScreenspaceV2(Bitmap* instance, Vector3 v0, Vector3 v1, Vector3 v2, Color color)
{
    // TODO Finish

    // v0 is top
    // v1 is middle
    // v2 is bottom

    if (v0.y > v1.y) SwapVector3(&v0, &v1);
    if (v1.y > v2.y) SwapVector3(&v1, &v2);
    if (v0.y > v1.y) SwapVector3(&v0, &v1);

    int x0 = (int)v0.x;
    int y0 = (int)v0.y;
    int x1 = (int)v2.x;
    int y1 = (int)v2.y;

    int _x0 = (int)v0.x;
    int _y0 = (int)v0.y;
    int _x1 = (int)v1.x;
    int _y1 = (int)v1.y;

    int __x0 = (int)v1.x;
    int __y0 = (int)v1.y;
    int __x1 = (int)v2.x;
    int __y1 = (int)v2.y;

    int dy2 = v1.y - v0.y;
    int dy3 = v2.y - v1.y;

    int x;
    int dx =  abs(x1 - x0);
    int dy = -abs(y1 - y0);
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;
    int err = dx + dy;

    int _x;
    int _dx =  abs(_x1 - _x0);
    int _dy = -abs(_y1 - _y0);
    int _sx = _x0 < _x1 ? 1 : -1;
    int _sy = _y0 < _y1 ? 1 : -1;
    int _err = _dx + _dy;

    int __x;
    int __dx =  abs(__x1 - __x0);
    int __dy = -abs(__y1 - __y0);
    int __sx = __x0 < __x1 ? 1 : -1;
    int __sy = __y0 < __y1 ? 1 : -1;
    int __err = __dx + __dy;

    int y = v0.y;

    for (int i = 0; i < dy2; i++)
    {
        BitmapDrawLineStep( &x0,  &y0,  &x1,  &y1,  &err,  dx,  dy,  sx,  sy,  &x);
        BitmapDrawLineStep(&_x0, &_y0, &_x1, &_y1, &_err, _dx, _dy, _sx, _sy, &_x);
        // BitmapSetPixel(instance,  x,  y, color);
        // BitmapSetPixel(instance, _x, _y, color);
        if (x > _x) SwapInt(&x, &_x);
        BitmapSetLineZ(instance, y, x, _x, 0, 0, color);
        y++;
    }
    for (int i = 0; i < dy3; i++)
    {
        BitmapDrawLineStep(  &x0,   &y0,   &x1,   &y1,   &err,   dx,   dy,   sx,   sy,   &x);
        BitmapDrawLineStep(&__x0, &__y0, &__x1, &__y1, &__err, __dx, __dy, __sx, __sy, &__x);
        // BitmapSetPixel(instance,  x,  y, color);
        // BitmapSetPixel(instance, __x, __y, color);
        if (x > __x) SwapInt(&x, &_x);
        BitmapSetLineZ(instance, y, x, __x, 0, 0, color);
        y++;
    }
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
        if (!TriangleIsInside(v0, v1, v2, v)) continue;
        float z = Barycentric(v0, v1, v2, x, y);
        BitmapSetPixelZ(instance, x, y, z, color);
    }
}
void BitmapDrawTriangleScreenspaceV2(Bitmap* instance, Vector3 v0, Vector3 v1, Vector3 v2, Color color)
{
    // TODO not accurate, improve

    // v0 is top
    // v1 is middle
    // v2 is bottom

    if (v0.y > v1.y) SwapVector3(&v0, &v1);
    if (v1.y > v2.y) SwapVector3(&v1, &v2);
    if (v0.y > v1.y) SwapVector3(&v0, &v1);

    int x0 = (int)v0.x;
    int x1 = (int)v1.x;
    int x2 = (int)v2.x;

    int y0 = (int)v0.y;
    int y1 = (int)v1.y;
    int y2 = (int)v2.y;

    float z0 = v0.z;
    float z1 = v1.z;
    float z2 = v2.z;

    int dx1 = x2 - x0;
    int dx2 = x1 - x0;
    int dx3 = x2 - x1;

    int dy1 = y2 - y0;
    int dy2 = y1 - y0;
    int dy3 = y2 - y1;

    int dir1 = MathSignInt(dx1);
    int dir2 = MathSignInt(dx2);
    int dir3 = MathSignInt(dx3);

    int dx1abs = MathAbsInt(dx1);
    int dx2abs = MathAbsInt(dx2);
    int dx3abs = MathAbsInt(dx3);

    int err1 = dy1 - dx1abs;
    int err2 = dy2 - dx2abs;
    int err3 = dy3 - dx3abs;

    // TODO check for 0 division?
    float offset1 = (z2 - z0) / dy1;
    float offset2 = (z1 - z0) / dy2;
    float offset3 = (z2 - z1) / dy3;

    if (dy2 > 0) { x1 = x0; z1 = z0; }
    else         { x1 = x1; z1 = z1; }

    int cross = dx1 * dy2 - dy1 * dx2;

    int* xl; int* xr; float* zl; float* zr;
    if (cross < 0) { xl = &x0; xr = &x1; zl = &z0; zr = &z1; }
    else           { xl = &x1; xr = &x0; zl = &z1; zr = &z0; }

    for (int i = 0; i < dy2; i++)
    {
        while (err1 < 0) { err1 += dy1; x0 += dir1; }
        while (err2 < 0) { err2 += dy2; x1 += dir2; }
        BitmapSetLineZ(instance, y0, *xl, *xr, *zl, *zr, color);
        y0++;
        err1 -= dx1abs;
        err2 -= dx2abs;
        z0 += offset1;
        z1 += offset2;
    }
    for (int i = 0; i < dy3; i++)
    {
        while (err1 < 0) { err1 += dy1; x0 += dir1; }
        while (err3 < 0) { err3 += dy3; x1 += dir3; }
        BitmapSetLineZ(instance, y0, *xl, *xr, *zl, *zr, color);
        y0++;
        err1 -= dx1abs;
        err3 -= dx3abs;
        z0 += offset1;
        z1 += offset3;
    }
    BitmapSetLineZ(instance, y0, *xl, *xr, *zl, *zr, color);
}
void BitmapDrawTriangleScreenspace(Bitmap* instance, Vector3 v0, Vector3 v1, Vector3 v2, Color color)
{
    // BitmapDrawTriangleScreenspaceV1(instance, v0, v1, v2, color);
    BitmapDrawTriangleScreenspaceV2(instance, v0, v1, v2, color);
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

void BitmapDrawLineWire(Bitmap* instance, Vector3 p0, Vector3 p1, Color color)
{
    Matrix view = instance->view;
    Matrix proj = instance->proj;

    p0 = MatrixMultiply3L(p0, view);
    p1 = MatrixMultiply3L(p1, view);

    Vector4 _v0 = { p0.x, p0.y, p0.z, 1 };
    Vector4 _v1 = { p1.x, p1.y, p1.z, 1 };

    _v0 = MatrixMultiply4L(_v0, proj);
    _v1 = MatrixMultiply4L(_v1, proj);

    if (ClipLineWClipSpace      (&_v0, &_v1)) return;
    if (ClipLineBackClipSpace   (&_v0, &_v1)) return;
    if (ClipLineFrontClipSpace  (&_v0, &_v1)) return;
    if (ClipLineLeftClipSpace   (&_v0, &_v1)) return;
    if (ClipLineRightClipSpace  (&_v0, &_v1)) return;
    if (ClipLineDownClipSpace   (&_v0, &_v1)) return;
    if (ClipLineUpClipSpace     (&_v0, &_v1)) return;

    _v0.x /= _v0.w;
    _v0.y /= _v0.w;
    _v0.z /= _v0.w;
    _v1.x /= _v1.w;
    _v1.y /= _v1.w;
    _v1.z /= _v1.w;

    // removing clip errors
    _v0.x = MathClampFloat(_v0.x, -1, +1);
    _v0.y = MathClampFloat(_v0.y, -1, +1);
    _v0.z = MathClampFloat(_v0.z, -1, +1);
    _v1.x = MathClampFloat(_v1.x, -1, +1);
    _v1.y = MathClampFloat(_v1.y, -1, +1);
    _v1.z = MathClampFloat(_v1.z, -1, +1);

    _v0.z += 1.0f;
    _v1.z += 1.0f;

    p0.x = _v0.x;
    p0.y = _v0.y;
    p0.z = _v0.z;
    p1.x = _v1.x;
    p1.y = _v1.y;
    p1.z = _v1.z;

    BitmapDrawLineNdc(instance, p0, p1, color);
}
void BitmapDrawTriangleWire(Bitmap* instance, Vector3 p0, Vector3 p1, Vector3 p2, Color color)
{
    abort();
}
void BitmapDrawPoligonWire(Bitmap* instance, Vector3 p0, Vector3 p1, Vector3 p2, Vector3 p3, Color color)
{
    abort();
}
void BitmapDrawCubeWire(Bitmap* instance, Vector3 position, Vector3 rotation, Vector3 scale, Color color)
{
    Matrix model = MatrixWorld2(position, rotation, scale);

    for (int i = 0; i < 12; i++)
    {
        int i0 = ModelCubeIndecesLine[i][0];
        int i1 = ModelCubeIndecesLine[i][1];
        Vector3 v0 = ModelCubeVerteces[i0];
        Vector3 v1 = ModelCubeVerteces[i1];
        v0 = MatrixMultiply3L(v0, model);
        v1 = MatrixMultiply3L(v1, model);
        BitmapDrawLineWire(instance, v0, v1, color);
    }
}
void BitmapDrawSphereWire(Bitmap* instance, Vector3 position, Vector3 rotation, Vector3 scale, Color color)
{
    abort();
}

void BitmapDrawTriangle(Bitmap* instance, Vector3 p0, Vector3 p1, Vector3 p2, Color color)
{
    BitmapTrianglesAdd(instance, p0, p1, p2);

    Matrix view = instance->view;
    Matrix proj = instance->proj;

    p0 = MatrixMultiply3L(p0, view);
    p1 = MatrixMultiply3L(p1, view);
    p2 = MatrixMultiply3L(p2, view);

    int vertexCount = 3;

    Vector4 v0[6];
    Vector4 v1[6];

    v0[0] = (Vector4){ p0.x, p0.y, p0.z, 1 };
    v0[1] = (Vector4){ p1.x, p1.y, p1.z, 1 };
    v0[2] = (Vector4){ p2.x, p2.y, p2.z, 1 };

    v0[0] = MatrixMultiply4L(v0[0], proj);
    v0[1] = MatrixMultiply4L(v0[1], proj);
    v0[2] = MatrixMultiply4L(v0[2], proj);

    ClipPoligonWClipSpace      (v0, v1, &vertexCount); if (vertexCount < 3) return;
    ClipPoligonBackClipSpace   (v1, v0, &vertexCount); if (vertexCount < 3) return;
    ClipPoligonFrontClipSpace  (v0, v1, &vertexCount); if (vertexCount < 3) return;
    ClipPoligonLeftClipSpace   (v1, v0, &vertexCount); if (vertexCount < 3) return;
    ClipPoligonRightClipSpace  (v0, v1, &vertexCount); if (vertexCount < 3) return;
    ClipPoligonDownClipSpace   (v1, v0, &vertexCount); if (vertexCount < 3) return;
    ClipPoligonUpClipSpace     (v0, v1, &vertexCount); if (vertexCount < 3) return;

    for (int i = 0; i < vertexCount; i++)
    {
        v1[i].x /= v1[i].w;
        v1[i].y /= v1[i].w;
        v1[i].z /= v1[i].w;
    }

    // if (!TriangleIsClockwise(v1[0], v1[1], v1[2])) return;

    for (int i = 0; i < vertexCount; i++)
    {
        v1[i].x = MathClampFloat(v1[i].x, -1, +1);
        v1[i].y = MathClampFloat(v1[i].y, -1, +1);
        v1[i].z = MathClampFloat(v1[i].z, -1, +1);
    }

    for (int i = 0; i < vertexCount; i++)
        v1[i].z += 1.0f;

    for (int i = 1; i < vertexCount - 1; i++)
    {
        Vector4 _p0 = v1[0];
        Vector4 _p1 = v1[i];
        Vector4 _p2 = v1[i+1];

        p0 = (Vector3){ _p0.x, _p0.y, _p0.z };
        p1 = (Vector3){ _p1.x, _p1.y, _p1.z };
        p2 = (Vector3){ _p2.x, _p2.y, _p2.z };

        BitmapDrawTriangleNdc(instance, p0, p1, p2, color);
    }
}
void BitmapDrawPoligon(Bitmap* instance, Vector3 p0, Vector3 p1, Vector3 p2, Vector3 p3, Color color)
{
    BitmapDrawTriangle(instance, p0, p1, p2, color);
    BitmapDrawTriangle(instance, p2, p3, p0, color);
}
void BitmapDrawCube(Bitmap* instance, Vector3 position, Vector3 rotation, Vector3 scale, Color color)
{
    Matrix model = MatrixWorld2(position, rotation, scale);

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
        p0 = MatrixMultiply3L(p0, model);                     \
        p1 = MatrixMultiply3L(p1, model);                     \
        p2 = MatrixMultiply3L(p2, model);                     \
        p3 = MatrixMultiply3L(p3, model);                     \
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
void BitmapDrawSphere(Bitmap* instance, Vector3 position, Vector3 rotation, Vector3 scale, Color color)
{
    abort();
}

void BitmapDrawCubeColored(Bitmap* instance, Vector3 position, Vector3 rotation, Vector3 scale)
{
    Matrix model = MatrixWorld2(position, rotation, scale);

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
        p0 = MatrixMultiply3L(p0, model);                    \
        p1 = MatrixMultiply3L(p1, model);                    \
        p2 = MatrixMultiply3L(p2, model);                    \
        p3 = MatrixMultiply3L(p3, model);                    \
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
