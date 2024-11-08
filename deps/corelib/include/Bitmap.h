// http://www.sunshine2k.de/coding/java/TriangleRasterization/TriangleRasterization.html
// https://developer.nvidia.com/gpugems/gpugems2/part-v-image-oriented-computing/chapter-42-conservative-rasterization

#pragma once

#include "Clipping.h"
#include "Models.h"
#include "Color.h"
#include "float.h"
#include "assert.h"

class Bitmap
{
public:
    uint32_t* pixels;
    vector<float> zbuffer;

    Bitmap(int width, int height)
    {
        assert(width > 0);
        assert(height > 0);

        this->width = width;
        this->height = height;

        maxX = width - 1;
        maxY = height - 1;

        pixelsSize = width * height;

        // TODO free
        pixels = (uint32_t*)malloc(sizeof(uint32_t) * pixelsSize);
        zbuffer = vector<float>(pixelsSize, FLT_MAX);
    }

    int Width() const
    {
        return width;
    }
    int Height() const
    {
        return height;
    }

    void DrawCube(Vector3 position, Vector3 rotation, Camera camera, Color color)
    {
        Vector3 scale = { 1, 1, 1 };
        auto world = MatrixWorld2(position, rotation, scale);
        auto view = MatrixView3(&camera);
        DrawCube(world * view, color);
    }

