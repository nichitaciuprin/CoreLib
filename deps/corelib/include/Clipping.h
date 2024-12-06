// https://fabiensanglard.net/polygon_codec/
// https://fabiensanglard.net/polygon_codec/clippingdocument/p245-blinn.pdf
// https://fabiensanglard.net/polygon_codec/clippingdocument/Clipping.pdf

#pragma once

#include "BaseExt.h"
#include "HelperExt.h"

inline bool ClipLineBack(Vector3* v0, Vector3* v1, float offset)
{
    int flags = 0;

    if (v0->z < offset) flags += 1;
    if (v1->z < offset) flags += 2;

    switch (flags)
    {
        case 0:
        {
            return false;
        }
        case 1:
        {
            float t = MathInverseLerp(v0->z, v1->z, offset);

            v0->x = MathLerp(v0->x, v1->x, t);
            v0->y = MathLerp(v0->y, v1->y, t);
            v0->z = offset;

            return false;
        }
        case 2:
        {
            float t = MathInverseLerp(v0->z, v1->z, offset);

            v1->x = MathLerp(v0->x, v1->x, t);
            v1->y = MathLerp(v0->y, v1->y, t);
            v1->z = offset;

            return false;
        }
        default:
        {
            return true;
        }
    }
}
inline bool ClipLineFront(Vector3* v0, Vector3* v1, float offset)
{
    int flags = 0;

    if (v0->z > offset) flags += 1;
    if (v1->z > offset) flags += 2;

    switch (flags)
    {
        case 0:
        {
            return false;
        }
        case 1:
        {
            float t = MathInverseLerp(v0->z, v1->z, offset);

            v0->x = MathLerp(v0->x, v1->x, t);
            v0->y = MathLerp(v0->y, v1->y, t);
            v0->z = offset;

            return false;
        }
        case 2:
        {
            float t = MathInverseLerp(v0->z, v1->z, offset);

            v1->x = MathLerp(v0->x, v1->x, t);
            v1->y = MathLerp(v0->y, v1->y, t);
            v1->z = offset;

            return false;
        }
        default:
        {
            return true;
        }
    }
}
inline bool ClipLineLeft(Vector3* v0, Vector3* v1, float offset)
{
    int flags = 0;

    if (v0->x < offset) flags += 1;
    if (v1->x < offset) flags += 2;

    switch (flags)
    {
        case 0:
        {
            return false;
        }
        case 1:
        {
            float t = MathInverseLerp(v0->x, v1->x, offset);

            v0->x = offset;
            v0->y = MathLerp(v0->y, v1->y, t);
            v0->z = MathLerp(v0->z, v1->z, t);

            return false;
        }
        case 2:
        {
            float t = MathInverseLerp(v0->x, v1->x, offset);

            v1->x = offset;
            v1->y = MathLerp(v0->y, v1->y, t);
            v1->z = MathLerp(v0->z, v1->z, t);

            return false;
        }
        default:
        {
            return true;
        }
    }
}
inline bool ClipLineRight(Vector3* v0, Vector3* v1, float offset)
{
    int flags = 0;

    if (v0->x > offset) flags += 1;
    if (v1->x > offset) flags += 2;

    switch (flags)
    {
        case 0:
        {
            return false;
        }
        case 1:
        {
            float t = MathInverseLerp(v0->x, v1->x, offset);

            v0->x = offset;
            v0->y = MathLerp(v0->y, v1->y, t);
            v0->z = MathLerp(v0->z, v1->z, t);

            return false;
        }
        case 2:
        {
            float t = MathInverseLerp(v0->x, v1->x, offset);

            v1->x = offset;
            v1->y = MathLerp(v0->y, v1->y, t);
            v1->z = MathLerp(v0->z, v1->z, t);

            return false;
        }
        default:
        {
            return true;
        }
    }
}
inline bool ClipLineDown(Vector3* v0, Vector3* v1, float offset)
{
    int flags = 0;

    if (v0->y < offset) flags += 1;
    if (v1->y < offset) flags += 2;

    switch (flags)
    {
        case 0:
        {
            return false;
        }
        case 1:
        {
            float t = MathInverseLerp(v0->y, v1->y, offset);

            v0->x = MathLerp(v0->x, v1->x, t);
            v0->y = offset;
            v0->z = MathLerp(v0->z, v1->z, t);

            return false;
        }
        case 2:
        {
            float t = MathInverseLerp(v0->y, v1->y, offset);

            v1->x = MathLerp(v0->x, v1->x, t);
            v1->y = offset;
            v1->z = MathLerp(v0->z, v1->z, t);

            return false;
        }
        default:
        {
            return true;
        }
    }
}
inline bool ClipLineUp(Vector3* v0, Vector3* v1, float offset)
{
    int flags = 0;

    if (v0->y > offset) flags += 1;
    if (v1->y > offset) flags += 2;

    switch (flags)
    {
        case 0:
        {
            return false;
        }
        case 1:
        {
            float t = MathInverseLerp(v0->y, v1->y, offset);

            v0->x = MathLerp(v0->x, v1->x, t);
            v0->y = offset;
            v0->z = MathLerp(v0->z, v1->z, t);

            return false;
        }
        case 2:
        {
            float t = MathInverseLerp(v0->y, v1->y, offset);

            v1->x = MathLerp(v0->x, v1->x, t);
            v1->y = offset;
            v1->z = MathLerp(v0->z, v1->z, t);

            return false;
        }
        default:
        {
            return true;
        }
    }
}

