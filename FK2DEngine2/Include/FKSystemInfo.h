/**
*	created:		2013-4-28   2:42
*	filename: 		FKSystemInfo
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#define WIN32_LEAN_AND_MEAN
//------------------------------------------------------------------------
// 版本号
#define FK_SYSTEMINFO_VERSION		1.01
//------------------------------------------------------------------------
#define SI_BYTES		1
#define SI_KILOBYTES	1024
#define SI_MEGABYTES	(1024 * 1024)
//------------------------------------------------------------------------
// OS名称定义
#define SI_OS_NT		0
#define SI_OS_2K		1
#define SI_OS_XP		2
#define SI_OS_DOTNET	3
#define SI_OS_95		4
#define SI_OS_98		5
#define SI_OS_ME		6
#define SI_OS_LINUX		7
#define SI_OS_FREEBSD	8
#define SI_OS_UNKNOWN	9
//------------------------------------------------------------------------
// OS版本信息
typedef struct
{
	int major;
	int minor;
	int revision;
}siVersion;
//------------------------------------------------------------------------
// CPU类型信息
typedef struct
{
	char hasMMX;
	char hasSSE;
	char hasSSE2;
	char has3dNow;
	char idString[16];
}siCpu;
//------------------------------------------------------------------------
// OS名称表
extern char* siOsNames[];
//------------------------------------------------------------------------
unsigned int	siGetCpuSpeed(void);
siCpu			siGetCpuType(void);
int				siGetPhysicalMem(int units);
int				siGetAvailableMem(int units);
siVersion		siGetOsVersion(void);
char*			siGetOsName(void);
unsigned int	siGetOsType(void);
const char*		siGetLastError(void);
//------------------------------------------------------------------------