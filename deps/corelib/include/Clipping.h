#pragma once

#include "BaseExt.h"
#include "HelperExt.h"

// functions made for specific case
// maybe remove hardcoded values

inline bool ClipLineBack(Vector3* v0, Vector3* v1)
{
    float offset = 0.1f;

    int flags = 0;

    if (v0->z < offset) flags += 1;
    if (v1->z < offset) flags += 2;

    switch (flags)
    {
        case /* 00 */ 0: return false;
        case /* 01 */ 1:
        {
            Vector3 diff = Vector3Subtract(*v0, *v1);
            diff *= (offset - v0->z) / diff.z;
            *v0 = Vector3Add(*v0, diff);
            v0->z = offset;
            return false;
        }
        case /* 10 */ 2:
        {
            Vector3 diff = Vector3Subtract(*v1, *v0);
            diff *= (offset - v1->z) / diff.z;
            *v1 = Vector3Add(*v1, diff);
            v1->z = offset;
            return false;
        }
        default /* 11 */ : return true;
    }
}
inline bool ClipLineLeft(Vector3* v0, Vector3* v1)
{
    float offset = -1;

    int flags = 0;

    if (v0->x < offset) flags += 1;
    if (v1->x < offset) flags += 2;

    switch (flags)
    {
        case /* 00 */ 0: return false;
        case /* 01 */ 1:
        {
            Vector3 diff = Vector3Subtract(*v0, *v1);
            diff *= (offset - v0->x) / diff.x;
            *v0 = Vector3Add(*v0, diff);
            v0->x = offset;
            return false;
        }
        case /* 10 */ 2:
        {
            Vector3 diff = Vector3Subtract(*v1, *v0);
            diff *= (offset - v1->x) / diff.x;
            *v1 = Vector3Add(*v1, diff);
            v1->x = offset;
            return false;
        }
        default /* 11 */ : return true;
    }
}
inline bool ClipLineRight(Vector3* v0, Vector3* v1)
{
    float offset = 1;

    int flags = 0;

    if (v0->x > offset) flags += 1;
    if (v1->x > offset) flags += 2;

    switch (flags)
    {
        case /* 00 */ 0: return false;
        case /* 01 */ 1:
        {
            Vector3 diff = Vector3Subtract(*v0, *v1);
            diff *= (offset - v0->x) / diff.x;
            *v0 = Vector3Add(*v0, diff);
            v0->x = offset;
            return false;
        }
        case /* 10 */ 2:
        {
            Vector3 diff = Vector3Subtract(*v1, *v0);
            diff *= (offset - v1->x) / diff.x;
            *v1 = Vector3Add(*v1, diff);
            v1->x = offset;
            return false;
        }
        default /* 11 */ : return true;
    }
}
inline bool ClipLineTop(Vector3* v0, Vector3* v1)
{
    float offset = 1;

    int flags = 0;

    if (v0->y > offset) flags += 1;
    if (v1->y > offset) flags += 2;

    switch (flags)
    {
        case /* 00 */ 0: return false;
        case /* 01 */ 1:
        {
            Vector3 diff = Vector3Subtract(*v0, *v1);
            diff *= (offset - v0->y) / diff.y;
            *v0 = Vector3Add(*v0, diff);
            v0->y = offset;
            return false;
        }
        case /* 10 */ 2:
        {
            Vector3 diff = Vector3Subtract(*v1, *v0);
            diff *= (offset - v1->y) / diff.y;
            *v1 = Vector3Add(*v1, diff);
            v1->y = offset;
            return false;
        }
        default /* 11 */ : return true;
    }
}
inline bool ClipLineBottom(Vector3* v0, Vector3* v1)
{
    float offset = -1;

    int flags = 0;

    if (v0->y < offset) flags += 1;
    if (v1->y < offset) flags += 2;

    switch (flags)
    {
        case /* 00 */ 0: return false;
        case /* 01 */ 1:
        {
            Vector3 diff = Vector3Subtract(*v0, *v1);
            diff *= (offset - v0->y) / diff.y;
            *v0 = Vector3Add(*v0, diff);
            v0->y = offset;
            return false;
        }
        case /* 10 */ 2:
        {
            Vector3 diff = Vector3Subtract(*v1, *v0);
            diff *= (offset - v1->y) / diff.y;
            *v1 = Vector3Add(*v1, diff);
            v1->y = offset;
            return false;
        }
        default /* 11 */ : return true;
    }
}

