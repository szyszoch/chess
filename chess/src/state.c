#include "state.h"

int app_state = STATE_MENU;

void menu() 
{
	SDL_Rect bp1 = { 0,150,420,50 };	
	SDL_Rect bp2 = { 0,225,420,50 };
	SDL_Rect bp3 = { 0,300,420,50 };
	SDL_Rect bp4 = { 0,375,420,50 };

	center_x_to(&bp1, WINDOW_RECT);
	center_x_to(&bp2, WINDOW_RECT);
	center_x_to(&bp3, WINDOW_RECT);
	center_x_to(&bp4, WINDOW_RECT);

	reserve_object_memory(4);

	create_button("Local Game", bp1, ev_goto_localgame);
	create_button("Join Game",	bp2, ev_goto_joingame);
	create_button("Create Game",bp3, ev_goto_creategame);
	create_button("Exit",		bp4, ev_exit_program);

	while (app_state == STATE_MENU) {
		handle_objects();
		
		if (pressed_key(SDL_SCANCODE_ESCAPE) || pressed_quit())
			app_state = STATE_QUIT;
		
		render_objects();
		delay();
	}

	destroy_objects();
}

void local_game() 
{																
	SDL_Rect board_pos = { 0,0,600,600 };						
	SDL_Rect bp1 = { WINDOW_WIDTH-200,WINDOW_HEIGHT-100,150,50 };
	
	reserve_object_memory(2);

	create_button("Menu", bp1, ev_goto_menu);
	unsigned int chess = create_chess(board_pos);

	while (app_state == STATE_LOCALGAME) {
		handle_objects();

		if (pressed_key(SDL_SCANCODE_ESCAPE) || pressed_quit())
			app_state = STATE_QUIT;

		render_objects();
		delay();
	}

	destroy_objects();
}

void network_game()
{
	SDL_Rect board_pos = { 0,0,600,600 };
	SDL_Rect bp1 = { WINDOW_WIDTH - 200,WINDOW_HEIGHT - 100,150,50 };
	int myturn = (get_host_type() == HOST_CLIENT) ? TEAM_BLACK : TEAM_WHITE;

	reserve_object_memory(2);

	create_button("Menu", bp1, ev_goto_menu);

	unsigned int chessid = create_chess(board_pos);
	Chess* chess = get_object(chessid)->chess;

	if (myturn != c_get_turn(chess))
		freeze_object(c_get_object(chess));

	while (app_state == STATE_NETWORKGAME) {

		handle_objects();

		Move move = c_get_last_move(chess);
		if (move.src_x != -1) {
			char msg[] = { move.src_x,move.src_y,move.dst_x,move.dst_y,'\0' };
			send_message(msg, 5);
			freeze_object(c_get_object(chess));
		}

		if (myturn != c_get_turn(chess)) {
			char buff[DEFAULT_BUFLEN];
			if (receive_message(buff, DEFAULT_BUFLEN)) {
				Move move = { buff[0],buff[1],buff[2],buff[3] };
				Board_Move(chess, move);
				Board_ChangeTurn(chess);
				unfreeze_object(c_get_object(chess));
			}
		}

		if (pressed_key(SDL_SCANCODE_ESCAPE) || pressed_quit())
			app_state = STATE_QUIT;

		render_objects();
		delay();
	}

	destroy_objects();
}

void join_game() 
{
	while (app_state == STATE_JOINGAME) {
		handle_objects();
		render_objects();
		if (create_client("6969"))
			app_state = STATE_NETWORKGAME;
	}

	destroy_objects();
}

void create_game() 
{
	create_server("6969");

	while (!accept_client()) {
		handle_objects();
		render_objects();
	}

	app_state = STATE_NETWORKGAME;

	destroy_objects();
}


void ev_exit_program() 
{
	app_state = STATE_QUIT;
}

void ev_goto_menu() 
{
	app_state = STATE_MENU;
}

void ev_goto_localgame() 
{
	app_state = STATE_LOCALGAME;
}

void ev_goto_joingame() 
{
	app_state = STATE_JOINGAME;
}

void ev_goto_creategame() 
{
	app_state = STATE_CREATEGAME;
}