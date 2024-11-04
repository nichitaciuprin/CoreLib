#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <memory.h>
#include <time.h>
#include <math.h>

#include <iostream>
#include <algorithm>
#include <string>
#include <memory>
#include <vector>
#include <array>
#include <set>
#include <unordered_set>
#include <forward_list>

using namespace std;

#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"

#include "ModelInfo.h"
#include "Model1.h"

float MathAbs(float value)
{
    return fabsf(value);
}
float MathPingPong(float value, float length)
{
    value = MathAbs(value);
    int whole = (int)(value/length);
    float rem = fmodf(value, length);
    return whole % 2 == 0 ? rem : length-rem;
}
Vector3 GetVertexTranslated(int vertexIndex, Matrix bones[])
{
    int offset = vertexIndex*7;

    float x       = vertex[offset+0];
    float y       = vertex[offset+1];
    float z       = vertex[offset+2];
    int boneId1   = vertex[offset+3];
    int boneId2   = vertex[offset+4];
    float weight1 = vertex[offset+5];
    float weight2 = vertex[offset+6];

    Vector3 result = {};

    Matrix mInit =
    {
        1,0,0,x,
        0,1,0,y,
        0,0,1,z,
        0,0,0,1,
    };

    int boneId;
    float weight;

    boneId = boneId1;
    weight = weight1;
    if (boneId != -1)
    {
        Matrix m = mInit;
        m = MatrixMultiply(m, bones[boneId]);
        result.x += m.m12 * weight;
        result.y += m.m13 * weight;
        result.z += m.m14 * weight;
    }

    boneId = boneId2;
    weight = weight2;
    if (boneId != -1)
    {
        Matrix m = mInit;
        m = MatrixMultiply(m, bones[boneId]);
        result.x += m.m12 * weight;
        result.y += m.m13 * weight;
        result.z += m.m14 * weight;
    }

    return result;
}
Vector3 GetVertexTranslated2(ModelInfo modelInfo, int vertexIndex, Matrix bones[])
{
    auto vertexInfo = modelInfo.vertexInfos[vertexIndex];

    Vector3 result = {};

    for (size_t i = 0; i < 2; i++)
    {
        int boneId = vertexInfo.boneIds[i];
        float weight = vertexInfo.weights[i];

        if (boneId == -1) break;

        Matrix m =
        {
            1,0,0,vertexInfo.position.x,
            0,1,0,vertexInfo.position.y,
            0,0,1,vertexInfo.position.z,
            0,0,0,1,
        };

        m = MatrixMultiply(m, bones[boneId]);
        result.x += m.m12 * weight;
        result.y += m.m13 * weight;
        result.z += m.m14 * weight;
    }

    return result;
}

void MoveBones(Matrix bones[], Matrix offsets[])
{
    for (size_t parent = 0; parent < 3; parent++)
    {
        Matrix offset = offsets[parent];
        Matrix m = bones[parent];
        Matrix mi = MatrixInvert(m);

        bones[parent] = MatrixMultiply(bones[parent], mi);
        bones[parent] = MatrixMultiply(bones[parent], offset);
        bones[parent] = MatrixMultiply(bones[parent], m);

        size_t childCount = 2;

        for (size_t i = 0; i < childCount; i++)
        {
            auto child = parentsChildren[parent*2+i];
            if (child == -1) continue;

            bones[child] = MatrixMultiply(bones[child], mi);
            bones[child] = MatrixMultiply(bones[child], offset);
            bones[child] = MatrixMultiply(bones[child], m);
        }
    }
}
void MoveBones2(int boneCount, BoneData boneData[], Matrix offsets[], Matrix result[])
{
    for (int i = 0; i < boneCount; i++)
        result[i] = boneData[i].init;

    for (int parent = 0; parent < boneCount; parent++)
    {
        auto boneInfo = boneData[parent];
        Matrix offset = offsets[parent];
        Matrix m = boneInfo.init;
        Matrix mi = boneInfo.initInvert;

        result[parent] = MatrixMultiply(result[parent], mi);
        result[parent] = MatrixMultiply(result[parent], offset);
        result[parent] = MatrixMultiply(result[parent], m);

        int childCount = 2;

        for (int i = 0; i < childCount; i++)
        {
            auto child = parentsChildren[parent*2+i];
            if (child == -1) continue;

            result[child] = MatrixMultiply(result[child], mi);
            result[child] = MatrixMultiply(result[child], offset);
            result[child] = MatrixMultiply(result[child], m);
        }
    }
}

