#include "chess.h"

int main(int argc, char* args[]) {
	
	App_Init();

	bool run = true;

	while (run) {
		
		switch (app_state) {
		case STATE_QUIT:		{run = false			; break; };
		case STATE_MENU:		{App_State_Menu()		; break; };
		case STATE_GAME:	{App_State_Game(); break; };
		}

	}

	App_Destroy();

	return 0;
}