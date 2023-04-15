#include "state.h"

int app_state = STATE_MENU;

bool init() 
{
	if (!init_window()) {
		return false;
	}

	if (!load_textures()) {
		return false;
	}

	return true;

}

void quit()
{
	destroy_textures();
	destroy_window();
}

void menu() 
{
	SDL_Rect bp1 = { 0,150,420,50 };	
	SDL_Rect bp2 = { 0,225,420,50 };
	SDL_Rect bp3 = { 0,300,420,50 };
	SDL_Rect bp4 = { 0,375,420,50 };

	center_rect_to_rect_x(&bp1, &WINDOW_RECT);
	center_rect_to_rect_x(&bp2, &WINDOW_RECT);
	center_rect_to_rect_x(&bp3, &WINDOW_RECT);
	center_rect_to_rect_x(&bp4, &WINDOW_RECT);

	Button* b1 = create_button("Local Game",	bp1, ev_goto_localgame);
	Button* b2 = create_button("Join Game",		bp2, ev_goto_joingame);
	Button* b3 = create_button("Create Game",	bp3, ev_goto_creategame);
	Button* b4 = create_button("Exit",			bp4, ev_exit_program);

	while (app_state == STATE_MENU) {
		
		update();

		if (pressed_key(SDL_SCANCODE_ESCAPE) || pressed_quit())
			app_state = STATE_QUIT;
		
		handle_button(b1);
		handle_button(b2);
		handle_button(b3);
		handle_button(b4);
		
		render_button(b1);
		render_button(b2);
		render_button(b3);
		render_button(b4);

		display();
		delay();
	}

	destroy_button(b1);
	destroy_button(b2);
	destroy_button(b3);
	destroy_button(b4);
}

void local_game() 
{	
	SDL_Rect board_pos = { 0,0,600,600 };		
	SDL_Rect left_panel = { board_pos.w, 0, WINDOW_WIDTH - board_pos.w, WINDOW_HEIGHT };
	SDL_Rect bp1 = { 0,500,250,50 };
	SDL_Rect tp1 = { 625,50,250,100 };

	center_rect_to_rect_x(&bp1, &left_panel);

	Button* b1 = create_button("Menu", bp1, ev_goto_menu);
	Chess* c1 = chess_create(&board_pos, GAMEMODE_LOCAL);
	
	Text* t1 = text_create("Turn : white",tp1);
	Text* t2 = text_create("Turn : black",tp1);

	while (app_state == STATE_LOCALGAME) {

		update();

		if (pressed_key(SDL_SCANCODE_ESCAPE) || pressed_quit())
			app_state = STATE_QUIT;

		handle_button(b1);

		if (!chess_is_gameover(c1)) {
			chess_handle(c1);
		}

		if (chess_get_turn(c1) == TEAM_WHITE)
			text_render(t1);
		else 
			text_render(t2);

		render_button(b1);
		chess_render(c1);

		display();
		delay();
	}

	text_destroy(t1);
	text_destroy(t2);
	destroy_button(b1);
	chess_destroy(c1);
}

void network_game()
{
	SDL_Rect board_pos = { 0,0,600,600 };
	SDL_Rect left_panel = { board_pos.w, 0, WINDOW_WIDTH - board_pos.w, WINDOW_HEIGHT };
	SDL_Rect bp1 = { 0,500,250,50 };
	SDL_Rect tp1 = { 625,50,250,100 };

	center_rect_to_rect_x(&bp1, &left_panel);

	Button* b1 = create_button("Menu", bp1, ev_goto_menu);
	Chess* c1 = chess_create(&board_pos, GAMEMODE_NETWORK);

	Text* t1 = text_create("Turn : white", tp1);
	Text* t2 = text_create("Turn : black", tp1);

	while (app_state == STATE_NETWORKGAME) {

		update();

		if (pressed_key(SDL_SCANCODE_ESCAPE) || pressed_quit())
			app_state = STATE_MENU;

		handle_button(b1);

		if (!chess_is_gameover(c1)) {
			chess_handle(c1);
		}
		
		if (chess_get_turn(c1) == TEAM_WHITE)
			text_render(t1);
		else
			text_render(t2);

		render_button(b1);
		chess_render(c1);

		display();
		delay();
	}

	text_destroy(t1);
	text_destroy(t2);
	destroy_button(b1);
	chess_destroy(c1);
}

void join_game() 
{
	while (app_state == STATE_JOINGAME) {
		update();
		if (create_client("6969"))
			app_state = STATE_NETWORKGAME;
		display();
		delay();
	}
}

void create_game()
{
	create_server("6969");

	while (!accept_client()) {
		update();
		display();
		delay();
	}

	app_state = STATE_NETWORKGAME;

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

void ev_goto_networkgame()
{
	app_state = STATE_NETWORKGAME;
}


void ev_goto_joingame() 
{
	app_state = STATE_JOINGAME;
}

void ev_goto_creategame() 
{
	app_state = STATE_CREATEGAME;
}