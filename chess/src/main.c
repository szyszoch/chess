
#include "log.h"

int main(int argc, char* args[]) {
	Log_Init();
	INFO("test");
	WARN("test");
	ERROR("test");
	Log_Quit();
	return 0;
}