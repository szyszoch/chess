#include "chess.h"

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

	create_button("Local Game", bp1, App_Event_GoToLocalGame);
	create_button("Join Game",	bp2, App_Event_GoToJoinGame);
	create_button("Create Game",bp3, App_Event_GoToCreateGame);
	create_button("Exit",		bp4, App_Event_Exit);

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

	create_button("Menu", bp1, App_Event_GoToMenu);
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
	int myturn = (GetHostType() == HOST_CLIENT) ? TEAM_BLACK : TEAM_WHITE;

	reserve_object_memory(2);

	create_button("Menu", bp1, App_Event_GoToMenu);

	unsigned int chessid = create_chess(board_pos);
	Chess* chess = get_object(chessid)->chess;

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

void JoinGame() {

	while (app_state == STATE_JOINGAME) {
		handle_objects();
		render_objects();
		if (CreateClient("6969") == 0) {
			app_state = STATE_NETWORKGAME;
			char msg[17] = "Joined to server";
			send_message(msg, 17);
		}

	}
	destroy_objects();

}

void CreateGame() {

	CreateServer("6969");

	while (!AcceptClient()) {
		handle_objects();
		render_objects();
	}

	while (app_state == STATE_CREATEGAME) {
		handle_objects();
		render_objects();
		
		char buffer[DEFAULT_BUFLEN];

		if (receive_message(buffer, DEFAULT_BUFLEN)) {
			printf("message from client: %s", buffer);
			app_state = STATE_NETWORKGAME;
		}
	}

	destroy_objects();
}


void App_Event_Exit() {
	app_state = STATE_QUIT;
}

void App_Event_GoToMenu() {
	app_state = STATE_MENU;
}

void App_Event_GoToLocalGame() {
	app_state = STATE_LOCALGAME;
}

void App_Event_GoToJoinGame() {
	app_state = STATE_JOINGAME;
}

void App_Event_GoToCreateGame() {
	app_state = STATE_CREATEGAME;
}