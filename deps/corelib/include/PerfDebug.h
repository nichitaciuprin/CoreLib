#pragma once

#include "stdio.h"
#include "SysHelper.h"

int PrintAvgPerf_TimeStart = 0;
int PrintAvgPerf_TimeEnd = 0;
int PrintAvgPerf_Count = 0;
int PrintAvgPerf_CountMax = 100;
int PrintAvgPerf_Time = 0;
void PrintAvgPerf_Start()
{
    PrintAvgPerf_TimeStart = SysHelperGetTime();
}
void PrintAvgPerf_End()
{
    PrintAvgPerf_TimeEnd = SysHelperGetTime();

    PrintAvgPerf_Count++;
    PrintAvgPerf_Time += PrintAvgPerf_TimeEnd - PrintAvgPerf_TimeStart;

    if (PrintAvgPerf_Count != PrintAvgPerf_CountMax) return;

    int result = PrintAvgPerf_Time /= PrintAvgPerf_CountMax;

    PrintAvgPerf_Count = 0;
    PrintAvgPerf_Time = 0;

    printf("PrintAvgPerf: %i\n", result);
}
