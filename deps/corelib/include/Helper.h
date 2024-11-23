// https://www.youtube.com/watch?v=pThw0S8MR7w&t=3s
// https://www.youtube.com/watch?v=t7Ztio8cwqM
// https://www.youtube.com/watch?v=4p-E_31XOPM
// https://www.youtube.com/watch?v=PahbNFypubE&ab_channel=Bisqwit
// https://www.youtube.com/watch?v=hxOw_p0kLfI&t=346s&ab_channel=Bisqwit
// https://www.youtube.com/watch?v=NYW1TKZG-58&ab_channel=CedricMartens
// https://www.youtube.com/watch?v=f4s1h2YETNY&ab_channel=kishimisu
// https://www.scratchapixel.com/lessons/3d-basic-rendering/perspective-and-orthographic-projection-matrix/projection-matrix-GPU-rendering-pipeline-clipping.html
// https://www.mdpi.com/1999-4893/16/4/201
// https://www.braynzarsoft.net/viewtutorial/q16390-transformations-and-world-view-projection-space-matrices
// https://www.ijirt.org/master/publishedpaper/IJIRT100119_PAPER.pdf
// https://carmencincotti.com/2022-11-28/from-clip-space-to-ndc-space/
// https://groups.csail.mit.edu/graphics/classes/6.837/F04/lectures/07_Pipeline_II.pdf
// https://gabrielgambetta.com/computer-graphics-from-scratch/11-clipping.html
// https://www.youtube.com/watch?v=HXSuNxpCzdM&ab_channel=javidx9
// http://www.sunshine2k.de/coding/java/TriangleRasterization/TriangleRasterization.html
// https://developer.nvidia.com/gpugems/gpugems2/part-v-image-oriented-computing/chapter-42-conservative-rasterization
// https://jpcharalambosh.co/posts/blur/
// https://jpcharalambosh.co/posts/ndc/#update
// http://www.songho.ca/opengl/gl_projectionmatrix.html#infinite
// https://rao.im/computer%20graphics/2022/03/03/prospective-projection/
// https://www.inf.ed.ac.uk/teaching/courses/cg/lectures/cg6_2013.pdf
// https://www.shadertoy.com/view/lsBSDm
// https://en.wikipedia.org/wiki/Bilinear_interpolation    inverse bilinear interpolation
// https://iquilezles.org/articles/ibilinear/
// https://www.youtube.com/watch?v=VMD7fsCYO9o
// http://www.cs.ucr.edu/~shinar/courses/cs130-winter-2019/content/clipping.pdf

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <memory.h>
#include <time.h>
#include <math.h>

#include "Subgen.h"

#define MY_PI        (float)3.14159265358979323846
#define MY_PI_MUL_2  (float)6.28318530717958647692
#define MY_PI_DIV_2  (float)1.57079632679489661923

typedef struct Vector2
{
    float x, y;
}
Vector2;
typedef struct Vector3
{
    float x, y, z;
}
Vector3;
typedef struct Vector4
{
    float x, y, z, w;
}
Vector4;
typedef struct Vector2Int
{
    int x, y;
}
Vector2Int;
typedef struct Matrix
{
    float m[4][4];
}
Matrix;
typedef struct Camera
{
    Vector3 position;
    float yaw;
    float pitch;
}
Camera;
typedef struct Bound
{
    Vector3 p0;
    Vector3 p1;
}
Bound;
typedef struct Box
{
    Vector3 position;
    Vector3 rotation;
    Vector3 halfExtent;
}
Box;
typedef struct Sphere
{
    Vector3 position;
    float radius;
}
Sphere;
typedef struct Pose
{
    Vector3 position;
    Vector3 rotation;
}
Pose;

inline int MathSignInt(int value)
{
    if (value > 0) { return  1; }
    if (value < 0) { return -1; }
                     return  0;
}
inline int MathMinInt(int v1, int v2)
{
    return fmin(v1, v2);
}
inline int MathMaxInt(int v1, int v2)
{
    return fmax(v1, v2);
}
inline int MathClampInt(int value, int min, int max)
{
    if (value < min) { return min; };
    if (value > max) { return max; };
                       return value;
}

inline float MathSignFloat(float value)
{
    if (value > 0) { return  1; }
    if (value < 0) { return -1; }
                     return  0;
}
inline float MathMinFloat(float value1, float value2)
{
    return fminf(value1, value2);
}
inline float MathMaxFloat(float value1, float value2)
{
    return fmaxf(value1, value2);
}
inline float MathAbs(float value)
{
    return fabsf(value);
}
inline float MathSqrt(float value)
{
    return sqrtf(value);
}
inline float MathClampFloat(float value, float min, float max)
{
    if (value < min) { return min; };
    if (value > max) { return max; };
                       return value;
}
inline float MathSin(float f)
{
    return sinf(f);
}
inline float MathCos(float f)
{
    return cosf(f);
}
inline float MathLerp(float a, float b, float t)
{
    return a + (b - a) * t;
}
inline float MathInverseLerp(float a, float b, float value)
{
    return (value - a) / (b - a);
}
inline float MathMod(float value, float div)
{
    return fmodf(value, div);
}
inline float MathPingPong(float value, float length)
{
    value = MathAbs(value);
    int whole = (int)(value/length);
    float rem = fmodf(value,length);
    return whole % 2 == 0 ? rem : length-rem;
}
inline float MathToDegree(float radians)
{
    float _180_div_pi = (float)57.2957795130823208768;
    return _180_div_pi * radians;
}
inline float MathToRadians(float degree)
{
    float _pi_div_180 = (float)0.01745329251994329576;
    return _pi_div_180 * degree;
}

inline bool Vector2Equal(Vector2 l, Vector2 r)
{
    return
    l.x == r.x &&
    l.y == r.y;
}
inline bool Vector3Equal(Vector3 l, Vector3 r)
{
    return
    l.x == r.x &&
    l.y == r.y &&
    l.z == r.z;
}
inline bool Vector4Equal(Vector4 l, Vector4 r)
{
    return
    l.x == r.x &&
    l.y == r.y &&
    l.z == r.z &&
    l.w == r.w;
}

inline Vector2 Vector2Neg(Vector2 r)
{
    r.x = -r.x;
    r.y = -r.y;
    return r;
}
inline Vector3 Vector3Neg(Vector3 r)
{
    r.x = -r.x;
    r.y = -r.y;
    r.z = -r.z;
    return r;
}
inline Vector4 Vector4Neg(Vector4 r)
{
    r.x = -r.x;
    r.y = -r.y;
    r.z = -r.z;
    r.w = -r.w;
    return r;
}

