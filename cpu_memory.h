#ifndef CPU_H
#define CPU_H

#include <Windows.h>
#include <Qstring>

#define DIV 1048576

float GetCPULoad();
MEMORYSTATUSEX getMemoryState();
QString getCPUName();
int getCpuCoreCount();

#endif // CPU_H
