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

    void DrawCubeTemp(Vector3 position, Vector3 rotation, Camera camera, Color color)  { BitmapDrawCubeTemp(&bitmap, position, rotation, camera, color); }
    void DrawCubeColored(Matrix modelView)                                             { BitmapDrawCubeColored(&bitmap, modelView); }
    void DrawCube1(Matrix modelView, Color color)                                      { BitmapDrawCube1(&bitmap, modelView, color); }
    void DrawCubeWireframe(Matrix modelView, Color color)                              { BitmapDrawCubeWireframe(&bitmap, modelView, color); }
    void DrawPoligon1(Vector3 p0, Vector3 p1, Vector3 p2, Vector3 p3, Color color)     { BitmapDrawPoligon1(&bitmap, p0, p1, p2, p3, color); }
    void DrawTriangle1(Vector3 p0, Vector3 p1, Vector3 p2, Color color)                { BitmapDrawTriangle1(&bitmap, p0, p1, p2, color); }
    void DrawTriangle2(Vector3 p0, Vector3 p1, Vector3 p2, Color color)                { BitmapDrawTriangle2(&bitmap, p0, p1, p2, color); }
    void DrawTriangle3(Vector3 v0, Vector3 v1, Vector3 v2, Color color)                { BitmapDrawTriangle3(&bitmap, v0, v1, v2, color); }
    void DrawLine1(Vector3 v0, Vector3 v1, Color color)                                { BitmapDrawLine1(&bitmap, v0, v1, color); }
    void DrawLine2(Vector3 v0, Vector3 v1, Color color)                                { BitmapDrawLine2(&bitmap, v0, v1, color); }
    void DrawLine3(Vector3 v0, Vector3 v1, Color color)                                { BitmapDrawLine3(&bitmap, v0, v1, color); }
    void ApplyBlackWhiteColorDepth()                                                   { BitmapApplyBlackWhiteColorDepth(&bitmap); }
    void ApplyPerspective(Vector3* v)                                                  { BitmapApplyPerspective(v); }
    void ToScreenSpace(Vector3* v)                                                     { BitmapToScreenSpace(&bitmap, v); }
    void FillBorder(Color color)                                                       { BitmapFillBorder(&bitmap, color); }
    void FillCross(Color color)                                                        { BitmapFillCross(&bitmap, color); }
    void FillAll(Color color)                                                          { BitmapFillAll(&bitmap, color); }
    void DrawLineHorizontal(int y, int xl, int xr, float zl, float zr, Color color)    { BitmapDrawLineHorizontal(&bitmap, y, xl, xr, zl, zr, color); }
    void SetPixel(int x, int y, Color color)                                           { BitmapSetPixel(&bitmap, x, y, color); }
    void SetPixelZ(int x, int y, float z, Color color)                                 { BitmapSetPixelZ(&bitmap, x, y, z, color); }
    void Reset()                                                                       { BitmapReset(&bitmap); }

private:
    Bitmap bitmap;
};