    void DrawCubeWireframe(Matrix modelView, Color color)
    {
        for (size_t i = 0; i < 12; i++)
        {
            auto i0 = ModelCubeIndecesLine[i][0];
            auto i1 = ModelCubeIndecesLine[i][1];
            auto v0 = ModelCubeVerteces[i0] * modelView;
            auto v1 = ModelCubeVerteces[i1] * modelView;
            DrawLine1(v0, v1, color);
        }
    }
    void DrawCubeColored(Matrix modelView)
    {
        #define DRAW(INDEX, COLOR)                        \
        {                                                 \
            auto i0 = ModelCubeIndecesQuad[INDEX][0];     \
            auto i1 = ModelCubeIndecesQuad[INDEX][1];     \
            auto i2 = ModelCubeIndecesQuad[INDEX][2];     \
            auto i3 = ModelCubeIndecesQuad[INDEX][3];     \
            auto p0 = ModelCubeVerteces[i0];              \
            auto p1 = ModelCubeVerteces[i1];              \
            auto p2 = ModelCubeVerteces[i2];              \
            auto p3 = ModelCubeVerteces[i3];              \
            p0 *= modelView;                              \
            p1 *= modelView;                              \
            p2 *= modelView;                              \
            p3 *= modelView;                              \
            DrawPoligon1(p0, p1, p2, p3, COLOR);          \
        }                                                 \

        DRAW(0, COLOR_CYAN)
        DRAW(1, COLOR_GREEN)
        DRAW(2, COLOR_BLUE)
        DRAW(3, COLOR_YELLOW)
        DRAW(4, COLOR_MAGENTA)
        DRAW(5, COLOR_RED)

        #undef DRAW
    }
    void DrawCube(Matrix modelView, Color color)
    {
        #define DRAW(INDEX, COLOR)                        \
        {                                                 \
            auto i0 = ModelCubeIndecesQuad[INDEX][0];     \
            auto i1 = ModelCubeIndecesQuad[INDEX][1];     \
            auto i2 = ModelCubeIndecesQuad[INDEX][2];     \
            auto i3 = ModelCubeIndecesQuad[INDEX][3];     \
            auto p0 = ModelCubeVerteces[i0];              \
            auto p1 = ModelCubeVerteces[i1];              \
            auto p2 = ModelCubeVerteces[i2];              \
            auto p3 = ModelCubeVerteces[i3];              \
            p0 *= modelView;                              \
            p1 *= modelView;                              \
            p2 *= modelView;                              \
            p3 *= modelView;                              \
            DrawPoligon1(p0, p1, p2, p3, COLOR);          \
        }                                                 \

        DRAW(0, color)
        DRAW(1, color)
        DRAW(2, color)
        DRAW(3, color)
        DRAW(4, color)
        DRAW(5, color)

        #undef DRAW
    }
    void DrawPoligon1(Vector3 p0, Vector3 p1, Vector3 p2, Vector3 p3, Color color)
    {
        auto v0 = vector<Vector3>();
        auto v1 = vector<Vector3>();

        v0.reserve(6);
        v1.reserve(6);

        v0.push_back(p0);
        v0.push_back(p1);
        v0.push_back(p2);
        v0.push_back(p3);

        ClipPoligonBack      (v0, v1); if (v1.size() < 3) return; v0.clear();

        for (auto& x : v1)
        {
            if (x.z == 0) continue;
            x.x /= x.z;
            x.y /= x.z;
        }

        if (!Vector3TriangleIsClockwise(v1[0], v1[1], v1[2])) return;

        ClipPoligonLeft      (v1, v0); if (v0.size() < 3) return; v1.clear();
        ClipPoligonRight     (v0, v1); if (v1.size() < 3) return; v0.clear();
        ClipPoligonTop       (v1, v0); if (v0.size() < 3) return; v1.clear();
        ClipPoligonBottom    (v0, v1); if (v1.size() < 3) return;

        for (auto& x : v1)
            ToScreenSpace(&x);

        for (size_t i = 1; i < v1.size() - 1; i++)
            DrawTriangle(v1[0], v1[i], v1[i + 1], color);
    }
    void DrawTriangle1(Vector3 p0, Vector3 p1, Vector3 p2, Color color)
    {
        auto v0 = vector<Vector3>();
        auto v1 = vector<Vector3>();

        v0.reserve(6);
        v1.reserve(6);

        v0.push_back(p0);
        v0.push_back(p1);
        v0.push_back(p2);

        ClipPoligonBack   (v0, v1); if (v1.size() < 3) return; v0.clear();

        for (auto& x : v1)
        {
            if (x.z == 0) continue;
            x.x /= x.z;
            x.y /= x.z;
        }

        if (!Vector3TriangleIsClockwise(v1[0], v1[1], v1[2])) return;

        ClipPoligonLeft   (v1, v0); if (v0.size() < 3) return; v1.clear();
        ClipPoligonRight  (v0, v1); if (v1.size() < 3) return; v0.clear();
        ClipPoligonTop    (v1, v0); if (v0.size() < 3) return; v1.clear();
        ClipPoligonBottom (v0, v1); if (v1.size() < 3) return;

        for (auto& x : v1)
            ToScreenSpace(&x);

        for (size_t i = 1; i < v1.size() - 1; i++)
            DrawTriangle(v1[0], v1[i], v1[i + 1], color);
    }
    void DrawTriangle2(Vector3 p0, Vector3 p1, Vector3 p2, Color color)
    {
        auto v0 = vector<Vector3>();
        auto v1 = vector<Vector3>();

        v0.reserve(6);
        v1.reserve(6);

        v0.push_back(p0);
        v0.push_back(p1);
        v0.push_back(p2);

        ClipPoligonBack(v0, v1); if (v1.size() < 3) return; v0.clear();

        if (!Vector3TriangleIsClockwise(v1[0], v1[1], v1[2])) return;

        for (auto& x : v1)
            ToScreenSpace(&x);

        for (size_t i = 1; i < v1.size() - 1; i++)
            DrawTriangle(v1[0], v1[i], v1[i + 1], color);
    }
    void DrawLine1(Vector3 v0, Vector3 v1, Color color)
    {
        if (ClipLineBack(v0, v1)) return;

        if (v0.z != 0) { v0.x /= v0.z; v0.y /= v0.z; };
        if (v1.z != 0) { v1.x /= v1.z; v1.y /= v1.z; };

        if (ClipLineLeft(v0, v1)) return;
        if (ClipLineRight(v0, v1)) return;
        if (ClipLineTop(v0, v1)) return;
        if (ClipLineBottom(v0, v1)) return;

        ToScreenSpace(&v0);
        ToScreenSpace(&v1);

        DrawLine(v0, v1, color);
    }
    void DrawLine2(Vector3 v0, Vector3 v1, Color color)
    {
        if (ClipLineLeft(v0, v1)) return;
        if (ClipLineRight(v0, v1)) return;
        if (ClipLineTop(v0, v1)) return;
        if (ClipLineBottom(v0, v1)) return;

        ToScreenSpace(&v0);
        ToScreenSpace(&v1);

        DrawLine(v0, v1, color);
    }
    void ToScreenSpace(Vector3* point)
    {
        point->y = -point->y;
        point->x += 1.0f;
        point->y += 1.0f;
        point->x /= 2;
        point->y /= 2;
        point->x = maxX * point->x;
        point->y = maxY * point->y;
    }

