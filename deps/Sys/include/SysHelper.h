#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

uint64_t GetPid();
int GetCpuUsage();
long GetTime();
void GetConsolePosition(int* x, int* y);
void Halt(unsigned long milliseconds);
void FixedTimeStart();
void FixedTimeEnd();

#ifdef __cplusplus
}
#endif
