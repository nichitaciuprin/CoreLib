typedef struct Box
{
    Vector2 p0;
    Vector2 p1;
}
Box;

float MathClamp(float value, float min, float max)
{
    if (value < min) { return min; }
    if (value > max) { return max; }
                       return value;
}
float MathSign(float value)
{
    if (value > 0) { return  1; }
    if (value < 0) { return -1; }
                     return  0;
}
float MathAbs(float value)
{
    return fabsf(value);
}
float MathSqrt(float value)
{
    return sqrtf(value);
}

void PrintFloatHex(float f)
{
    unsigned int ui;
    memcpy(&ui, &f, sizeof (ui));
    printf("%X", ui);
}
void PrintVector2Hex(Vector2 v)
{
    PrintFloatHex(v.x);
    PrintFloatHex(v.y);
}

bool MyVector2IsZero(Vector2 v1)
{
    return v1.x == 0 && v1.y == 0;
}
bool MyVector2Equal(Vector2 v1, Vector2 v2)
{
    return v1.x == v2.x && v1.y == v2.y;
}
Vector2 MyVector2Zero()
{
    return (Vector2) { 0.0f, 0.0f };
}
Vector2 MyVector2Add(Vector2 v1, Vector2 v2)
{
    return (Vector2) { v1.x + v2.x, v1.y + v2.y };
}
Vector2 MyVector2Sub(Vector2 v1, Vector2 v2)
{
    return (Vector2) { v1.x - v2.x, v1.y - v2.y };
}
Vector2 MyVector2Mul(Vector2 v1, float value)
{
    return (Vector2) { v1.x * value, v1.y * value };
}
Vector2 MyVector2Div(Vector2 v1, float value)
{
    return (Vector2) { v1.x / value, v1.y / value };
}
Vector2 MyVector2Abs(Vector2 v1)
{
    return (Vector2) { fabs(v1.x), fabs(v1.y) };
}
Vector2 MyVector2Negate(Vector2 v1)
{
    return (Vector2) { -v1.x, -v1.y };
}
float MyVector2Length(Vector2 v)
{
    float distSquared = v.x * v.x + v.y * v.y;
    float dist = sqrtf(distSquared);
    return dist;
}
float MyVector2LengthSquared(Vector2 v)
{
    float distSquared = v.x * v.x + v.y * v.y;
    return distSquared;
}
float MyVector2Angle(Vector2 v)
{
    // v ( 0, 1) =  0.000000
    // v ( 1, 0) = -1.570796
    // v ( 0,-1) = -3.141593
    // v (-1, 0) =  1.570796
    return MyVector2IsZero(v) ? 0 : atan2f(v.y, v.x) - M_PI_2;
}
float MyVector2Distance(Vector2 v1, Vector2 v2)
{
    Vector2 diff = MyVector2Sub(v1, v2);
    return MyVector2Length(diff);
}
Vector2 MyVector2Normalized(Vector2 v)
{
    float dist = MyVector2Length(v);
    float t = 1.0f / dist;
    return (Vector2) { v.x * t, v.y * t };
}
Vector2 MyVector2RandNormDir(Subgen* subgen)
{
    float x = SubgenFractionSigned(subgen);
    float y = SubgenFractionSigned(subgen);
    Vector2 result = { x, y };
    return MyVector2Normalized(result);
}
Vector2 MyVector2ClampLength(Vector2 v1, float min, float max)
{
    float length = MyVector2Length(v1);
    if (length > max) return MyVector2Mul(v1, (max / length));
    if (length < min) return MyVector2Mul(v1, (min / length));
    return v1;
}
Vector2 MyVector2Rotate(Vector2 v, float angle)
{
    Vector2 result = MyVector2Zero();
    float cosres = cosf(angle);
    float sinres = sinf(angle);
    result.x = v.x * cosres - v.y * sinres;
    result.y = v.x * sinres + v.y * cosres;
    return result;
}
Vector2 MyVector2MoveTowards(Vector2 fromVec, Vector2 toVec, float delta)
{
    if (MyVector2Equal(fromVec, toVec)) return fromVec;
    Vector2 diff = MyVector2Sub(toVec, fromVec);
    float dist = MyVector2Length(diff);
    if (dist <= delta) return toVec;
    Vector2 dir = MyVector2Normalized(diff);
    Vector2 moveVec = MyVector2Mul(dir, delta);
    return MyVector2Add(fromVec, moveVec);
}
Vector2 MyVector2Snap(Vector2 a, Vector2 b, float range)
{
    return MyVector2Distance(a,b) > range ? a : b;
}
Vector2 MyVector2UpdatePositionSimple(Vector2 position, Vector2 velocity, float deltaTime)
{
    // result = position + velocity * deltaTime
    Vector2 result = velocity;
    result = MyVector2Mul(result, deltaTime);
    result = MyVector2Add(result, position);
    return result;
}
Vector2 MyVector2UpdatePositionAdvanced(Vector2 position, Vector2 oldVelocity, Vector2 newVelocity, float deltaTime)
{
    // result = position + (oldVelocity + velocityNew) / 2 * deltaTime
    Vector2 result = oldVelocity;
    result = MyVector2Add(result, newVelocity);
    result = MyVector2Div(result, 2);
    result = MyVector2Mul(result, deltaTime);
    result = MyVector2Add(result, position);
    return result;
}

float BoxMinX(Box* box)
{
    return fminf(box->p0.x, box->p1.x);
}
float BoxMinY(Box* box)
{
    return fminf(box->p0.y, box->p1.y);
}
float BoxMaxX(Box* box)
{
    return fmaxf(box->p0.x, box->p1.x);
}
float BoxMaxY(Box* box)
{
    return fmaxf(box->p0.y, box->p1.y);
}
Vector2 BoxSize(Box* box)
{
    Vector2 diff = MyVector2Sub(box->p0, box->p1);
    return MyVector2Abs(diff);
}

Vector2 RandomPointInside(Subgen* subgen, Box* box)
{
    float x = SubgenRange(subgen, BoxMinX(box), BoxMaxX(box) );
    float y = SubgenRange(subgen, BoxMinY(box), BoxMaxY(box) );
    return (Vector2) { x, y };
}
Vector2 BoundWrapAround(Box* box, Vector2 point)
{
    Vector2 size = BoxSize(box);
    if      (point.x < BoxMinX(box)) point.x += size.x;
    else if (point.x > BoxMaxX(box)) point.x -= size.x;
    if      (point.y < BoxMinY(box)) point.y += size.y;
    else if (point.y > BoxMaxY(box)) point.y -= size.y;
    return point;
}
