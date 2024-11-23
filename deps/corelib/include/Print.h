
#pragma once

#include "Helper.h"
#include <stdio.h>

void PrintFloat(float f)
{
    if (f > 0)       printf("+");
    else if (f == 0) printf(" ");
    printf("%.2f", f);
}
void PrintFloatHex(float f)
{
    // unsigned int ui;
    // memcpy(&ui, &f, sizeof (ui));
    // printf("%X", ui);
}
void PrintVector2(Vector2 v)
{
    printf("<");
    PrintFloat(v.x); printf(", ");
    PrintFloat(v.y);
    printf(">");
}
void PrintVector3(Vector3 v)
{
    printf("<");
    PrintFloat(v.x); printf(", ");
    PrintFloat(v.y); printf(", ");
    PrintFloat(v.z);
    printf(">");
}
void PrintVector4(Vector4 v)
{
    printf("<");
    PrintFloat(v.x); printf(", ");
    PrintFloat(v.y); printf(", ");
    PrintFloat(v.z); printf(", ");
    PrintFloat(v.w);
    printf(">");
}
void PrintVector2Hex(Vector2 v)
{
    PrintFloatHex(v.x);
    PrintFloatHex(v.y);
}
void PrintMatrix(Matrix m)
{
    Vector4 row0 = { m.m[0][0], m.m[0][1], m.m[0][2], m.m[0][3] };
    Vector4 row1 = { m.m[1][0], m.m[1][1], m.m[1][2], m.m[1][3] };
    Vector4 row2 = { m.m[2][0], m.m[2][1], m.m[2][2], m.m[2][3] };
    Vector4 row3 = { m.m[3][0], m.m[3][1], m.m[3][2], m.m[3][3] };

    #define PRINT(ROW)                    \
    {                                     \
        printf("[");                      \
        PrintFloat(ROW.x); printf(", ");  \
        PrintFloat(ROW.y); printf(", ");  \
        PrintFloat(ROW.z); printf(", ");  \
        PrintFloat(ROW.w);                \
        printf("]");                      \
        printf("\n");                     \
    }                                     \

    PRINT(row0);
    PRINT(row1);
    PRINT(row2);
    PRINT(row3);

    #undef PRINT
}
