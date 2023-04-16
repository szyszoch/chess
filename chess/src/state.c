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

	SDL_StartTextInput();

	return true;

}

void quit()
{
	SDL_StopTextInput();
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

	Button* b1 = button_create("Local Game",	bp1, ev_goto_localgame);
	Button* b2 = button_create("Join Game",		bp2, ev_goto_joingame);
	Button* b3 = button_create("Create Game",	bp3, ev_goto_creategame);
	Button* b4 = button_create("Exit",			bp4, ev_exit_program);

	while (app_state == STATE_MENU) {
		
		update();

		if (pressed_key(SDL_SCANCODE_ESCAPE) || pressed_quit())
			app_state = STATE_QUIT;
		
		button_handle(b1);
		button_handle(b2);
		button_handle(b3);
		button_handle(b4);
		
		button_render(b1);
		button_render(b2);
		button_render(b3);
		button_render(b4);

		display();
		delay();
	}

	button_destroy(b1);
	button_destroy(b2);
	button_destroy(b3);
	button_destroy(b4);
}

void local_game() 
{	
	SDL_Rect board_pos = { 0,0,600,600 };		
	SDL_Rect left_panel = { board_pos.w, 0, WINDOW_WIDTH - board_pos.w, WINDOW_HEIGHT };
	SDL_Rect bp1 = { 0,500,250,50 };
	SDL_Rect tp1 = { 625,50,250,100 };

	center_rect_to_rect_x(&bp1, &left_panel);

	Button* b1 = button_create("Menu", bp1, ev_goto_menu);
	Chess* c1 = chess_create(&board_pos, GAMEMODE_LOCAL);
	
	Text* t1 = text_create("Turn : white",tp1);
	Text* t2 = text_create("Turn : black",tp1);

	while (app_state == STATE_LOCALGAME) {

		update();

		if (pressed_key(SDL_SCANCODE_ESCAPE) || pressed_quit())
			app_state = STATE_QUIT;

		button_handle(b1);

		if (!chess_is_gameover(c1)) {
			chess_handle(c1);
		}

		if (chess_get_turn(c1) == TEAM_WHITE)
			text_render(t1);
		else 
			text_render(t2);

		button_render(b1);
		chess_render(c1);

		display();
		delay();
	}

	text_destroy(t1);
	text_destroy(t2);
	button_destroy(b1);
	chess_destroy(c1);
}

void network_game()
{
	SDL_Rect board_pos = { 0,0,600,600 };
	SDL_Rect left_panel = { board_pos.w, 0, WINDOW_WIDTH - board_pos.w, WINDOW_HEIGHT };
	SDL_Rect bp1 = { 0,500,250,50 };
	SDL_Rect tp1 = { 625,50,250,100 };

	center_rect_to_rect_x(&bp1, &left_panel);

	Button* b1 = button_create("Menu", bp1, ev_goto_menu);
	Chess* c1 = chess_create(&board_pos, GAMEMODE_NETWORK);

	Text* t1 = text_create("Turn : white", tp1);
	Text* t2 = text_create("Turn : black", tp1);

	while (app_state == STATE_NETWORKGAME) {

		update();

		if (pressed_key(SDL_SCANCODE_ESCAPE) || pressed_quit())
			app_state = STATE_MENU;

		button_handle(b1);

		if (!chess_is_gameover(c1)) {
			chess_handle(c1);
		}
		
		if (chess_get_turn(c1) == TEAM_WHITE)
			text_render(t1);
		else
			text_render(t2);

		button_render(b1);
		chess_render(c1);

		display();
		delay();
	}

	text_destroy(t1);
	text_destroy(t2);
	button_destroy(b1);
	chess_destroy(c1);
}

void join_game() 
{
	SDL_Rect bp1 = { 0,500,250,50 };
	SDL_Rect inbp1 = { 0,150,250,50 };
	SDL_Rect inbp2 = { 0,210,210,50 };

	center_rect_to_rect_x(&inbp1, &WINDOW_RECT);
	center_rect_to_rect_x(&inbp2, &WINDOW_RECT);
	center_rect_to_rect_x(&bp1, &WINDOW_RECT);
	
	InputBox* inb1 = inputbox_create(inbp1, 15);
	InputBox* inb2 = inputbox_create(inbp2, 8);
	Button* b1 = button_create("Enter", bp1, NULL);

	while (app_state == STATE_JOINGAME) {

		update();
		inputbox_handle(inb1);
		inputbox_handle(inb2);
		button_handle(b1);

		if (pressed_key(SDL_SCANCODE_ESCAPE) || pressed_quit())
			app_state = STATE_MENU;

		if (button_clicked(b1)) {

			const char* addr = inputbox_get_input(inb1);
			const char* port = inputbox_get_input(inb2);

			while (!create_client(addr,port)) {
				update();
				if (pressed_key(SDL_SCANCODE_ESCAPE) || pressed_quit()) {
					app_state = STATE_MENU;
					break;
				}
			}

			if (is_connected()) 
				app_state = STATE_NETWORKGAME;
			else
				app_state = STATE_MENU;
		}

		inputbox_render(inb1);
		inputbox_render(inb2);
		button_render(b1);

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