inline void ClipPoligonBack(Vector3* input, Vector3* output, int* vertexCount)
{
    int flags = 0;
    int index = 0;
    int initCount = *vertexCount;
    int finalCount = 0;

    float offset = 0.1f;

    Vector3 p0 = input[initCount - 1];

    if (p0.z < offset) flags += 2;

    for (int i = 0; i < initCount; i++)
    {
        flags = flags >> 1;

        Vector3 p1 = input[i];
        if (p1.z < offset) flags += 2;

        switch (flags)
        {
            /* 00 */ case 0:
            {
                output[index] = p0; index++;
                finalCount += 1;
                break;
            };
            /* 10 */ case 2:
            {
                output[index] = p0; index++;
                auto diff = p1 - p0;
                auto newPoint = p0 + diff * (offset - p0.z) / diff.z;
                newPoint.z = offset;
                output[index] = newPoint; index++;
                finalCount += 2;
                break;
            };
            /* 01 */ case 1:
            {
                auto diff = p1 - p0;
                auto newPoint = p0 + diff * (offset - p0.z) / diff.z;
                newPoint.z = offset;
                output[index] = newPoint; index++;
                finalCount += 1;
                break;
            };
            default: break;
        }

        p0 = p1;
    }

    *vertexCount = finalCount;
}
inline void ClipPoligonLeft(Vector3* input, Vector3* output, int* vertexCount)
{
    int flags = 0;
    int index = 0;
    int initCount = *vertexCount;
    int finalCount = 0;

    float offset = -1;

    Vector3 p0 = input[initCount - 1];

    if (p0.x < offset) flags += 2;

    for (int i = 0; i < initCount; i++)
    {
        flags = flags >> 1;

        Vector3 p1 = input[i];
        if (p1.x < offset) flags += 2;

        switch (flags)
        {
            /* 00 */ case 0:
            {
                output[index] = p0; index++;
                finalCount += 1;
                break;
            };
            /* 10 */ case 2:
            {
                output[index] = p0; index++;
                auto diff = p1 - p0;
                auto newPoint = p0 + diff * (offset - p0.x) / diff.x;
                newPoint.x = offset;
                output[index] = newPoint; index++;
                finalCount += 2;
                break;
            };
            /* 01 */ case 1:
            {
                auto diff = p1 - p0;
                auto newPoint = p0 + diff * (offset - p0.x) / diff.x;
                newPoint.x = offset;
                output[index] = newPoint; index++;
                finalCount += 1;
                break;
            };
            default: break;
        }

        p0 = p1;
    }

    *vertexCount = finalCount;
}
inline void ClipPoligonRight(Vector3* input, Vector3* output, int* vertexCount)
{
    int flags = 0;
    int index = 0;
    int initCount = *vertexCount;
    int finalCount = 0;

    float offset = 1;

    Vector3 p0 = input[initCount - 1];

    if (p0.x > offset) flags += 2;

    for (int i = 0; i < initCount; i++)
    {
        flags = flags >> 1;

        Vector3 p1 = input[i];
        if (p1.x > offset) flags += 2;

        switch (flags)
        {
            /* 00 */ case 0:
            {
                output[index] = p0; index++;
                finalCount += 1;
                break;
            };
            /* 10 */ case 2:
            {
                output[index] = p0; index++;
                auto diff = p1 - p0;
                auto newPoint = p0 + diff * (offset - p0.x) / diff.x;
                newPoint.x = offset;
                output[index] = newPoint; index++;
                finalCount += 2;
                break;
            };
            /* 01 */ case 1:
            {
                auto diff = p1 - p0;
                auto newPoint = p0 + diff * (offset - p0.x) / diff.x;
                newPoint.x = offset;
                output[index] = newPoint; index++;
                finalCount += 1;
                break;
            };
            default: break;
        }

        p0 = p1;
    }

    *vertexCount = finalCount;
}
inline void ClipPoligonTop(Vector3* input, Vector3* output, int* vertexCount)
{
    int flags = 0;
    int index = 0;
    int initCount = *vertexCount;
    int finalCount = 0;

    float offset = 1;

    Vector3 p0 = input[initCount - 1];

    if (p0.y > offset) flags += 2;

    for (int i = 0; i < initCount; i++)
    {
        flags = flags >> 1;

        Vector3 p1 = input[i];
        if (p1.y > offset) flags += 2;

        switch (flags)
        {
            /* 00 */ case 0:
            {
                output[index] = p0; index++;
                finalCount += 1;
                break;
            };
            /* 10 */ case 2:
            {
                output[index] = p0; index++;
                auto diff = p1 - p0;
                auto newPoint = p0 + diff * (offset - p0.y) / diff.y;
                newPoint.y = offset;
                output[index] = newPoint; index++;
                finalCount += 2;
                break;
            };
            /* 01 */ case 1:
            {
                auto diff = p1 - p0;
                auto newPoint = p0 + diff * (offset - p0.y) / diff.y;
                newPoint.y = offset;
                output[index] = newPoint; index++;
                finalCount += 1;
                break;
            };
            default: break;
        }

        p0 = p1;
    }

    *vertexCount = finalCount;
}
inline void ClipPoligonBottom(Vector3* input, Vector3* output, int* vertexCount)
{
    int flags = 0;
    int index = 0;
    int initCount = *vertexCount;
    int finalCount = 0;

    float offset = -1;

    Vector3 p0 = input[initCount - 1];

    if (p0.y < offset) flags += 2;

    for (int i = 0; i < initCount; i++)
    {
        flags = flags >> 1;

        Vector3 p1 = input[i];
        if (p1.y < offset) flags += 2;

        switch (flags)
        {
            /* 00 */ case 0:
            {
                output[index] = p0; index++;
                finalCount += 1;
                break;
            };
            /* 10 */ case 2:
            {
                output[index] = p0; index++;
                auto diff = p1 - p0;
                auto newPoint = p0 + diff * (offset - p0.y) / diff.y;
                newPoint.y = offset;
                output[index] = newPoint; index++;
                finalCount += 2;
                break;
            };
            /* 01 */ case 1:
            {
                auto diff = p1 - p0;
                auto newPoint = p0 + diff * (offset - p0.y) / diff.y;
                newPoint.y = offset;
                output[index] = newPoint; index++;
                finalCount += 1;
                break;
            };
            default: break;
        }

        p0 = p1;
    }

    *vertexCount = finalCount;
}

