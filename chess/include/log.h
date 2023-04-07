#pragma once
#include <stdio.h>
#include <time.h>

extern void log_init();
extern void log_quit();
extern void log_info(const char* message);
extern void log_warn(const char* message);
extern void log_error(const char* message);
extern char* get_time();

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define DEBUG_MODE

#ifdef DEBUG_MODE 

#define LOG_INFO(x)  log_info(x)
#define LOG_WARN(x)  log_warn(x)
#define LOG_ERROR(x) log_error(x)

#define COLOR_RED(x)	ANSI_COLOR_RED		x ANSI_COLOR_RESET
#define COLOR_GREEN(x)	ANSI_COLOR_GREEN	x ANSI_COLOR_RESET
#define COLOR_YELLOW(x) ANSI_COLOR_YELLOW	x ANSI_COLOR_RESET

#else

#define LOG_INFO(x) 
#define LOG_WARN(x)
#define LOG_ERROR(x) 

#define COLOR_RED(x)
#define COLOR_GREEN(x)
#define COLOR_YELLOW(x) 

#endif


