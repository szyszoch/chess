#pragma once
#include <stdio.h>
#include <time.h>

typedef struct Log Log;

extern void Log_Init();
extern void Log_Quit();
extern void Log_Info(const char* message);
extern void Log_Warn(const char* message);
extern void Log_Error(const char* message);
extern char* Log_GetTime();

#define DEBUG_MODE

#ifdef DEBUG_MODE 

#define LOG_INFO(x)  Log_Info(x)
#define LOG_WARN(x)  Log_Warn(x)
#define LOG_ERROR(x) Log_Error(x)

#else

#define INFO(x) 
#define WARN(x)
#define ERROR(x)

#endif


