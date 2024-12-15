#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

uint64_t SysHelperGetPid();
int SysHelperGetCpuUsage();
long SysHelperGetTime();
void SysHelperGetConsolePosition(int* x, int* y);
void SysHelperHalt(unsigned long milliseconds);
void SysHelperFixedTimeStart();
void SysHelperFixedTimeEnd();

#ifdef __cplusplus
}
#endif