inline Vector2 Vector2Add(Vector2 l, Vector2 r)
{
    l.x += r.x;
    l.y += r.y;
    return l;
}
inline Vector3 Vector3Add(Vector3 l, Vector3 r)
{
    l.x += r.x;
    l.y += r.y;
    l.z += r.z;
    return l;
}
inline Vector4 Vector4Add(Vector4 l, Vector4 r)
{
    l.x += r.x;
    l.y += r.y;
    l.z += r.z;
    l.w += r.w;
    return l;
}

inline Vector2 Vector2Sub(Vector2 l, Vector2 r)
{
    l.x -= r.x;
    l.y -= r.y;
    return l;
}
inline Vector3 Vector3Sub(Vector3 l, Vector3 r)
{
    l.x -= r.x;
    l.y -= r.y;
    l.z -= r.z;
    return l;
}
inline Vector4 Vector4Sub(Vector4 l, Vector4 r)
{
    l.x -= r.x;
    l.y -= r.y;
    l.z -= r.z;
    l.w -= r.w;
    return l;
}

inline Vector2 Vector2Mul(Vector2 l, float r)
{
    l.x *= r;
    l.y *= r;
    return l;
}
inline Vector3 Vector3Mul(Vector3 l, float r)
{
    l.x *= r;
    l.y *= r;
    l.z *= r;
    return l;
}
inline Vector4 Vector4Mul(Vector4 l, float r)
{
    l.x *= r;
    l.y *= r;
    l.z *= r;
    l.w *= r;
    return l;
}

inline Vector2 Vector2Div(Vector2 l, float r)
{
    l.x /= r;
    l.y /= r;
    return l;
}
inline Vector3 Vector3Div(Vector3 l, float r)
{
    l.x /= r;
    l.y /= r;
    l.z /= r;
    return l;
}
inline Vector4 Vector4Div(Vector4 l, float r)
{
    l.x /= r;
    l.y /= r;
    l.z /= r;
    l.w /= r;
    return l;
}

inline float Vector2Dot(Vector2 l, Vector2 r)
{
    float x = l.x * r.x;
    float y = l.y * r.y;
    return x + y;
}
inline float Vector3Dot(Vector3 l, Vector3 r)
{
    float x = l.x * r.x;
    float y = l.y * r.y;
    float z = l.z * r.z;
    return x + y + z;
}
inline float Vector4Dot(Vector4 l, Vector4 r)
{
    float x = l.x * r.x;
    float y = l.y * r.y;
    float z = l.z * r.z;
    float w = l.w * r.w;
    return x + y + z + w;
}

inline Vector2 MatrixMultiply2L(Vector2 v, Matrix m)
{
    Vector4 col0 = { m.m[0][0], m.m[1][0], m.m[2][0], m.m[3][0] };
    Vector4 col1 = { m.m[0][1], m.m[1][1], m.m[2][1], m.m[3][1] };

    Vector4 row = { v.x, v.y, 1, 1 };

    v.x = Vector4Dot(row, col0);
    v.y = Vector4Dot(row, col1);

    return v;
}
inline Vector3 MatrixMultiply3L(Vector3 v, Matrix m)
{
    Vector4 col0 = { m.m[0][0], m.m[1][0], m.m[2][0], m.m[3][0] };
    Vector4 col1 = { m.m[0][1], m.m[1][1], m.m[2][1], m.m[3][1] };
    Vector4 col2 = { m.m[0][2], m.m[1][2], m.m[2][2], m.m[3][2] };

    Vector4 row = { v.x, v.y, v.z, 1 };

    v.x = Vector4Dot(row, col0);
    v.y = Vector4Dot(row, col1);
    v.z = Vector4Dot(row, col2);

    return v;
}
inline Vector4 MatrixMultiply4L(Vector4 v, Matrix m)
{
    Vector4 col0 = { m.m[0][0], m.m[1][0], m.m[2][0], m.m[3][0] };
    Vector4 col1 = { m.m[0][1], m.m[1][1], m.m[2][1], m.m[3][1] };
    Vector4 col2 = { m.m[0][2], m.m[1][2], m.m[2][2], m.m[3][2] };
    Vector4 col3 = { m.m[0][3], m.m[1][3], m.m[2][3], m.m[3][3] };

    Vector4 row = v;

    v.x = Vector4Dot(row, col0);
    v.y = Vector4Dot(row, col1);
    v.z = Vector4Dot(row, col2);
    v.w = Vector4Dot(row, col3);

    return v;
}

inline Vector2 MatrixMultiply2R(Matrix m, Vector2 v)
{
    Vector4 col0 = { m.m[0][0], m.m[0][1], m.m[0][2], m.m[0][3] };
    Vector4 col1 = { m.m[1][0], m.m[1][1], m.m[1][2], m.m[1][3] };

    Vector4 row = { v.x, v.y, 1, 1 };

    v.x = Vector4Dot(row, col0);
    v.y = Vector4Dot(row, col1);

    return v;
}
inline Vector3 MatrixMultiply3R(Matrix m, Vector3 v)
{
    Vector4 col0 = { m.m[0][0], m.m[0][1], m.m[0][2], m.m[0][3] };
    Vector4 col1 = { m.m[1][0], m.m[1][1], m.m[1][2], m.m[1][3] };
    Vector4 col2 = { m.m[2][0], m.m[2][1], m.m[2][2], m.m[2][3] };

    Vector4 row = { v.x, v.y, v.z, 1 };

    v.x = Vector4Dot(row, col0);
    v.y = Vector4Dot(row, col1);
    v.z = Vector4Dot(row, col2);

    return v;
}
inline Vector4 MatrixMultiply4R(Matrix m, Vector4 v)
{
    Vector4 col0 = { m.m[0][0], m.m[0][1], m.m[0][2], m.m[0][3] };
    Vector4 col1 = { m.m[1][0], m.m[1][1], m.m[1][2], m.m[1][3] };
    Vector4 col2 = { m.m[2][0], m.m[2][1], m.m[2][2], m.m[2][3] };
    Vector4 col3 = { m.m[3][0], m.m[3][1], m.m[3][2], m.m[3][3] };

    Vector4 row = v;

    v.x = Vector4Dot(row, col0);
    v.y = Vector4Dot(row, col1);
    v.z = Vector4Dot(row, col2);
    v.w = Vector4Dot(row, col3);

    return v;
}

inline Vector2 Vector2Abs(Vector2 v)
{
    v.x = fabs(v.x);
    v.y = fabs(v.y);
    return v;
}
inline Vector3 Vector3Abs(Vector3 v)
{
    v.x = fabs(v.x);
    v.y = fabs(v.y);
    v.z = fabs(v.z);
    return v;
}
inline Vector4 Vector4Abs(Vector4 v)
{
    v.x = fabs(v.x);
    v.y = fabs(v.y);
    v.z = fabs(v.z);
    v.w = fabs(v.w);
    return v;
}

