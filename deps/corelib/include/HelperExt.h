#ifndef HELPEREXT_H
#define HELPEREXT_H

#include "Helper.h"

inline Vector2 operator -  (Vector2 left, Vector2 right)
{
    left.x -= right.x;
    left.y -= right.y;
    return left;
}
inline Vector2 operator *  (Vector2 v, float f)
{
    v.x *= f;
    v.y *= f;
    return v;
}
inline Vector2 operator /  (Vector2 v, float f)
{
    v.x /= f;
    v.y /= f;
    return v;
}
inline Vector2 operator /= (Vector2& v, float f)
{
    v.x /= f;
    v.y /= f;
    return v;
}

inline bool    operator == (Vector3 left, Vector3 right)
{
    if (left.x != right.x) { return false; };
    if (left.y != right.y) { return false; };
    if (left.z != right.z) { return false; };
                             return true;
}
inline Vector3 operator -  (Vector3 v)
{
    return {-v.x, -v.y, -v.z};
}
inline Vector3 operator +  (Vector3 left, Vector3 right)
{
    left.x += right.x;
    left.y += right.y;
    left.z += right.z;
    return left;
}
inline Vector3 operator -  (Vector3 left, Vector3 right)
{
    left.x -= right.x;
    left.y -= right.y;
    left.z -= right.z;
    return left;
}
inline Vector3 operator *  (Vector3 v, float f)
{
    v.x *= f;
    v.y *= f;
    v.z *= f;
    return v;
}
inline Vector3 operator /  (Vector3 v, float f)
{
    v.x /= f;
    v.y /= f;
    v.z /= f;
    return v;
}
inline Vector3 operator *  (Vector3 v, Matrix m)
{
    Vector4 col0 = { m.m[0][0], m.m[1][0], m.m[2][0], m.m[3][0] };
    Vector4 col1 = { m.m[0][1], m.m[1][1], m.m[2][1], m.m[3][1] };
    Vector4 col2 = { m.m[0][2], m.m[1][2], m.m[2][2], m.m[3][2] };

    Vector4 row0 = { v.x, v.y, v.z, 1 };

    float x = Vector4Dot(row0,col0);
    float y = Vector4Dot(row0,col1);
    float z = Vector4Dot(row0,col2);

    return { x, y, z };
}
inline Vector3 operator += (Vector3& left, Vector3 right)
{
    left.x += right.x;
    left.y += right.y;
    left.z += right.z;
    return left;
}
inline Vector3 operator -= (Vector3& left, Vector3 right)
{
    left.x -= right.x;
    left.y -= right.y;
    left.z -= right.z;
    return left;
}
inline Vector3 operator *= (Vector3& v, float f)
{
    v.x *= f;
    v.y *= f;
    v.z *= f;
    return v;
}
inline Vector3 operator /= (Vector3& v, float f)
{
    v.x /= f;
    v.y /= f;
    v.z /= f;
    return v;
}
inline Vector3 operator *= (Vector3& v, Matrix m)
{
    Vector4 col0 = { m.m[0][0], m.m[1][0], m.m[2][0], m.m[3][0] };
    Vector4 col1 = { m.m[0][1], m.m[1][1], m.m[2][1], m.m[3][1] };
    Vector4 col2 = { m.m[0][2], m.m[1][2], m.m[2][2], m.m[3][2] };

    Vector4 row0 = { v.x, v.y, v.z, 1 };

    float x = Vector4Dot(row0,col0);
    float y = Vector4Dot(row0,col1);
    float z = Vector4Dot(row0,col2);

    v = { x, y, z };

    return v;
}

inline Vector4 operator * (Vector4 v, Matrix m)
{
    Vector4 col0 = { m.m[0][0], m.m[1][0], m.m[2][0], m.m[3][0] };
    Vector4 col1 = { m.m[0][1], m.m[1][1], m.m[2][1], m.m[3][1] };
    Vector4 col2 = { m.m[0][2], m.m[1][2], m.m[2][2], m.m[3][2] };
    Vector4 col3 = { m.m[0][3], m.m[1][3], m.m[2][3], m.m[3][3] };

    Vector4 row0 = { v.x, v.y, v.z, 1 };

    float x = Vector4Dot(row0,col0);
    float y = Vector4Dot(row0,col1);
    float z = Vector4Dot(row0,col2);
    float w = Vector4Dot(row0,col3);

    return { x, y, z, w };
}
inline Vector4 operator / (Vector4 v, float f)
{
    v.x /= f;
    v.y /= f;
    v.z /= f;
    v.w /= f;
    return v;
}

inline Matrix operator * (Matrix left, Matrix right)
{
    return MatrixMultiply(left, right);
}

#endif
