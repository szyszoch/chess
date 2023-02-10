#include "app.h"

int main(int argc, char* args[]) {
	
	App_Init();

	while (App_State()) {
		App_Render();
		App_HandleEvent();
		App_Delay();
	}

	App_Destroy();

	return 0;
}