inline void ClipPoligonBack(Vector3* input, Vector3* output, int* vertexCount, float offset)
{
    int flags = 0;
    int index = 0;
    int initCount = *vertexCount;
    int finalCount = 0;

    Vector3 p0 = input[initCount - 1];
    if (p0.z < offset) flags += 2;

    for (int i = 0; i < initCount; i++)
    {
        flags >>= 1;

        Vector3 p1 = input[i];
        if (p1.z < offset) flags += 2;

        switch (flags)
        {
            case 0:
            {
                output[index] = p0; index++;

                finalCount += 1;

                break;
            }
            case 1:
            {
                Vector3 newPoint;

                float t = MathInverseLerp(p0.z, p1.z, offset);

                newPoint.x = MathLerp(p0.x, p1.x, t);
                newPoint.y = MathLerp(p0.y, p1.y, t);
                newPoint.z = offset;

                output[index] = newPoint; index++;

                finalCount += 1;

                break;
            }
            case 2:
            {
                Vector3 newPoint;

                float t = MathInverseLerp(p0.z, p1.z, offset);

                newPoint.x = MathLerp(p0.x, p1.x, t);
                newPoint.y = MathLerp(p0.y, p1.y, t);
                newPoint.z = offset;

                output[index] = p0; index++;
                output[index] = newPoint; index++;

                finalCount += 2;

                break;
            }
            default:
            {
                break;
            }
        }

        p0 = p1;
    }

    *vertexCount = finalCount;
}
inline void ClipPoligonFront(Vector3* input, Vector3* output, int* vertexCount, float offset)
{
    int flags = 0;
    int index = 0;
    int initCount = *vertexCount;
    int finalCount = 0;

    Vector3 p0 = input[initCount - 1];
    if (p0.z > offset) flags += 2;

    for (int i = 0; i < initCount; i++)
    {
        flags >>= 1;

        Vector3 p1 = input[i];
        if (p1.z > offset) flags += 2;

        switch (flags)
        {
            case 0:
            {
                output[index] = p0; index++;

                finalCount += 1;

                break;
            }
            case 1:
            {
                Vector3 newPoint;

                float t = MathInverseLerp(p0.z, p1.z, offset);

                newPoint.x = MathLerp(p0.x, p1.x, t);
                newPoint.y = MathLerp(p0.y, p1.y, t);
                newPoint.z = offset;

                output[index] = newPoint; index++;

                finalCount += 1;

                break;
            }
            case 2:
            {
                Vector3 newPoint;

                float t = MathInverseLerp(p0.z, p1.z, offset);

                newPoint.x = MathLerp(p0.x, p1.x, t);
                newPoint.y = MathLerp(p0.y, p1.y, t);
                newPoint.z = offset;

                output[index] = p0;       index++;
                output[index] = newPoint; index++;

                finalCount += 2;

                break;
            }
            default:
            {
                break;
            }
        }

        p0 = p1;
    }

    *vertexCount = finalCount;
}
inline void ClipPoligonLeft(Vector3* input, Vector3* output, int* vertexCount, float offset)
{
    int flags = 0;
    int index = 0;
    int initCount = *vertexCount;
    int finalCount = 0;

    Vector3 p0 = input[initCount - 1];
    if (p0.x < offset) flags += 2;

    for (int i = 0; i < initCount; i++)
    {
        flags >>= 1;

        Vector3 p1 = input[i];
        if (p1.x < offset) flags += 2;

        switch (flags)
        {
            case 0:
            {
                output[index] = p0; index++;

                finalCount += 1;

                break;
            }
            case 1:
            {
                Vector3 newPoint;

                float t = MathInverseLerp(p0.x, p1.x, offset);

                newPoint.x = offset;
                newPoint.y = MathLerp(p0.y, p1.y, t);
                newPoint.z = MathLerp(p0.z, p1.z, t);

                output[index] = newPoint; index++;

                finalCount += 1;

                break;
            }
            case 2:
            {
                Vector3 newPoint;

                float t = MathInverseLerp(p0.x, p1.x, offset);

                newPoint.x = offset;
                newPoint.y = MathLerp(p0.y, p1.y, t);
                newPoint.z = MathLerp(p0.z, p1.z, t);

                output[index] = p0; index++;
                output[index] = newPoint; index++;

                finalCount += 2;

                break;
            }
            default:
            {
                break;
            }
        }

        p0 = p1;
    }

    *vertexCount = finalCount;
}
inline void ClipPoligonRight(Vector3* input, Vector3* output, int* vertexCount, float offset)
{
    int flags = 0;
    int index = 0;
    int initCount = *vertexCount;
    int finalCount = 0;

    Vector3 p0 = input[initCount - 1];
    if (p0.x > offset) flags += 2;

    for (int i = 0; i < initCount; i++)
    {
        flags >>= 1;

        Vector3 p1 = input[i];
        if (p1.x > offset) flags += 2;

        switch (flags)
        {
            case 0:
            {
                output[index] = p0; index++;

                finalCount += 1;

                break;
            }
            case 1:
            {
                Vector3 newPoint;

                float t = MathInverseLerp(p0.x, p1.x, offset);

                newPoint.x = offset;
                newPoint.y = MathLerp(p0.y, p1.y, t);
                newPoint.z = MathLerp(p0.z, p1.z, t);

                output[index] = newPoint; index++;

                finalCount += 1;

                break;
            }
            case 2:
            {
                Vector3 newPoint;

                float t = MathInverseLerp(p0.x, p1.x, offset);

                newPoint.x = offset;
                newPoint.y = MathLerp(p0.y, p1.y, t);
                newPoint.z = MathLerp(p0.z, p1.z, t);

                output[index] = p0;       index++;
                output[index] = newPoint; index++;

                finalCount += 2;

                break;
            }
            default:
            {
                break;
            }
        }

        p0 = p1;
    }

    *vertexCount = finalCount;
}
inline void ClipPoligonDown(Vector3* input, Vector3* output, int* vertexCount, float offset)
{
    int flags = 0;
    int index = 0;
    int initCount = *vertexCount;
    int finalCount = 0;

    Vector3 p0 = input[initCount - 1];
    if (p0.y < offset) flags += 2;

    for (int i = 0; i < initCount; i++)
    {
        flags >>= 1;

        Vector3 p1 = input[i];
        if (p1.y < offset) flags += 2;

        switch (flags)
        {
            case 0:
            {
                output[index] = p0; index++;

                finalCount += 1;

                break;
            }
            case 1:
            {
                Vector3 newPoint;

                float t = MathInverseLerp(p0.y, p1.y, offset);

                newPoint.x = MathLerp(p0.x, p1.x, t);
                newPoint.y = offset;
                newPoint.z = MathLerp(p0.z, p1.z, t);

                output[index] = newPoint; index++;

                finalCount += 1;

                break;
            }
            case 2:
            {
                Vector3 newPoint;

                float t = MathInverseLerp(p0.y, p1.y, offset);

                newPoint.x = MathLerp(p0.x, p1.x, t);
                newPoint.y = offset;
                newPoint.z = MathLerp(p0.z, p1.z, t);

                output[index] = p0; index++;
                output[index] = newPoint; index++;

                finalCount += 2;

                break;
            }
            default:
            {
                break;
            }
        }

        p0 = p1;
    }

    *vertexCount = finalCount;
}
inline void ClipPoligonUp(Vector3* input, Vector3* output, int* vertexCount, float offset)
{
    int flags = 0;
    int index = 0;
    int initCount = *vertexCount;
    int finalCount = 0;

    Vector3 p0 = input[initCount - 1];
    if (p0.y > offset) flags += 2;

    for (int i = 0; i < initCount; i++)
    {
        flags >>= 1;

        Vector3 p1 = input[i];
        if (p1.y > offset) flags += 2;

        switch (flags)
        {
            case 0:
            {
                output[index] = p0; index++;

                finalCount += 1;

                break;
            }
            case 1:
            {
                Vector3 newPoint;

                float t = MathInverseLerp(p0.y, p1.y, offset);

                newPoint.x = MathLerp(p0.x, p1.x, t);
                newPoint.y = offset;
                newPoint.z = MathLerp(p0.z, p1.z, t);

                output[index] = newPoint; index++;

                finalCount += 1;

                break;
            }
            case 2:
            {
                Vector3 newPoint;

                float t = MathInverseLerp(p0.y, p1.y, offset);

                newPoint.x = MathLerp(p0.x, p1.x, t);
                newPoint.y = offset;
                newPoint.z = MathLerp(p0.z, p1.z, t);

                output[index] = p0;       index++;
                output[index] = newPoint; index++;

                finalCount += 2;

                break;
            }
            default:
            {
                break;
            }
        }

        p0 = p1;
    }

    *vertexCount = finalCount;
}