void DrawModel(Matrix bones[])
{
    rlSetTexture(texture.id);

    rlBegin(RL_QUADS);
    {
        Color color = WHITE;

        rlColor4ub(color.r, color.g, color.b, color.a);

        for (int i = 0; i < 16; i++)
        {
            int offset = i*4;

            auto v0 = GetVertexTranslated(modelIndeces[offset+0], bones);
            auto v1 = GetVertexTranslated(modelIndeces[offset+1], bones);
            auto v2 = GetVertexTranslated(modelIndeces[offset+2], bones);
            auto v3 = GetVertexTranslated(modelIndeces[offset+3], bones);

            rlVertex3f(v0.x, v0.y, v0.z); rlTexCoord2f(0, 0);
            rlVertex3f(v1.x, v1.y, v1.z); rlTexCoord2f(1, 0);
            rlVertex3f(v2.x, v2.y, v2.z); rlTexCoord2f(1, 1);
            rlVertex3f(v3.x, v3.y, v3.z); rlTexCoord2f(0, 1);
        }
    }
    rlEnd();

    rlSetTexture(0);
    DrawGrid(10, 1.0f);
}
void DrawModel2(ModelInfo modelInfo, Matrix bones[])
{
    rlSetTexture(texture.id);

    rlBegin(RL_QUADS);
    {
        Color color = WHITE;

        rlColor4ub(color.r, color.g, color.b, color.a);

        for (int i = 0; i < modelInfo.vertexCount; i++)
        {
            auto v = GetVertexTranslated2(modelInfo, i, bones);
            rlVertex3f(v.x, v.y, v.z);
            rlTexCoord2f(0, 0);
        }
    }
    rlEnd();

    rlSetTexture(0);
    DrawGrid(10, 1.0f);
}
int main(void)
{
    InitWindow(800, 450, "skining test");

    Model1Init();

    Camera camera = { 0 };
    camera.position = { 0.0f, 4.0f, 15.0f };
    camera.target = camera.position;
    camera.target.z -= 1;
    camera.up = { 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        UpdateCamera(&camera, CAMERA_FREE);

        BeginDrawing();
        {
            ClearBackground(RAYWHITE);

            BeginMode3D(camera);
            {
                DrawGrid(10, 1);

                Matrix bone0 = MatrixIdentity();
                Matrix bone1 = MatrixIdentity();
                Matrix bone2 = MatrixIdentity();

                {
                    float time = GetTime();
                    float value  = (MathPingPong(time/2, 2) - 1) / 1.4f;
                    float value2 = (MathPingPong(time*10  , 2) - 1) / 1.4f;

                    // bone0 = MatrixRotateZ(DEG2RAD * 90);
                    bone0 = MatrixRotateZ(value);
                    bone1 = MatrixRotateZ(value2);
                    // bone1 = MatrixTranslate(sinf(time)*1.3f, cosf(time)*1.3f, 0);
                    // bone1 = MatrixTranslate(0, 10, 0);
                }

                Matrix bones[3] =
                {
                    bonesInit[0],
                    bonesInit[1],
                    bonesInit[2],
                };

                Matrix offsets[3] = { bone0, bone1, bone2 };

                MoveBones(bones, offsets);

                // // debug draw
                // {
                //     auto m1 = bones[0];
                //     auto m2 = bones[1];
                //     auto m3 = bones[2];
                //     Vector3 v1 = { m1.m12, m1.m13, m1.m14 };
                //     Vector3 v2 = { m2.m12, m2.m13, m2.m14 };
                //     Vector3 v3 = { m3.m12, m3.m13, m3.m14 };
                //     DrawLine3D(v1, v2, RED);
                //     DrawLine3D(v2, v3, GREEN);
                // }

                for (size_t i = 0; i < 3; i++)
                    offsets[i] = MatrixMultiply(bonesInitInvert[i], bones[i]);

                DrawModel(offsets);
            }
            EndMode3D();
        }
        EndDrawing();
    }

    UnloadTexture(texture);
    CloseWindow();

    return 0;
}
