#include "log.h"

typedef struct Log {
	FILE* file;
	const char* file_name;
} Log;

Log logger;

void log_init() {
	logger.file_name = "log.txt";
	logger.file = fopen(logger.file_name, "w");
}

void log_quit() {
	fclose(logger.file);
}

void log_info(const char* message) 
{
	// console
	printf("[%s]", get_time());
	printf("["COLOR_GREEN("INFO")"]: ");
	printf("%s\n", message);
	// file
	fprintf(logger.file, "[%s]", get_time());
	fprintf(logger.file, "[INFO]: ");
	fprintf(logger.file, message);
	fprintf(logger.file, "\n");
}

void log_warn(const char* message) 
{
	// console
	printf("[%s]", get_time());
	printf("["COLOR_YELLOW("WARN")"]: ");
	printf("%s\n", message);
	// file
	fprintf(logger.file, "[%s]", get_time());
	fprintf(logger.file, "[WARN]: ");
	fprintf(logger.file, message);
	fprintf(logger.file, "\n");
}

void log_error(const char* message) 
{
	// console
	printf("[%s]", get_time());
	printf("["COLOR_RED("ERROR")"]: ");
	printf("%s\n", message);
	// file
	fprintf(logger.file, "[%s]", get_time());
	fprintf(logger.file, "[ERROR]: ");
	fprintf(logger.file, message);
	fprintf(logger.file, "\n");
}

char* get_time() 
{
	time_t current_time = time(NULL);
	struct tm* time_info = localtime(&current_time);
	static char time_string[9];
	strftime(time_string, sizeof(time_string), "%T", time_info);
	return time_string;
}
