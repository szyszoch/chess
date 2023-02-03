#include "log.h"

typedef struct Log {
	FILE* file;
	const char* file_name;
} Log;

Log log;

void Log_Init() {
	log.file_name = "log.txt";
	log.file = fopen(log.file_name, "w");
}

void Log_Quit() {
	fclose(log.file);
}

void Log_Info(const char* message) {
	// console
	printf("[%s][\033[38;2;0;255;0mINFO\033[39m]: %s\n", Log_GetTime(),message);
	// file
	fprintf(log.file, "[INFO]: ");
	fprintf(log.file, message);
	fprintf(log.file, "\n");
}

void Log_Warn(const char* message) {
	// console
	printf("[%s][\033[38;2;255;255;0mWARNING\033[39m]: %s\n", Log_GetTime(), message);
	// file
	fprintf(log.file, "[WARN]: ");
	fprintf(log.file, message);
	fprintf(log.file, "\n");
}

void Log_Error(const char* message) {
	// console
	printf("[%s][\033[38;2;255;0;0mERROR\033[39m]: %s\n", Log_GetTime(), message);
	// file
	fprintf(log.file, "[ERROR]: ");
	fprintf(log.file, message);
	fprintf(log.file, "\n");
}

char* Log_GetTime() {
	time_t current_time = time(NULL);
	struct tm* time_info = localtime(&current_time);
	static char time_string[9];
	strftime(time_string, sizeof(time_string), "%T", time_info);
	return time_string;
}
