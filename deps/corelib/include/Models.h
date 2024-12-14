#pragma once

#include "BaseMath.h"

const Vector3 ModelCubeVerteces[8] =
{
    { -0.5f, -0.5f, -0.5f },
    { -0.5f, -0.5f,  0.5f },
    { -0.5f,  0.5f, -0.5f },
    { -0.5f,  0.5f,  0.5f },
    {  0.5f, -0.5f, -0.5f },
    {  0.5f, -0.5f,  0.5f },
    {  0.5f,  0.5f, -0.5f },
    {  0.5f,  0.5f,  0.5f }
};
const int ModelCubeIndecesLine[12][2] =
{
    0, 1,
    1, 5,
    5, 4,
    4, 0,
    2, 3,
    3, 7,
    7, 6,
    6, 2,
    0, 2,
    1, 3,
    5, 7,
    4, 6
};
const int ModelCubeIndecesQuad[6][4] =
{
    2, 6, 4, 0,
    6, 7, 5, 4,
    7, 3, 1, 5,
    3, 2, 0, 1,
    1, 0, 4, 5,
    3, 7, 6, 2
};
