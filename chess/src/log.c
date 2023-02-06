#include "log.h"

typedef struct Log {
	FILE* file;
	const char* file_name;
} Log;

Log logger;

void Log_Init() {
	logger.file_name = "log.txt";
	logger.file = fopen(logger.file_name, "w");
}

void Log_Quit() {
	fclose(logger.file);
}

void Log_Info(const char* message) {
	// console
	printf("[%s][\033[38;2;0;255;0mINFO\033[39m]: %s\n", Log_GetTime(),message);
	// file
	fprintf(logger.file, "[INFO]: ");
	fprintf(logger.file, message);
	fprintf(logger.file, "\n");
}

void Log_Warn(const char* message) {
	// console
	printf("[%s][\033[38;2;255;255;0mWARNING\033[39m]: %s\n", Log_GetTime(), message);
	// file
	fprintf(logger.file, "[WARN]: ");
	fprintf(logger.file, message);
	fprintf(logger.file, "\n");
}

void Log_Error(const char* message) {
	// console
	printf("[%s][\033[38;2;255;0;0mERROR\033[39m]: %s\n", Log_GetTime(), message);
	// file
	fprintf(logger.file, "[ERROR]: ");
	fprintf(logger.file, message);
	fprintf(logger.file, "\n");
}

char* Log_GetTime() {
	time_t current_time = time(NULL);
	struct tm* time_info = localtime(&current_time);
	static char time_string[9];
	strftime(time_string, sizeof(time_string), "%T", time_info);
	return time_string;
}
