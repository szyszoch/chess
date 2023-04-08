#include "state.h"

int main(int argc, char* args[]) 
{
	bool run = true;
	
	log_init();

	if (!init_window())
		run = false;
	if (!load_textures())
		run = false;

	while (run) {
		
		switch (app_state) {
		case STATE_QUIT:		{run = false;	break; };
		case STATE_MENU:		{menu();		break; };
		case STATE_NETWORKGAME: {network_game();break; };
		case STATE_LOCALGAME:	{local_game();	break; };
		case STATE_JOINGAME:	{join_game()	;	break; };
		case STATE_CREATEGAME:	{create_game();	break; };
		}

	}
	
	destroy_textures();
	destroy_window();
	log_quit();

	return 0;
}