inline float Vector2Length(Vector2 v)
{
    float x = v.x * v.x;
    float y = v.y * v.y;
    return MathSqrt(x + y);
}
inline float Vector3Length(Vector3 v)
{
    float x = v.x * v.x;
    float y = v.y * v.y;
    float z = v.z * v.z;
    return MathSqrt(x + y + z);
}
inline float Vector4Length(Vector4 v)
{
    float x = v.x * v.x;
    float y = v.y * v.y;
    float z = v.z * v.z;
    float w = v.w * v.w;
    return MathSqrt(x + y + z + w);
}

inline float Vector2LengthSquared(Vector2 v)
{
    float x = v.x * v.x;
    float y = v.y * v.y;
    return x + y;
}
inline float Vector3LengthSquared(Vector3 v)
{
    float x = v.x * v.x;
    float y = v.y * v.y;
    float z = v.z * v.z;
    return x + y + z;
}
inline float Vector4LengthSquared(Vector4 v)
{
    float x = v.x * v.x;
    float y = v.y * v.y;
    float z = v.z * v.z;
    float w = v.w * v.w;
    return x + y + z + w;
}

inline float Vector2Distance(Vector2 a, Vector2 b)
{
    Vector2 v = Vector2Sub(a, b);
    float x = v.x * v.x;
    float y = v.y * v.y;
    return MathSqrt(x + y);
}
inline float Vector3Distance(Vector3 a, Vector3 b)
{
    Vector3 v = Vector3Sub(a, b);
    float x = v.x * v.x;
    float y = v.y * v.y;
    float z = v.z * v.z;
    return MathSqrt(x + y + z);
}
inline float Vector4Distance(Vector4 a, Vector4 b)
{
    Vector4 v = Vector4Sub(a, b);
    float x = v.x * v.x;
    float y = v.y * v.y;
    float z = v.z * v.z;
    float w = v.w * v.w;
    return MathSqrt(x + y + z + w);
}

inline float Vector2DistanceSquared(Vector2 a, Vector2 b)
{
    Vector2 v = Vector2Sub(a, b);
    float x = v.x * v.x;
    float y = v.y * v.y;
    return x + y;
}
inline float Vector3DistanceSquared(Vector3 a, Vector3 b)
{
    Vector3 v = Vector3Sub(a, b);
    float x = v.x * v.x;
    float y = v.y * v.y;
    float z = v.z * v.z;
    return x + y + z;
}
inline float Vector4DistanceSquared(Vector4 a, Vector4 b)
{
    Vector4 v = Vector4Sub(a, b);
    float x = v.x * v.x;
    float y = v.y * v.y;
    float z = v.z * v.z;
    float w = v.w * v.w;
    return x + y + z + w;
}

inline Vector3 Vector2Lerp(Vector3 a, Vector3 b, float t)
{
    a.x = MathLerp(a.x, b.x, t);
    a.y = MathLerp(a.y, b.y, t);
    return a;
}
inline Vector3 Vector3Lerp(Vector3 a, Vector3 b, float t)
{
    a.x = MathLerp(a.x, b.x, t);
    a.y = MathLerp(a.y, b.y, t);
    a.z = MathLerp(a.z, b.z, t);
    return a;
}
inline Vector4 Vector4Lerp(Vector4 a, Vector4 b, float t)
{
    a.x = MathLerp(a.x, b.x, t);
    a.y = MathLerp(a.y, b.y, t);
    a.z = MathLerp(a.z, b.z, t);
    a.w = MathLerp(a.w, b.w, t);
    return a;
}

inline Vector2 Vector2Zero()
{
    return (Vector2){};
}
inline Vector3 Vector3Zero()
{
    return (Vector3){};
}
inline Vector4 Vector4Zero()
{
    return (Vector4){};
}

inline Vector2 Vector2Left()
{
    return (Vector2) { -1, 0 };
}
inline Vector2 Vector2Right()
{
    return (Vector2) { +1, 0 };
}
inline Vector2 Vector2Down()
{
    return (Vector2) { 0, -1 };
}
inline Vector2 Vector2Up()
{
    return (Vector2) { 0, +1 };
}

inline Vector3 Vector3Left()
{
    return (Vector3){ -1, 0, 0 };
}
inline Vector3 Vector3Right()
{
    return (Vector3){ 1, 0, 0 };
}
inline Vector3 Vector3Up()
{
    return (Vector3){ 0, 1, 0 };
}
inline Vector3 Vector3Down()
{
    return (Vector3){ 0, 1, 0 };
}
inline Vector3 Vector3Backward()
{
    return (Vector3){ 0, 0, -1 };
}
inline Vector3 Vector3Forward()
{
    return (Vector3){ 0, 0, 1 };
}

inline Vector2 Vector2Normalize(Vector2 v)
{
    float length = Vector2Length(v);
    if (length < 0) return Vector2Zero();
    return Vector2Div(v, length);
}
inline Vector3 Vector3Normalize(Vector3 v)
{
    float length = Vector3Length(v);
    if (length < 0) return Vector3Zero();
    return Vector3Div(v, length);
}
inline Vector4 Vector4Normalize(Vector4 v)
{
    float length = Vector4Length(v);
    if (length < 0) return Vector4Zero();
    return Vector4Div(v, length);
}

inline float Vector2Rotation(Vector2 v)
{
    // atan2( 0.0f,  1.0f ) = 0.0000
    // atan2( 1.0f,  1.0f ) = 0.7853
    // atan2( 1.0f,  0.0f ) = 1.5708
    // atan2( 1.0f, -1.0f ) = 2.3561
    // atan2( 0.0f, -1.0f ) = 3.1415
    return atan2(v.x, v.y);
}
inline Vector2 Vector2MoveTowards(Vector2 from, Vector2 target, float delta)
{
    if (Vector2Equal(from, target)) return from;
    Vector2 diff = Vector2Sub(target, from);
    float dist = Vector2Length(diff);
    if (dist <= delta) return target;
    diff = Vector2Normalize(diff);
    Vector2 moveVec = Vector2Mul(diff, delta);
    return Vector2Add(from, moveVec);
}
inline Vector2 Vector2MoveTowardsLimit(Vector2 from, Vector2 target, float delta, float limit)
{
    if (Vector2Equal(from, target)) return from;
    Vector2 diff = Vector2Sub(target, from);
    float dist = Vector2Length(diff);
    if (dist <= limit) return from;
    if (dist <= delta) return target;
    diff = Vector2Normalize(diff);
    Vector2 moveVec = Vector2Mul(diff, delta);
    return Vector2Add(from, moveVec);
}

