#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT 500
#define WINDOW_SCALE 10

void Ray_CreateWindow()
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Window1");
	rlDisableBackfaceCulling();
}
void Ray_PollInputEvents()
{
    PollInputEvents();
}
void Ray_CloseWindow()
{
    CloseWindow();
}
Vector2 ToWindowSpace(Vector2 v)
{
    v = MyVector2Mul(v, WINDOW_SCALE);
    v.y = WINDOW_HEIGHT - v.y;
    return (Vector2){ v.x, v.y };
}

void RenderRectangleLines(int x, int y, int width, int height, Color color)
{
    x      *= WINDOW_SCALE;
    y      *= WINDOW_SCALE;
    width  *= WINDOW_SCALE;
    height *= WINDOW_SCALE;

    y = WINDOW_HEIGHT - y;
    y -= height;

    DrawRectangleLines(x, y, width, height, color);
}
void RenderTriangle(Vector2 v1, Vector2 v2, Vector2 v3, Color color)
{
    Vector2 rv1 = ToWindowSpace(v1);
    Vector2 rv2 = ToWindowSpace(v2);
    Vector2 rv3 = ToWindowSpace(v3);
    DrawTriangle(rv1, rv2, rv3, color);
}
void RenderBox(Box* box)
{
    Vector2 position = (Vector2) { BoxMinX(box), BoxMinY(box) };
    Vector2 size = BoxSize(box);

    DrawRectangleLines(position.x, position.y, size.x, size.y, DARKGREEN);
}

void RenderBoid(Boid* boid, Color color)
{
    Vector2 v1 = {  0.00f,  0.00f };
    Vector2 v2 = { -0.25f, -0.25f };
    Vector2 v3 = {  0.00f,  0.50f };
    Vector2 v4 = {  0.25f, -0.25f };

    float angle = MyVector2Angle(boid->velocity);

    v1 = MyVector2Rotate(v1, angle);
    v2 = MyVector2Rotate(v2, angle);
    v3 = MyVector2Rotate(v3, angle);
    v4 = MyVector2Rotate(v4, angle);

    v1 = MyVector2Add(boid->position, v1);
    v2 = MyVector2Add(boid->position, v2);
    v3 = MyVector2Add(boid->position, v3);
    v4 = MyVector2Add(boid->position, v4);

    RenderTriangle(v1, v2, v3, color);
    RenderTriangle(v1, v4, v3, color);
}
void RenderState(State* state)
{
    BeginDrawing();

    ClearBackground(BLACK);
    DrawFPS(0, 0);

    if (STATE_BOIDSCOUNT > 0)
    {
        RenderBoid(&state->boids[0], RED);
        for (int i = 1; i < STATE_BOIDSCOUNT; i++)
            RenderBoid(&state->boids[i], WHITE);
    }

    EndDrawing();
}
