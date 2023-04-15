#pragma once
#include <SDL.h>

#define DEBUG

#ifdef DEBUG

#define LOG_DEBUG(x, ...) SDL_LogDebug(x, ##__VA_ARGS__)
#define LOG_VERBOSE(x, ...) SDL_LogVerbose(x, ##__VA_ARGS__)
#define LOG_INFO(x, ...) SDL_LogInfo(x, ##__VA_ARGS__)
#define LOG_WARN(x, ...) SDL_LogWarn(x, ##__VA_ARGS__)
#define LOG_ERROR(x, ...) SDL_LogError(x, ##__VA_ARGS__)
#define LOG_CRITICAL(x, ...) SDL_LogCritical(x, ##__VA_ARGS__)

#else

#define LOG_DEBUG(x,y)
#define LOG_VERBOSE(x,y)
#define LOG_INFO(x,y)
#define LOG_WARN(x,y)
#define LOG_ERROR(x,y)

#endif