inline Vector3 Vector3ClampLength(Vector3 vector, float min, float max)
{
    float length = Vector3Length(vector);
    if (length <= 0)  return Vector3Zero();
    if (length > max) return Vector3Mul(vector, (max/length));
    if (length < min) return Vector3Mul(vector, (min/length));
    return vector;
}
inline Vector3 Vector3Cross(Vector3 a, Vector3 b)
{
    return (Vector3)
    {
        a.y*b.z - a.z*b.y,
        a.z*b.x - a.x*b.z,
        a.x*b.y - a.y*b.x
    };
}
inline Vector3 Vector3RotateX(Vector3 v, float rot)
{
    float sin = sinf(rot);
    float cos = cosf(rot);
    float y = v.y * ( cos) + v.z * ( sin);
    float z = v.y * (-sin) + v.z * ( cos);
    return (Vector3){ v.x, y, z };
}
inline Vector3 Vector3RotateY(Vector3 v, float rot)
{
    float sin = sinf(rot);
    float cos = cosf(rot);
    float x = v.x * ( cos) + v.z * (-sin);
    float z = v.x * ( sin) + v.z * ( cos);
    return (Vector3){ x, v.y, z };
}
inline Vector3 Vector3RotateZ(Vector3 v, float rot)
{
    float sin = sinf(rot);
    float cos = cosf(rot);
    float x = v.x * ( cos) + v.y * ( sin);
    float y = v.x * (-sin) + v.y * ( cos);
    return (Vector3){ x, y, v.z };
}
inline Vector3 Vector3Rotate(Vector3 v, Vector3 rot)
{
    v = Vector3RotateX(v, rot.x);
    v = Vector3RotateY(v, rot.y);
    v = Vector3RotateZ(v, rot.z);
    return v;
}
inline Vector3 Vector3MoveTowards(Vector3 source, Vector3 target, float delta)
{
    if (Vector3Equal(source, target)) return source;
    Vector3 diff = Vector3Sub(target, source);
    float dist = Vector3Length(diff);
    if (dist <= delta) return target;
    diff = Vector3Normalize(diff);
    Vector3 moveVec = Vector3Mul(diff, delta);
    return Vector3Add(source, moveVec);
}
inline Vector3 Vector3MoveTowards2(Vector3 source, Vector3 target, float acc, float deltaTime)
{
    // like easeOut function

    float dist = Vector3Distance(source, target);
    float speed = MathSqrt(2 * dist * acc);
    return Vector3MoveTowards(source, target, speed * deltaTime);
}
inline Vector3 Vector3MoveTowards3(Vector3 source, Vector3 target, Vector3* velocity, float acc, float maxSpeed, float deltaTime)
{
    // like easeInOut function
    // but source will decelerate only on rotations

    Vector3 diff = Vector3Sub(target, source);
    Vector3 dir = Vector3Normalize(diff);

    Vector3 targetVelocity = Vector3Mul(dir, maxSpeed);

    Vector3 oldVelocity = *velocity;
    Vector3 newVelocity = Vector3MoveTowards(oldVelocity, targetVelocity, acc * deltaTime);

    Vector3 offset;

    offset = Vector3Add(oldVelocity, newVelocity);
    offset = Vector3Div(offset, 2);
    offset = Vector3Mul(offset, deltaTime);

    Vector3 result = Vector3Add(source, offset);

    *velocity = newVelocity;

    return result;
}
inline Vector3 Vector3MoveTowards4(Vector3 source, Vector3 target, Vector3* velocity, float acc, float deltaTime)
{
    // like easeInOut function

    Vector3 diff = Vector3Sub(target, source);
    Vector3 dir = Vector3Normalize(diff);

    float dist = Vector3Length(diff);
    float maxSpeed = MathSqrt(2 * dist * acc);

    Vector3 targetVelocity = Vector3Mul(dir, maxSpeed);

    Vector3 oldVelocity = *velocity;
    Vector3 newVelocity = Vector3MoveTowards(oldVelocity, targetVelocity, acc * deltaTime);

    Vector3 offset;

    offset = Vector3Add(oldVelocity, newVelocity);
    offset = Vector3Div(offset, 2);
    offset = Vector3Mul(offset, deltaTime);

    Vector3 result = Vector3Add(source, offset);

    *velocity = newVelocity;

    return result;
}
inline Vector3 Vector3MoveTowards5(Vector3 source, Vector3 target, Vector3* velocity, float acc, float deltaTime)
{
    // like easeInOut function
    // but removes jittering near target

    Vector3 diff = Vector3Sub(target, source);
    Vector3 dir = Vector3Normalize(diff);

    float dist = Vector3Length(diff);

    float maxSpeed = MathSqrt(2 * dist * acc);
    Vector3 targetVelocity = Vector3Mul(dir, maxSpeed);

    Vector3 oldVelocity = *velocity;
    Vector3 newVelocity;

    if (dist < 0.1f)
        newVelocity = targetVelocity;
    else
        newVelocity = Vector3MoveTowards(oldVelocity, targetVelocity, acc * deltaTime);

    Vector3 offset;

    offset = Vector3Add(oldVelocity, newVelocity);
    offset = Vector3Div(offset, 2);
    offset = Vector3Mul(offset, deltaTime);

    Vector3 result = Vector3Add(source, offset);

    *velocity = newVelocity;

    return result;
}

