#include "cpu_memory.h"

#include <Windows.h>
#include <QString>
#include <iostream>
#include <intrin.h>

static float CalculateCPULoad(unsigned long long idleTicks, unsigned long long totalTicks)
{
    static unsigned long long _previousTotalTicks = 0;
    static unsigned long long _previousIdleTicks = 0;

    unsigned long long totalTicksSinceLastTime = totalTicks - _previousTotalTicks;
    unsigned long long idleTicksSinceLastTime = idleTicks - _previousIdleTicks;

    float ret = 1.0f - ((totalTicksSinceLastTime > 0) ? ((float)idleTicksSinceLastTime) / totalTicksSinceLastTime : 0);

    _previousTotalTicks = totalTicks;
    _previousIdleTicks = idleTicks;
    return ret;
}

static unsigned long long FileTimeToInt64(const FILETIME & ft) { return (((unsigned long long)(ft.dwHighDateTime)) << 32) | ((unsigned long long)ft.dwLowDateTime); }

// Returns 1.0f for "CPU fully pinned", 0.0f for "CPU idle", or somewhere in between
// You'll need to call this at regular intervals, since it measures the load between
// the previous call and the current one.  Returns -1.0 on error.
float GetCPULoad()
{
    FILETIME idleTime, kernelTime, userTime;
    return GetSystemTimes(&idleTime, &kernelTime, &userTime) ? CalculateCPULoad(FileTimeToInt64(idleTime), FileTimeToInt64(kernelTime) + FileTimeToInt64(userTime)) : -1.0f;
}

MEMORYSTATUSEX getMemoryState()
{
    MEMORYSTATUSEX statex;

    statex.dwLength = sizeof (statex);

    GlobalMemoryStatusEx (&statex);

    return statex;
 // _tprintf (TEXT("There is  %*ld percent of memory in use.\n"),WIDTH, statex.dwMemoryLoad);
 // _tprintf (TEXT("There are %*I64d total Mbytes of physical memory.\n"),WIDTH,statex.ullTotalPhys/DIV);
 // _tprintf (TEXT("There are %*I64d free Mbytes of physical memory.\n"),WIDTH, statex.ullAvailPhys/DIV);
 // _tprintf (TEXT("There are %*I64d total Mbytes of paging file.\n"),WIDTH, statex.ullTotalPageFile/DIV);
 // _tprintf (TEXT("There are %*I64d free Mbytes of paging file.\n"),WIDTH, statex.ullAvailPageFile/DIV);
 // _tprintf (TEXT("There are %*I64d total Mbytes of virtual memory.\n"),WIDTH, statex.ullTotalVirtual/DIV);
 // _tprintf (TEXT("There are %*I64d free Mbytes of virtual memory.\n"),WIDTH, statex.ullAvailVirtual/DIV);
 // _tprintf (TEXT("There are %*I64d free Mbytes of extended memory.\n"),WIDTH, statex.ullAvailExtendedVirtual/DIV);
}

using namespace std;

QString getCPUName()
{
    // Get extended ids.
    int CPUInfo[4] = {-1};
    __cpuid(CPUInfo, 0x80000000);
    unsigned int nExIds = CPUInfo[0];

    // Get the information associated with each extended ID.
    char CPUBrandString[0x40] = { 0 };
    for( unsigned int i=0x80000000; i<=nExIds; ++i)
    {
        __cpuid(CPUInfo, i);

        // Interpret CPU brand string and cache information.
        if  (i == 0x80000002)
        {
            memcpy( CPUBrandString,
            CPUInfo,
            sizeof(CPUInfo));
        }
        else if( i == 0x80000003 )
        {
            memcpy( CPUBrandString + 16,
            CPUInfo,
            sizeof(CPUInfo));
        }
        else if( i == 0x80000004 )
        {
            memcpy(CPUBrandString + 32, CPUInfo, sizeof(CPUInfo));
        }
}

    return CPUBrandString;
}

int getCpuCoreCount()
{
    SYSTEM_INFO siSysInfo;

        // Copy the hardware information to the SYSTEM_INFO structure.

    GetSystemInfo(&siSysInfo);

        // Display the contents of the SYSTEM_INFO structure.

    return siSysInfo.dwNumberOfProcessors;

    /*    printf("Hardware information: \n");
        printf("  OEM ID: %u\n", siSysInfo.dwOemId);
        printf("  Number of processors: %u\n",
            siSysInfo.dwNumberOfProcessors);
        printf("  Page size: %u\n", siSysInfo.dwPageSize);
        printf("  Processor type: %u\n", siSysInfo.dwProcessorType);
        printf("  Minimum application address: %lx\n",
            siSysInfo.lpMinimumApplicationAddress);
        printf("  Maximum application address: %lx\n",
            siSysInfo.lpMaximumApplicationAddress);
        printf("  Active processor mask: %u\n",
            siSysInfo.dwActiveProcessorMask);*/
}