// maybe better line clipping

inline int GetPointState(float x, float y)
{
    const int INSIDE = 0; // 0000
    const int LEFT   = 1; // 0001
    const int RIGHT  = 2; // 0010
    const int BOTTOM = 4; // 0100
    const int TOP    = 8; // 1000

    const int xmin = -1;
    const int xmax =  1;
    const int ymin = -1;
    const int ymax =  1;

	int code = INSIDE;

	if      (x < xmin) code |= LEFT;
	else if (x > xmax) code |= RIGHT;
	if      (y < ymin) code |= BOTTOM;
	else if (y > ymax) code |= TOP;

	return code;
}
inline void ClipLine(Vector3& p0, Vector3& p1, int& outCode)
{
    const int LEFT   = 1; // 0001
    const int RIGHT  = 2; // 0010
    const int BOTTOM = 4; // 0100
    const int TOP    = 8; // 1000

    const int xmin = -1;
    const int xmax =  1;
    const int ymin = -1;
    const int ymax =  1;

	int code0 = GetPointState(p0.x, p0.y);
	int code1 = GetPointState(p1.x, p1.y);

	while (true)
    {
		if (!(code0 | code1)) { outCode = 0; return; } // points inside
        if (  code0 & code1 ) { outCode = 1; return; } // points in same outside zone

        int code =
            code0 > code1 ?
            code0 : code1;

        float x = 0;
        float y = 0;

        if      (code & LEFT)   { y = p0.y + (p1.y - p0.y) * (xmin - p0.x) / (p1.x - p0.x); x = xmin; } // point is to the left of clip window
        else if (code & RIGHT)  { y = p0.y + (p1.y - p0.y) * (xmax - p0.x) / (p1.x - p0.x); x = xmax; } // point is to the right of clip window
        if      (code & BOTTOM) { x = p0.x + (p1.x - p0.x) * (ymin - p0.y) / (p1.y - p0.y); y = ymin; } // point is below the clip window
        else if (code & TOP)    { x = p0.x + (p1.x - p0.x) * (ymax - p0.y) / (p1.y - p0.y); y = ymax; } // point is above the clip window

        if (code == code0) { p0.x = x; p0.y = y; code0 = GetPointState(p0.x, p0.y); }
        else               { p1.x = x; p1.y = y; code1 = GetPointState(p1.x, p1.y); }
	}
}