    void Fill(Color color)
    {
        // TODO move to BeginDraw()
        int size = width * height * sizeof(uint32_t);
        memset((void*)pixels, color, size);
        fill(zbuffer.begin(), zbuffer.end(), FLT_MAX);
    }
    void ApplyBlackWhiteColorDepth()
    {
        for (size_t i = 0; i < pixelsSize; i++)
        {
            float depthLength = 100;
            float factor = MathClampFloat(zbuffer[i], 0.0f, depthLength);
            factor /= depthLength;
            factor = 1 - factor;
            auto byte = (int)(factor * 255);

            uint32_t color = 0;
            color += byte; color = color << 8;
            color += byte; color = color << 8;
            color += byte; color = color << 8;
            color += byte;

            pixels[i] = color;
        }
    }
    void DrawTriangle(Vector3 v0, Vector3 v1, Vector3 v2, Color color)
    {
        // TODO not accurate, improve

        // p0 is top
        // p1 is middle
        // p2 is bottom
        if (v0.y > v1.y) swap(v0, v1);
        if (v1.y > v2.y) swap(v1, v2);
        if (v0.y > v1.y) swap(v0, v1);

        // TODO maybe remove Vector2Int
        Vector2Int p0 = { (int)v0.x, (int)v0.y };
        Vector2Int p1 = { (int)v1.x, (int)v1.y };
        Vector2Int p2 = { (int)v2.x, (int)v2.y };

        int dx1 = p2.x - p0.x;
        int dx2 = p1.x - p0.x;
        int dx3 = p2.x - p1.x;
        int dy1 = p2.y - p0.y;
        int dy2 = p1.y - p0.y;
        int dy3 = p2.y - p1.y;
        int dir1 = MathSignFloat(dx1);
        int dir2 = MathSignFloat(dx2);
        int dir3 = MathSignFloat(dx3);
        int dx1abs = abs(dx1);
        int dx2abs = abs(dx2);
        int dx3abs = abs(dx3);
        int err1 = dy1 / 2 - dx1abs;
        int err2 = dy2 / 2 - dx2abs;
        int err3 = dy3 / 2 - dx3abs;

        // TODO check for 0 division?
        float offset1 = (v2.z - v0.z) / dy1;
        float offset2 = (v1.z - v0.z) / dy2;
        float offset3 = (v2.z - v1.z) / dy3;

        int y = p0.y;

        int x1 = p0.x;
        float z1 = v0.z;

        int x2;
        float z2;
        if (dy2 > 0) { x2 = p0.x; z2 = v0.z; }
        else         { x2 = p1.x; z2 = v1.z; }

        int cross = dx1 * dy2 - dy1 * dx2;

        int* xl; int* xr; float* zl; float* zr;
        if (cross < 0) { xl = &x1; xr = &x2; zl = &z1; zr = &z2; }
        else           { xl = &x2; xr = &x1; zl = &z2; zr = &z1; }

        for (int i = 0; i < dy2; i++)
        {
            while (err1 < 0) { err1 += dy1; x1 += dir1; }
            while (err2 < 0) { err2 += dy2; x2 += dir2; }
            DrawLineHorizontal(y, *xl, *xr, *zl, *zr, color);
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
            DrawLineHorizontal(y, *xl, *xr, *zl, *zr, color);
            y++;
            err1 -= dx1abs;
            err3 -= dx3abs;
            z1 += offset1;
            z2 += offset3;
        }
        DrawLineHorizontal(y, *xl, *xr, *zl, *zr, color);
    }
    void DrawLine(Vector3 v0, Vector3 v1, Color color)
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
            SetPixelZ(x0, y0, z, color);
            if (err < 0) { err += max; (*axis1) += val1; }
                         { err -= min; (*axis2) += val2; }
            z += offset;
        }
        SetPixelZ(x0, y0, z, color);
    }
    void DrawLineHorizontal(int y, int xLeft, int xRight, float zLeft, float zRight, Color color)
    {
        int count = xRight - xLeft;
        float diff = zRight - zLeft;
        float offset = diff / count;

        for (int i = 0; i < count + 1; i++)
        {
            auto x = xLeft + i;
            SetPixelZ(x, y, zLeft, color);
            zLeft += offset;
        }
    }
    void DrawBorder(Color color)
    {
        int x = maxX;
        int y = maxY;
        for (int i = 0; i < width;  i++) SetPixel(i, 0, color);
        for (int i = 0; i < width;  i++) SetPixel(i, y, color);
        for (int i = 0; i < height; i++) SetPixel(0, i, color);
        for (int i = 0; i < height; i++) SetPixel(x, i, color);
    }
    void DrawCross(Color color)
    {
        int centerX = width / 2;
        int centerY = height / 2;
        for (int i = 0; i < width;  i++) SetPixel(i, centerY, color);
        for (int i = 0; i < height; i++) SetPixel(centerX, i, color);
    }
    void SetPixel(int x, int y, Color color)
    {
        auto i = x + y * width;
        pixels[i] = color;
    }
    void SetPixelZ(int x, int y, float z, Color color)
    {
        auto i = x + y * width;
        if (zbuffer[i] >= z)
        {
            zbuffer[i] = z;
            pixels[i] = color;
        }
    }

private:
    int width = 0;
    int height = 0;
    int maxX = 0;
    int maxY = 0;
    size_t pixelsSize = 0;
};
