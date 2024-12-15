#include "SysHelper.h"

#include <stdint.h>
#include <math.h>
#include <time.h>
#include <errno.h>

static bool setInitSpec = true;
static struct timespec initSpec;

static long timeStep = 10;
static int endTime = 0;

// static long clock2()
// {
//     return clock()/(CLOCKS_PER_SEC/1000);
// }

uint64_t SysHelperGetPid()
{
    // #error SysHelperGetPid not implemented
    return 0;
}
int SysHelperGetCpuUsage()
{
    // #error GetCpuUsage not implemented
    return 100;
}
long SysHelperGetTime()
{
    if (setInitSpec)
    {
        setInitSpec = false;
        clock_gettime(CLOCK_REALTIME, &initSpec);
        return 0;
    }

    struct timespec spec;

    clock_gettime(CLOCK_REALTIME, &spec);

    unsigned long ms1 = initSpec.tv_sec * 1000 + round(initSpec.tv_nsec / 1.0e6);
    unsigned long ms2 =     spec.tv_sec * 1000 + round(    spec.tv_nsec / 1.0e6);

    long ms = ms2 - ms1;

    return ms;
}
void SysHelperGetConsolePosition(int* x, int* y)
{
    // #error SysHelperGetConsolePosition not implemented
    *x = 0;
    *y = 0;
}
void SysHelperHalt(unsigned long milliseconds)
{
    // TODO review

    struct timespec ts;
    int res;

    if (milliseconds < 0)
        errno = EINVAL;

    ts.tv_sec = milliseconds / 1000;
    ts.tv_nsec = (milliseconds % 1000) * 1000000;

    do
    {
        res = nanosleep(&ts, &ts);
    }
    while (res && errno == EINTR);

    // usleep(milliseconds * 1000);
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
