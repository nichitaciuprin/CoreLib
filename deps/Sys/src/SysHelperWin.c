#include "SysHelper.h"

#include <stdint.h>
#include <process.h>
#include <time.h>

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif

#include <windef.h>
#include <winbase.h>
#include <wingdi.h>
#include <winuser.h>
#include <wincon.h>

static FILETIME idleOld = {};
static FILETIME idleNew = {};
static FILETIME userOld = {};
static FILETIME userNew = {};

static int cpu = 0;
static int cpuTimer = 0;

static long timeStep = 10;
static int endTime = 0;

uint64_t SysHelperGetPid()
{
    // printf("Process PID:%ld\n", (long)getpid());
    return (uint64_t)getpid();
}
int SysHelperGetCpuUsage()
{
    // TODO
    if (cpuTimer != 100)
    {
        cpuTimer++;
        return cpu;
    }

    cpuTimer = 0;

    FILETIME kernel = {};

    GetSystemTimes(&idleNew, &kernel, &userNew);

    // cpu = GetCpuUsageDiff(idleOld, idleNew, userOld, userNew);

    DWORD idle = idleNew.dwLowDateTime - idleOld.dwLowDateTime;
    DWORD user = userNew.dwLowDateTime - userOld.dwLowDateTime;
    DWORD all = idle + user;
    cpu = all == 0 ? 0 : user * 100 / all;

    idleOld = idleNew;
    userOld = userNew;

    return cpu;
}
long SysHelperGetTime()
{
    // TODO maybe change to QueryPerformanceCounter
    // return clock()/(CLOCKS_PER_SEC/1000);
    return clock();
}
void SysHelperGetConsolePosition(int* x, int* y)
{
    RECT rect = {};

    HWND handle = GetConsoleWindow();

    // GetClientRect(handle, &rect)
    GetWindowRect(handle, &rect);

    *x = rect.left;
    *y = rect.top;

    // TODO fix this
    *x += 7;
}
void SysHelperHalt(unsigned long milliseconds)
{
    Sleep(milliseconds);
}
void SysHelperFixedTimeStart()
{
    endTime = SysHelperGetTime() + timeStep;
}
void SysHelperFixedTimeEnd()
{
    long haltTime = endTime - SysHelperGetTime();
    if (haltTime > 0)
        SysHelperHalt(haltTime);
    // else
    //     printf("SLOW!\n");
}
