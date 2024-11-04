const float minSpeed = 9;
const float maxSpeed = 15;
const float range_1 = 5;
const float range_2 = 5;
const float range_3 = 2;
const float rangeSquared_1 = range_1 * range_1;
const float rangeSquared_2 = range_2 * range_2;
const float rangeSquared_3 = range_3 * range_3;
const float power1 = 0.01;
const float power2 = 0.01;
const float power3 = 0.04;
const float acc = 10;

#define STATE_BOIDSCOUNT 300

typedef struct BoidCache
{
    Vector2 vec_1;
    Vector2 vec_2;
    Vector2 vec_3;
    int count_1;
    int count_2;
}
BoidCache;

typedef struct UpdateCache
{
    BoidCache boidCaches[STATE_BOIDSCOUNT];
}
UpdateCache;

typedef struct Boid
{
    Vector2 position;
    Vector2 velocity;
}
Boid;

typedef struct State
{
    Box box;
    Boid boids[STATE_BOIDSCOUNT];
}
State;

UpdateCache* updateCache;

void PrintBoid(Boid* boid)
{
    PrintVector2Hex(boid->position);
    PrintVector2Hex(boid->velocity);
}

void ClearCache()
{
    memset(updateCache, 0, sizeof(UpdateCache));
}
Vector2 TargetVelocity(Boid* boids, BoidCache* boidCaches, int boidIndex)
{
    Boid* boid = &boids[boidIndex];
    BoidCache* boidCache = &boidCaches[boidIndex];

    Vector2 result = boid->velocity;

    Vector2 vec_1 = boidCache->vec_1;
    Vector2 vec_2 = boidCache->vec_2;
    Vector2 vec_3 = boidCache->vec_3;
    int count_1 = boidCache->count_1;
    int count_2 = boidCache->count_2;

    if (count_1 != 0)
    {
        vec_1 = MyVector2Div(vec_1, count_1);
        vec_1 = MyVector2Sub(vec_1, boid->position);
    }
    if (count_2 != 0)
    {
        vec_2 = MyVector2Div(vec_2, count_2);
        vec_2 = MyVector2Sub(vec_2, boid->velocity);
    }

    vec_1 = MyVector2Mul(vec_1, power1);
    vec_2 = MyVector2Mul(vec_2, power2);
    vec_3 = MyVector2Mul(vec_3, power3);

    result = MyVector2Add(result, vec_1);
    result = MyVector2Add(result, vec_2);
    result = MyVector2Add(result, vec_3);

    result = MyVector2ClampLength(result, minSpeed, maxSpeed);

    return result;
}
void CalculatePair(Boid* boids, BoidCache* boidsCaches, int boid1Index, int boid2Index)
{
    Boid* boid1 = &boids[boid1Index];
    Boid* boid2 = &boids[boid2Index];

    BoidCache* boid1Cache = &boidsCaches[boid1Index];
    BoidCache* boid2Cache = &boidsCaches[boid2Index];

    Vector2 diff = MyVector2Sub(boid1->position, boid2->position);
    float distSquared = diff.x * diff.x + diff.y * diff.y;
    float dist = sqrtf(distSquared);

    // COHESION
    if (distSquared >= rangeSquared_1) return;

    boid1Cache->vec_1 = MyVector2Add(boid1Cache->vec_1, boid2->position); boid1Cache->count_1++;
    boid2Cache->vec_1 = MyVector2Add(boid2Cache->vec_1, boid1->position); boid2Cache->count_1++;

    // ALIGHMENT
    if (distSquared >= rangeSquared_2) return;

    boid1Cache->vec_2 = MyVector2Add(boid1Cache->vec_2, boid2->velocity); boid1Cache->count_2++;
    boid2Cache->vec_2 = MyVector2Add(boid2Cache->vec_2, boid1->velocity); boid2Cache->count_2++;

    // SEPARATION
    if (distSquared >= rangeSquared_3) return;

    float normFraction = 1.0f / dist;
    Vector2 normDiff = (Vector2) { diff.x * normFraction, diff.y * normFraction };
    float dist2 = range_3 - dist;
    normDiff = MyVector2Mul(normDiff, dist2);

    boid1Cache->vec_3 = MyVector2Add(boid1Cache->vec_3, normDiff);
    boid2Cache->vec_3 = MyVector2Add(boid2Cache->vec_3, MyVector2Negate(normDiff));
}

Boid CreateBoid(Box* box, Subgen* subgen)
{
    float randSpeed = SubgenRange(subgen, minSpeed, maxSpeed);
    Vector2 randDirection = MyVector2RandNormDir(subgen);

    Vector2 pos = RandomPointInside(subgen, box);
    Vector2 vel = MyVector2Mul(randDirection, randSpeed);

    Boid boid;
    boid.position = pos;
    boid.velocity = vel;

    return boid;
}
void UpdateBoids(Boid* boids, int boidsLength, Box* box, float deltaTime)
{
    ClearCache();

    BoidCache* boidCaches = updateCache->boidCaches;

    // iterating unique pairs
    for (int i = 0;   i < boidsLength; i++)
    for (int j = i+1; j < boidsLength; j++)
        CalculatePair(boids, boidCaches, i, j);

    for (int i = 0; i < boidsLength; i++)
    {
        Boid* boid = &boids[i];

        Vector2 targetVelocity = TargetVelocity(boids, boidCaches, i);
        Vector2 oldVelocity = boid->velocity;
        Vector2 newVelocity = MyVector2MoveTowards(boid->velocity, targetVelocity, acc * deltaTime);
        boid->position = MyVector2UpdatePositionAdvanced(boid->position, oldVelocity, newVelocity, deltaTime);
        boid->position = WrapAround(box, boid->position);
        boid->velocity = newVelocity;
    }
}

State* CreateState()
{
    State* state = new State;
    updateCache = new UpdateCache;

    Subgen subgen = SubgenCreate(0);

    state->box.p0 = (Vector2){ 0, 0 };
    state->box.p1 = (Vector2){ 50, 50 };

	for (int i = 0; i < STATE_BOIDSCOUNT; i++)
		state->boids[i] = CreateBoid(&state->box, &subgen);

    return state;
}
void UpdateState(State* state, float deltaTime)
{
    UpdateBoids(state->boids, STATE_BOIDSCOUNT, &state->box, deltaTime);
}
void DestroyState(State* state)
{
    delete state;
    delete updateCache;
}
