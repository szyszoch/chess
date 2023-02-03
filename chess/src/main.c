#include "chess.h"

int main(int argc, char* args[]) {
	
	Chess_Init();

	while (Chess_State()) {
		Chess_Render();
		Chess_HandleEvent();
		Chess_Delay();
	}

	Chess_Destroy();

	return 0;
}