inline Matrix MatrixMultiply(Matrix l, Matrix r)
{
    Vector4 row0 = { l.m[0][0], l.m[0][1], l.m[0][2], l.m[0][3] };
    Vector4 row1 = { l.m[1][0], l.m[1][1], l.m[1][2], l.m[1][3] };
    Vector4 row2 = { l.m[2][0], l.m[2][1], l.m[2][2], l.m[2][3] };
    Vector4 row3 = { l.m[3][0], l.m[3][1], l.m[3][2], l.m[3][3] };

    Vector4 col0 = { r.m[0][0], r.m[1][0], r.m[2][0], r.m[3][0] };
    Vector4 col1 = { r.m[0][1], r.m[1][1], r.m[2][1], r.m[3][1] };
    Vector4 col2 = { r.m[0][2], r.m[1][2], r.m[2][2], r.m[3][2] };
    Vector4 col3 = { r.m[0][3], r.m[1][3], r.m[2][3], r.m[3][3] };

    float m00 = Vector4Dot(row0, col0);
    float m01 = Vector4Dot(row0, col1);
    float m02 = Vector4Dot(row0, col2);
    float m03 = Vector4Dot(row0, col3);

    float m10 = Vector4Dot(row1, col0);
    float m11 = Vector4Dot(row1, col1);
    float m12 = Vector4Dot(row1, col2);
    float m13 = Vector4Dot(row1, col3);

    float m20 = Vector4Dot(row2, col0);
    float m21 = Vector4Dot(row2, col1);
    float m22 = Vector4Dot(row2, col2);
    float m23 = Vector4Dot(row2, col3);

    float m30 = Vector4Dot(row3, col0);
    float m31 = Vector4Dot(row3, col1);
    float m32 = Vector4Dot(row3, col2);
    float m33 = Vector4Dot(row3, col3);

    return (Matrix)
    {
        m00,m01,m02,m03,
        m10,m11,m12,m13,
        m20,m21,m22,m23,
        m30,m31,m32,m33
    };
}
inline Matrix MatrixIdentity()
{
    return (Matrix)
    {
        1,0,0,0,
        0,1,0,0,
        0,0,1,0,
        0,0,0,1,
    };
}
inline Matrix MatrixTranspose(Matrix a)
{
    return (Matrix)
    {
        a.m[0][0],a.m[1][0],a.m[2][0],a.m[3][0],
        a.m[0][1],a.m[1][1],a.m[2][1],a.m[3][1],
        a.m[0][2],a.m[1][2],a.m[2][2],a.m[3][2],
        a.m[0][3],a.m[1][3],a.m[2][3],a.m[3][3]
    };
}
inline Matrix MatrixInvert(Matrix mat)
{
    Matrix result;

    float a00 = mat.m[0][0], a01 = mat.m[0][1], a02 = mat.m[0][2], a03 = mat.m[0][3];
    float a10 = mat.m[1][0], a11 = mat.m[1][1], a12 = mat.m[1][2], a13 = mat.m[1][3];
    float a20 = mat.m[2][0], a21 = mat.m[2][1], a22 = mat.m[2][2], a23 = mat.m[2][3];
    float a30 = mat.m[3][0], a31 = mat.m[3][1], a32 = mat.m[3][2], a33 = mat.m[3][3];

    float b00 = a00*a11 - a01*a10;
    float b01 = a00*a12 - a02*a10;
    float b02 = a00*a13 - a03*a10;
    float b03 = a01*a12 - a02*a11;
    float b04 = a01*a13 - a03*a11;
    float b05 = a02*a13 - a03*a12;
    float b06 = a20*a31 - a21*a30;
    float b07 = a20*a32 - a22*a30;
    float b08 = a20*a33 - a23*a30;
    float b09 = a21*a32 - a22*a31;
    float b10 = a21*a33 - a23*a31;
    float b11 = a22*a33 - a23*a32;

    float invDet = 1.0f / (b00*b11 - b01*b10 + b02*b09 + b03*b08 - b04*b07 + b05*b06);

    result.m[0][0] = ( a11*b11 - a12*b10 + a13*b09) * invDet;
    result.m[0][1] = (-a01*b11 + a02*b10 - a03*b09) * invDet;
    result.m[0][2] = ( a31*b05 - a32*b04 + a33*b03) * invDet;
    result.m[0][3] = (-a21*b05 + a22*b04 - a23*b03) * invDet;
    result.m[1][0] = (-a10*b11 + a12*b08 - a13*b07) * invDet;
    result.m[1][1] = ( a00*b11 - a02*b08 + a03*b07) * invDet;
    result.m[1][2] = (-a30*b05 + a32*b02 - a33*b01) * invDet;
    result.m[1][3] = ( a20*b05 - a22*b02 + a23*b01) * invDet;
    result.m[2][0] = ( a10*b10 - a11*b08 + a13*b06) * invDet;
    result.m[2][1] = (-a00*b10 + a01*b08 - a03*b06) * invDet;
    result.m[2][2] = ( a30*b04 - a31*b02 + a33*b00) * invDet;
    result.m[2][3] = (-a20*b04 + a21*b02 - a23*b00) * invDet;
    result.m[3][0] = (-a10*b09 + a11*b07 - a12*b06) * invDet;
    result.m[3][1] = ( a00*b09 - a01*b07 + a02*b06) * invDet;
    result.m[3][2] = (-a30*b03 + a31*b01 - a32*b00) * invDet;
    result.m[3][3] = ( a20*b03 - a21*b01 + a22*b00) * invDet;

    return result;
}
inline Matrix MatrixTranslate(Vector3 v)
{
    return (Matrix)
    {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        v.x, v.y, v.z, 1
    };
}
inline Matrix MatrixRotateX(float rad)
{
    float sin = sinf(rad);
    float cos = cosf(rad);
    return (Matrix)
    {
        1,   0,    0,    0,
        0,   cos, -sin,  0,
        0,   sin,  cos,  0,
        0,   0,    0,    1
    };
}
inline Matrix MatrixRotateY(float rad)
{
    float sin = sinf(rad);
    float cos = cosf(rad);
    return (Matrix)
    {
         cos,   0,  sin,   0,
           0,   1,    0,   0,
        -sin,   0,  cos,   0,
           0,   0,    0,   1
    };
}
inline Matrix MatrixRotateZ(float rad)
{
    float sin = sinf(rad);
    float cos = cosf(rad);
    return (Matrix)
    {
        cos, -sin,  0,   0,
        sin,  cos,  0,   0,
        0,    0,    1,   0,
        0,    0,    0,   1
    };
}
inline Matrix MatrixRotate(Vector3 rotation)
{
    Matrix result;
    Matrix matX = MatrixRotateX(rotation.x);
    Matrix matY = MatrixRotateY(rotation.y);
    Matrix matZ = MatrixRotateZ(rotation.z);
    result = matX;
    result = MatrixMultiply(result, matY);
    result = MatrixMultiply(result, matZ);
    return result;
}
inline Matrix MatrixScale(Vector3 scale)
{
    float x = scale.x;
    float y = scale.y;
    float z = scale.z;
    return (Matrix)
    {
        x, 0, 0, 0,
        0, y, 0, 0,
        0, 0, z, 0,
        0, 0, 0, 1
    };
}
inline Matrix MatrixWorld(Vector3 position, Vector3 direction)
{
    Vector3 zAxis = direction;
            zAxis = Vector3Normalize(zAxis); // maybe remove

    Vector3 xAxis = Vector3Cross(Vector3Up(), zAxis);
            xAxis = Vector3Normalize(xAxis);

    Vector3 yAxis = Vector3Cross(zAxis, xAxis);

    float x = position.x;
    float y = position.y;
    float z = position.z;

    return (Matrix)
    {
        xAxis.x, xAxis.y, xAxis.z, 0.0f,
        yAxis.x, yAxis.y, yAxis.z, 0.0f,
        zAxis.x, zAxis.y, zAxis.z, 0.0f,
              x,       y,       z, 1.0f
    };
}
inline Matrix MatrixWorld2(Vector3 position, Vector3 rotation, Vector3 scale)
{
    Matrix result;
    Matrix mat1 = MatrixScale(scale);
    Matrix mat2 = MatrixRotate(rotation);
    Matrix mat3 = MatrixTranslate(position);
    result = mat1;
    result = MatrixMultiply(result, mat2);
    result = MatrixMultiply(result, mat3);
    return result;
}
inline Matrix MatrixView(Vector3 eye, float yaw, float pitch)
{
    eye = Vector3Neg(eye);
    Matrix mat1 = MatrixTranslate(eye);
    Matrix mat2 = MatrixRotateY(yaw);
    Matrix mat3 = MatrixRotateX(-pitch);
    Matrix result;
    result = mat1;
    result = MatrixMultiply(result, mat2);
    result = MatrixMultiply(result, mat3);
    return result;
}
inline Matrix MatrixView2(Vector3 eye, Vector3 target, Vector3 up)
{
    // it almost works, try fixing it
    /*
    Vector3 zAxis = Vector3Sub(target, eye);
            zAxis = Vector3Normalize(zAxis);

    Vector3 xAxis = Vector3Cross(up, zAxis);
            xAxis = Vector3Normalize(xAxis);

    Vector3 yAxis = Vector3Cross(zAxis, xAxis);

    float x = -Vector3Dot(xAxis, eye);
    float y = -Vector3Dot(yAxis, eye);
    float z = -Vector3Dot(zAxis, eye);

    return (Matrix)
    {
        xAxis.x, xAxis.y, xAxis.z, 0.0f,
        yAxis.x, yAxis.y, yAxis.z, 0.0f,
        zAxis.x, zAxis.y, zAxis.z, 0.0f,
              x,       y,       z, 1.0f
    };
    */

    Vector3 zAxis = Vector3Sub(target, eye);
            zAxis = Vector3Normalize(zAxis);

    Vector3 xAxis = Vector3Cross(up, zAxis);
            xAxis = Vector3Normalize(xAxis);

    Vector3 yAxis = Vector3Cross(zAxis, xAxis);

    Matrix result =
    {
        xAxis.x, xAxis.y, xAxis.z, 0,
        yAxis.x, yAxis.y, yAxis.z, 0,
        zAxis.x, zAxis.y, zAxis.z, 0,
          eye.x,   eye.y,   eye.z, 1
    };

    result = MatrixInvert(result);

    return result;
}
inline Matrix MatrixView3(const Camera* camera)
{
    return MatrixView(camera->position, camera->yaw, camera->pitch);
}
inline Matrix MatrixOrthographic(float width, float height, float zNear, float zFar)
{
    float w = 2.0f / width;
    float h = 2.0f / height;
    float a = 1.0f / (zFar - zNear);
    float b = a * -zNear;
    return (Matrix)
    {
        w, 0, 0, 0,
        0, h, 0, 0,
        0, 0, a, 0,
        0, 0, b, 1
    };
}
inline Matrix MatrixPerspectiveCube(float width, float height, float near, float far)
{
    float n = near;
    float f = far;

    float r =  n;
    float t =  n;
    float l = -n;
    float b = -n;

    float w =  (2*n) / (r-l);
    float h =  (2*n) / (t-b);
    float a =  (f+n) / (f-n);

    float u = (r+l) / (r-l);
    float i = (t+b) / (t-b);
    float o = (2*f*n) / (f-n);

    return (Matrix)
    {
        w,  0,  0,  0,
        0,  h,  0,  0,
       -u, -i,  a,  1,
        0,  0, -o,  0
    };
}
inline Matrix MatrixPerspectiveCubeHalf(float width, float height, float near, float far)
{
    float n = near;
    float f = far;

    float aspectRatio = width / height;
    float fov = (float)(MY_PI_DIV_2);
    float h = 1.0f / tanf(fov / 2);
    float w = h / aspectRatio;
    float a = f / (f - n);
    float o = a * n;

    return (Matrix)
    {
        w,  0,  0,  0,
        0,  h,  0,  0,
        0,  0,  a,  1,
        0,  0, -o,  0
    };
}

