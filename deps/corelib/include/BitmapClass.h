#pragma once

#include "Bitmap.h"

class BitmapClass
{
public:
    uint32_t* pixels;

    BitmapClass(int width, int height) { bitmap = BitmapCreate(width, height); pixels = bitmap.pixels; }
    ~BitmapClass() { BitmapDestroy(&bitmap);}

    int Width() const { return bitmap.width; }
    int Height() const { return bitmap.height; }

    void DrawCubeColored(Vector3 position, Vector3 rotation, Vector3 scale)                { BitmapDrawCubeColored(&bitmap, position, rotation, scale); }
    void DrawCube(Vector3 position, Vector3 rotation, Vector3 scale, Color color)          { BitmapDrawCube(&bitmap, position, rotation, scale, color); }
    void DrawCubeWireframe(Vector3 position, Vector3 rotation, Vector3 scale, Color color) { BitmapDrawCubeWire(&bitmap, position, rotation, scale, color); }
    void DrawPoligon(Vector3 p0, Vector3 p1, Vector3 p2, Vector3 p3, Color color)          { BitmapDrawPoligon(&bitmap, p0, p1, p2, p3, color); }
    void DrawTriangle(Vector3 p0, Vector3 p1, Vector3 p2, Color color)                     { BitmapDrawTriangle(&bitmap, p0, p1, p2, color); }
    void DrawTriangleNdc(Vector3 p0, Vector3 p1, Vector3 p2, Color color)                  { BitmapDrawTriangleNdc(&bitmap, p0, p1, p2, color); }
    void DrawTriangleScreenspace(Vector3 v0, Vector3 v1, Vector3 v2, Color color)          { BitmapDrawTriangleScreenspace(&bitmap, v0, v1, v2, color); }
    void DrawLine(Vector3 v0, Vector3 v1, Color color)                                     { BitmapDrawLineWire(&bitmap, v0, v1, color); }
    void DrawLineNdc(Vector3 v0, Vector3 v1, Color color)                                  { BitmapDrawLineNdc(&bitmap, v0, v1, color); }
    void DrawLineScreenSpace(Vector3 v0, Vector3 v1, Color color)                          { BitmapDrawLineScreenSpace(&bitmap, v0, v1, color); }
    void ApplyFade()                                                                       { BitmapApplyFade(&bitmap); }
    void ToScreenSpace(Vector3* v)                                                         { BitmapToScreenSpace(&bitmap, v); }
    void FillBorder(Color color)                                                           { BitmapFillBorder(&bitmap, color); }
    void FillCross(Color color)                                                            { BitmapFillCross(&bitmap, color); }
    void FillAll(Color color)                                                              { BitmapFillAll(&bitmap, color); }
    void SetLineZ(int y, int xl, int xr, float zl, float zr, Color color)                  { BitmapSetLineZ(&bitmap, y, xl, xr, zl, zr, color); }
    void SetPixel(int x, int y, Color color)                                               { BitmapSetPixel(&bitmap, x, y, color); }
    void SetPixelZ(int x, int y, float z, Color color)                                     { BitmapSetPixelZ(&bitmap, x, y, z, color); }
    void Reset()                                                                           { BitmapReset(&bitmap); }

private:
    Bitmap bitmap;
};
