#include "chess.h"

Uint32 window_flags;
Button_F button_form;
Text_F text_form;

int app_state = STATE_MENU;

void App_Init() {

	static bool init = false;

	if (init == true) {
		LOG_WARN("Trying to initialize program again");
		return;
	}

	init = true;
	Log_Init();

	LOG_INFO("Initializing");

	if (InitRenderer() < 0) {
		return;
	}

	app_state = STATE_MENU;
	window_flags = SDL_GetWindowFlags(window);

	button_form.font_size = 32;
	button_form.font_path = "rubik/static/Rubik-Regular.ttf";
	button_form.text_color = (SDL_Color){ 240,240,240,255 };
	button_form.background_color = (SDL_Color){ 40,40,40,255 };
	button_form.background_color_hover = (SDL_Color){ 70,70,70,255 };

	text_form.color = (SDL_Color){ 0,0,0,255 };
	text_form.font_path = "rubik/static/Rubik-Regular.ttf";
	text_form.size = 32;

	SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255);

}

void App_Destroy() {

	static bool quit = false;

	if (quit == true)
		return;

	quit = true;
	LOG_INFO("Closing");

	DestroyRenderer();

	LOG_INFO("Goodbye");

	Log_Quit();

}

void App_Delay() {
	SDL_Delay(1000 / 60);
}


void App_State_Menu() {

	// Init variables
	SDL_Rect bp1 = { WINDOW_WIDTH / 2 - 420 / 2,150,420,50 };	// button position 1
	SDL_Rect bp2 = { WINDOW_WIDTH / 2 - 420 / 2,225,420,50 };	// button position 2
	SDL_Rect bp3 = { WINDOW_WIDTH / 2 - 420 / 2,300,420,50 };	// button position 3
	SDL_Rect bp4 = { WINDOW_WIDTH / 2 - 420 / 2,375,420,50 };	// button position 4

	ReserveObjectMemory(4);

	// Init objects
	unsigned int object;

	object = CreateButton("Local Game", bp1, &button_form, BUTTONEVENT_FUNC);
	SetButtonEvent(object, App_Event_GoToLocalGame);

	object = CreateButton("Join Game", bp2, &button_form, BUTTONEVENT_FUNC);
	SetButtonEvent(object, App_Event_GoToJoinGame);

	object = CreateButton("Create Game", bp3, &button_form, BUTTONEVENT_FUNC);
	SetButtonEvent(object, App_Event_GoToCreateGame);

	object = CreateButton("Exit", bp4, &button_form, BUTTONEVENT_FUNC);
	SetButtonEvent(object, App_Event_Exit);

	// Error handling
		
	if (ErrorCount() > 0) {
		CleanRenderer();
		app_state = STATE_QUIT;
		return;
	}

	while (app_state == STATE_MENU) {
	
		{ // event handling
			SDL_PollEvent(&event_handler);
			const Uint8* keys = SDL_GetKeyboardState(NULL);

			if (keys[SDL_SCANCODE_ESCAPE]) {
				app_state = STATE_QUIT;
			}

			if (event_handler.type == SDL_QUIT) {
				app_state = STATE_QUIT;
			}
			
			HandleObjectsEvent();
		}

		{ // render handling
			
			RenderObjects();
			
			SDL_RenderPresent(renderer);
			SDL_RenderClear(renderer);

		}
		App_Delay();

	}

	CleanRenderer();

}

void App_State_Game() {

	// Init variables

	SDL_Rect board_pos = { 0,0,600,600 };

	SDL_Rect bp1 = { WINDOW_WIDTH-200,WINDOW_HEIGHT-100,150,50 };	// button position
	
	unsigned int nbutton = 1;
	ReserveObjectMemory(nbutton);

	// Init objects

	unsigned int button[1];

	if (Board_InitTextures(renderer) == false) {
		app_state = STATE_QUIT;
		return;
	}

	button[0] = CreateButton("Menu", bp1, &button_form, BUTTONEVENT_FUNC);

	{ // Error handling

		for (unsigned int i = 0; i < nbutton; i++) {
			if (button[i] == INVALID_OBJECT) {
				CleanRenderer();
				app_state = STATE_QUIT;
				return;
			}
		}

	}

	SetButtonEvent(button[0], App_Event_GoToMenu);

	Board board;
	Board_Restart(&board);

	while (app_state == STATE_GAME) {

		{ // event handling
			SDL_PollEvent(&event_handler);
			const Uint8* keys = SDL_GetKeyboardState(NULL);

			if (keys[SDL_SCANCODE_ESCAPE]) {
				app_state = STATE_MENU;
			}

			if (event_handler.type == SDL_QUIT) {
				app_state = STATE_QUIT;
			}

			if (board.gameover == false) { 
				// Handle Board

				Move move = {-1,-1,-1,-1};
				Board_Handle_Events(&board, &board_pos, &move);
				
				if (move.src_x != -1) {
					
					
					if (Board_CanMove(&board, move.src_x, move.src_y, move.dst_x, move.dst_y)) {
						Board_Move(&board, move.src_x, move.src_y, move.dst_x, move.dst_y);
						Board_ChangeTurn(&board);
					}

				}
				if (Board_IsKingInDanger(&board, board.turn) && Board_KingCannotMove(&board, board.turn)) {
					board.gameover = true;
					LOG_INFO("GameOver");
				}
				
			}

			for (unsigned int i = 0; i < nbutton; i++) {
				HandleObjectEvent(button[i]);
			}

		}

		{ // render handling

			for (unsigned int i = 0; i < nbutton; i++) {
				RenderObject(button[i]);
			}
			
			Board_Render(&board, &board_pos);

			SDL_RenderPresent(renderer);
			SDL_RenderClear(renderer);

		}
		App_Delay();

	}

	CleanRenderer();

}

void App_State_JoinGame() {

}

void App_State_CreateGame() {

}

void App_Event_Exit() {
	app_state = STATE_QUIT;
}

void App_Event_GoToMenu() {
	app_state = STATE_MENU;
}

void App_Event_GoToLocalGame() {
	app_state = STATE_GAME;
}

void App_Event_GoToJoinGame() {
	app_state = STATE_JOINGAME;
}

void App_Event_GoToCreateGame() {
	app_state = STATE_CREATEGAME;
}