inline Vector3 ToEuler(Vector4 q)
{
    Vector3 result;

    float x = q.x;
    float y = q.y;
    float z = q.z;
    float w = q.w;

    float x0 = 2.0f*(w*x + y*z);
    float x1 = 1.0f - 2.0f*(x*x + y*y);
    result.x = atan2f(x0, x1);

    float y0 = 2.0f*(w*y - z*x);
    y0 = y0 >  1.0f ?  1.0f : y0;
    y0 = y0 < -1.0f ? -1.0f : y0;
    result.y = asinf(y0);

    float z0 = 2.0f*(w*z + x*y);
    float z1 = 1.0f - 2.0f*(y*y + z*z);
    result.z = atan2f(z0, z1);

    return result;
}
inline Vector4 ToQuaternion(Vector3 e)
{
    Vector4 result;

    float pitch = e.x /= 2;
    float yaw   = e.y /= 2;
    float roll  = e.z /= 2;

    float x0 = cosf(pitch);
    float x1 = sinf(pitch);
    float y0 = cosf(yaw);
    float y1 = sinf(yaw);
    float z0 = cosf(roll);
    float z1 = sinf(roll);

    result.x = x1*y0*z0 - x0*y1*z1;
    result.y = x0*y1*z0 + x1*y0*z1;
    result.z = x0*y0*z1 - x1*y1*z0;
    result.w = x0*y0*z0 + x1*y1*z1;

    return result;
}

inline bool Vector3TriangleIsClockwise(Vector3 p1, Vector3 p2, Vector3 p3)
{
    Vector3 v1 = Vector3Sub(p2, p1);
    Vector3 v2 = Vector3Sub(p3, p1);
    float crossZ = v1.x*v2.y - v1.y*v2.x;
    return crossZ < 0;
}

inline Vector3 GetAxisX(Camera* camera)
{
    Vector3 result = { 1, 0, 0 };
    result = Vector3RotateX(result, camera->pitch);
    result = Vector3RotateY(result, -camera->yaw);
    return result;
}
inline Vector3 GetAxisY(Camera* camera)
{
    Vector3 result = { 0, 1, 0 };
    result = Vector3RotateX(result, camera->pitch);
    result = Vector3RotateY(result, -camera->yaw);
    return result;
}
inline Vector3 GetAxisZ(Camera* camera)
{
    Vector3 result = { 0, 0, 1 };
    result = Vector3RotateX(result, camera->pitch);
    result = Vector3RotateY(result, -camera->yaw);
    return result;
}

inline bool InFrustum(Vector3 point)
{
    if (point.z / MathAbs(point.x) < 1) return false;
    if (point.z / MathAbs(point.y) < 1) return false;
    return true;
}

inline void UpdateCameraRotation(Camera* camera, float deltaTime, bool left, bool up, bool down, bool right)
{
    float speed = (float)MY_PI;
    float speedDelta = speed * deltaTime;
    if (up)    camera->pitch += speedDelta;
    if (down)  camera->pitch -= speedDelta;
    if (right) camera->yaw   += speedDelta;
    if (left)  camera->yaw   -= speedDelta;

    // TODO review
    // Wrap yaw to avoid floating-point errors if we turn too far
    while (camera->yaw >=  MY_PI_MUL_2) camera->yaw -= MY_PI_MUL_2;
    while (camera->yaw <= -MY_PI_MUL_2) camera->yaw += MY_PI_MUL_2;

    // Clamp pitch to stop camera flipping upside down
    float degree = MathToRadians(85);
    if (camera->pitch >  degree) camera->pitch =  degree;
    if (camera->pitch < -degree) camera->pitch = -degree;
}
inline void UpdateCameraRotation2(Camera* camera, float rotX, float rotY)
{
    // inverses horizontal rotation when upsidedown
    // makes movement easy
    // float angle = cos(camera->pitch);
    // if (angle < 0)
    //     rotX = -rotX;

    camera->yaw += rotX;
    camera->pitch += rotY;
}
inline void UpdateCameraPosition(Camera* camera, float deltaTime, bool w, bool a, bool s, bool d, bool e, bool q)
{
    Vector3 x = GetAxisX(camera);
    Vector3 y = GetAxisY(camera);
    Vector3 z = GetAxisZ(camera);

    float speed = 50.0f;
    float speedDelta = speed * deltaTime;

    x = Vector3Mul(x, speedDelta);
    y = Vector3Mul(y, speedDelta);
    z = Vector3Mul(z, speedDelta);

    if (d) camera->position = Vector3Add      (camera->position, x);
    if (a) camera->position = Vector3Sub (camera->position, x);
    if (e) camera->position = Vector3Add      (camera->position, y);
    if (q) camera->position = Vector3Sub (camera->position, y);
    if (w) camera->position = Vector3Add      (camera->position, z);
    if (s) camera->position = Vector3Sub (camera->position, z);
}
inline void UpdateCameraPosition2(Camera* camera, Vector3 move)
{
    // TODO double check it works

    Vector3 x = GetAxisX(camera);
    Vector3 y = GetAxisY(camera);
    Vector3 z = GetAxisZ(camera);

    x.x *= move.x; x.y *= move.x; x.z *= move.x;
    y.x *= move.y; y.y *= move.y; y.z *= move.y;
    z.x *= move.z; z.y *= move.z; z.z *= move.z;

    camera->position = Vector3Add(camera->position, z);
    camera->position = Vector3Add(camera->position, y);
    camera->position = Vector3Add(camera->position, x);
}

inline void UpdateCameraFpsRotation(Camera* camera, Vector2 rot)
{
    camera->yaw += rot.x;
    camera->pitch += rot.y;

    // maybe bigger angle?
    // camera.pitch = MathClamp(camera.pitch, MathToRadians(-120.0f), MathToRadians(120.0f));

    camera->pitch = MathClampFloat(camera->pitch, MathToRadians(-90.0f), MathToRadians(90.0f));
}
inline void UpdateCameraFpsMovement(Camera* camera, Vector2 move)
{
    Vector3 up = { 0, 1, 0 };
    Vector3 forward = { 0, 0, 1 };

    forward = Vector3RotateY(forward, -camera->yaw);

    Vector3 right = Vector3Cross(up, forward);

    forward.x *= move.y;
    forward.z *= move.y;
    right.x *= move.x;
    right.z *= move.x;

    camera->position = Vector3Add(camera->position, forward);
    camera->position = Vector3Add(camera->position, right);
}
inline void UpdateCameraFps(Camera* camera, Vector2 move, Vector2 rot)
{
    UpdateCameraFpsRotation(camera, rot);
    UpdateCameraFpsMovement(camera, move);
}

inline float BoundMinX(Bound* bound)
{
    return fminf(bound->p0.x, bound->p1.x);
}
inline float BoundMaxX(Bound* bound)
{
    return fmaxf(bound->p0.x, bound->p1.x);
}
inline float BoundMinY(Bound* bound)
{
    return fminf(bound->p0.y, bound->p1.y);
}
inline float BoundMaxY(Bound* bound)
{
    return fmaxf(bound->p0.y, bound->p1.y);
}
inline float BoundMinZ(Bound* bound)
{
    return fminf(bound->p0.z, bound->p1.z);
}
inline float BoundMaxZ(Bound* bound)
{
    return fmaxf(bound->p0.z, bound->p1.z);
}
inline Vector3 BoundSize(const Bound* bound)
{
    Vector3 result = Vector3Sub(bound->p0, bound->p1);
    result.x = MathAbs(result.x);
    result.y = MathAbs(result.y);
    result.z = MathAbs(result.z);
    return result;
}
inline Vector3 BoundCenter(const Bound* bound)
{
    Vector3 result;
    result = Vector3Add(bound->p0, bound->p1);
    result = Vector3Div(result, 2);
    return result;
}

inline Vector3 RandomPointInside(Subgen* subgen, Bound* bound)
{
    float x = SubgenRange(subgen, BoundMinX(bound), BoundMaxX(bound));
    float y = SubgenRange(subgen, BoundMinY(bound), BoundMaxY(bound));
    float z = SubgenRange(subgen, BoundMinZ(bound), BoundMaxZ(bound));
    return (Vector3){ x, y, z };
}
inline Vector3 RandomPointTopFace(Subgen* subgen, Bound* bound)
{
    float maxY = BoundMaxY(bound);

    float minX = BoundMinX(bound);
    float maxX = BoundMaxX(bound);

    float minZ = BoundMinZ(bound);
    float maxZ = BoundMaxZ(bound);

    float randX = SubgenRange(subgen, minX, maxX);
    float randZ = SubgenRange(subgen, minZ, maxZ);

    return (Vector3){ randX, maxY, randZ };
}
inline Vector3 WrapAround(Bound* bound, Vector3 point)
{
    Vector3 size = BoundSize(bound);
    if      (point.x < BoundMinX(bound)) point.x += size.x;
    else if (point.x > BoundMaxX(bound)) point.x -= size.x;
    if      (point.y < BoundMinY(bound)) point.y += size.y;
    else if (point.y > BoundMaxY(bound)) point.y -= size.y;
    if      (point.z < BoundMinZ(bound)) point.z += size.z;
    else if (point.z > BoundMaxZ(bound)) point.z -= size.z;
    return point;
}
inline Vector3 BoundShortPathIn(Bound* aabb, Vector3 point)
{
    Vector3 result = Vector3Zero();
    if      (point.x < BoundMinX(aabb)) result.x = BoundMinX(aabb) - point.x;
    else if (point.x > BoundMaxX(aabb)) result.x = BoundMaxX(aabb) - point.x;
    if      (point.y < BoundMinY(aabb)) result.y = BoundMinY(aabb) - point.y;
    else if (point.y > BoundMaxY(aabb)) result.y = BoundMaxY(aabb) - point.y;
    if      (point.z < BoundMinZ(aabb)) result.z = BoundMinZ(aabb) - point.z;
    else if (point.z > BoundMaxZ(aabb)) result.z = BoundMaxZ(aabb) - point.z;
    return result;
}

inline bool InsideSphere(Vector3 point, Sphere sphere)
{
    Vector3 diff = Vector3Sub(point, sphere.position);
    return Vector3LengthSquared(diff) <= sphere.radius * sphere.radius;
}
inline bool RaycastFull1(Vector3 origin, Vector3 dirNorm, Sphere sphere)
{
    // TODO must be tested

    Vector3 v1 = Vector3Sub(sphere.position, origin);
    float v2Length = Vector3Dot(dirNorm, v1);
    Vector3 v2 = Vector3Mul(dirNorm, v2Length);
    Vector3 v3 = Vector3Sub(v2, v1);
    float v3LengthSquared = Vector3LengthSquared(v3);
    float radiusSquared = sphere.radius * sphere.radius;

    // no intersection
    if (v3LengthSquared > radiusSquared) return false;

    float offset = MathSqrt(radiusSquared - v3LengthSquared);

    float dist1 = v2Length - offset;
    float dist2 = v2Length + offset;

    Vector3 point1 = Vector3Add(origin, Vector3Mul(dirNorm, dist1));
    Vector3 point2 = Vector3Add(origin, Vector3Mul(dirNorm, dist2));

    Vector3 normal1 = Vector3Sub(point1, sphere.position);
    Vector3 normal2 = Vector3Sub(point2, sphere.position);

    normal1 = Vector3Normalize(normal1);
    normal2 = Vector3Normalize(normal2);

    return true;
}
inline bool RaycastFull2(Vector3 origin, Vector3 dirNorm, Sphere sphere)
{
    // TODO must be tested

    Vector3 diff = Vector3Sub(origin, sphere.position);
    float b = Vector3Dot(dirNorm, diff) * 2;
    float c = Vector3LengthSquared(diff) - (sphere.radius * sphere.radius);
    float deltaSquared = b * b - 4 * c;

    // no intersection
    if (deltaSquared < 0) return false;

    float delta = MathSqrt(deltaSquared);

    float dist1 = (-b - delta) / 2;
    float dist2 = (-b + delta) / 2;

    Vector3 point1 = Vector3Add(origin, Vector3Mul(dirNorm, dist1));
    Vector3 point2 = Vector3Add(origin, Vector3Mul(dirNorm, dist2));

    Vector3 normal1 = Vector3Sub(point1, sphere.position);
    Vector3 normal2 = Vector3Sub(point2, sphere.position);

    normal1 = Vector3Normalize(normal1);
    normal2 = Vector3Normalize(normal2);

    return true;
}
inline bool Raycast(Vector3 origin, Vector3 dirNorm, Sphere sphere, float* outDistance, Vector3* outPoint, Vector3* outNormal)
{
    // TODO must be tested
    // Assuming the origin is outside the sphere

    Vector3 v1 = Vector3Sub(sphere.position, origin);
    float v2Length = Vector3Dot(dirNorm, v1);

    // sphere is behind
    if (v2Length < 0) return false;

    Vector3 v2 = Vector3Mul(dirNorm, v2Length);
    Vector3 v3 = Vector3Sub(v2, v1);
    float v3LengthSquared = Vector3LengthSquared(v3);
    float radiusSquared = sphere.radius * sphere.radius;

    // no intersection
    if (v3LengthSquared > radiusSquared) return false;

    float offset = MathSqrt(radiusSquared - v3LengthSquared);
    float dist = v2Length - offset;
    Vector3 point = Vector3Add(origin, Vector3Mul(dirNorm, dist));
    Vector3 normal = Vector3Sub(point, sphere.position);
    normal = Vector3Normalize(normal);

    *outDistance = dist;
    *outPoint = point;
    *outNormal = normal;

    return true;
}
inline bool LineSegmentIntersection(Vector3 start, Vector3 end, Sphere sphere)
{
    // TODO must be tested

    Vector3 origin = start;
    Vector3 dir = Vector3Sub(end, start);
    Vector3 dirNorm = Vector3Normalize(dir);

    Vector3 v1 = Vector3Sub(sphere.position, origin);
    float v2Length = Vector3Dot(dirNorm, v1);
    Vector3 v2 = Vector3Mul(dirNorm, v2Length);
    Vector3 v3 = Vector3Sub(v2, v1);
    float v3LengthSquared = Vector3LengthSquared(v3);
    float radiusSquared = sphere.radius * sphere.radius;

    // no intersection
    if (v3LengthSquared > radiusSquared) return false;

    float offset = MathSqrt(radiusSquared - v3LengthSquared);
    float dist1 = v2Length - offset;
    float dist2 = v2Length + offset;
    float maxDist = MathMaxFloat(dist1, dist2);

    // all points behind
    if (maxDist < 0) return false;

    // segment is short
    if (Vector3LengthSquared(dir) < maxDist * maxDist) return false;

    return true;
}

inline Pose GetLocalPose(Pose parentWorld, Pose childWorld)
{
    childWorld.rotation = Vector3Sub(childWorld.rotation, parentWorld.rotation);
    childWorld.position = Vector3Sub(childWorld.position, parentWorld.position);
    childWorld.position = Vector3RotateZ(childWorld.position, -parentWorld.rotation.z);
    childWorld.position = Vector3RotateY(childWorld.position, -parentWorld.rotation.y);
    childWorld.position = Vector3RotateX(childWorld.position, -parentWorld.rotation.x);
    return childWorld;
}
inline Pose GetWorldPose(Pose parentWorld, Pose childLocal)
{
    childLocal.position = Vector3RotateX(childLocal.position, parentWorld.rotation.x);
    childLocal.position = Vector3RotateY(childLocal.position, parentWorld.rotation.y);
    childLocal.position = Vector3RotateZ(childLocal.position, parentWorld.rotation.z);
    childLocal.position = Vector3Add(childLocal.position, parentWorld.position);
    childLocal.rotation = Vector3Add(childLocal.rotation, parentWorld.rotation);
    return childLocal;
}
