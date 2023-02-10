#include "app.h"

App app;

void App_Init() {

	static bool init = false;

	if (init == true) {
		WARN("Trying to initialize program again");
		return;
	}

	init = true;
	Log_Init();

	INFO("Initializing");

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		ERROR(SDL_GetError());
		return;
	}

	if (IMG_Init(IMG_INIT_PNG) == 0) {
		ERROR(SDL_GetError());
		return;
	}

	if (TTF_Init() == -1) {
		ERROR(SDL_GetError());
		return;
	}

	app.window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

	if (app.window == NULL) {
		ERROR(SDL_GetError());
		return;
	}

	app.renderer = SDL_CreateRenderer(app.window, -1, SDL_RENDERER_ACCELERATED);

	if (app.renderer == NULL) {
		ERROR(SDL_GetError());
		return;
	}

	app.state = STATE_MENU;
	app.texture = NULL;
	app.ntexture = 0;
	app.button = NULL;
	app.nbutton = 0;
	app.chess = NULL;
	app.nchess = 0;
	app.window_flags = SDL_GetWindowFlags(app.window);

}

void App_Destroy() {

	static bool quit = false;

	if (quit == true)
		return;

	quit = true;
	INFO("Closing");

	SDL_DestroyRenderer(app.renderer);
	SDL_DestroyWindow(app.window);

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();

	INFO("Goodbye");

	Log_Quit();

}

void App_Render() {

	if (app.window_flags & SDL_WINDOW_MINIMIZED)
		return;

	SDL_RenderClear(app.renderer);

	for (int i = 0; i < app.nchess; i++)
		Board_Render(app.chess[i]);
	for (int i = 0; i < app.ntexture; i++)
		Texture_Render(app.texture[i]);
	for (int i = 0; i < app.nbutton; i++)
		Button_Render(app.button[i]);

	SDL_RenderPresent(app.renderer);

}

void App_HandleEvent() {
	
	SDL_PollEvent(&app.events);
	
	app.window_flags = SDL_GetWindowFlags(app.window);
	if (app.window_flags & SDL_WINDOW_MINIMIZED)
		return;

	if (app.events.type == SDL_QUIT) 
		app.state = STATE_QUIT;

	if (app.events.key.state == SDL_PRESSED) {
		
		const Uint8* keys = SDL_GetKeyboardState(NULL);

		if (keys[SDL_SCANCODE_ESCAPE] == true)
			app.state = STATE_QUIT;

	}

	for (int i = 0; i < app.nchess; i++)
		Board_Event(app.chess[i], &app.events);
	for(int i=0; i<app.nbutton; i++) 
		Button_Event(app.button[i], &app.events);

}

void App_Delay() {
	SDL_Delay(1000 / 60);
}

int App_State() {

	static p_state = 0;

	if (p_state == app.state)
		return app.state;

	App_StateClean();

	if (app.state == STATE_MENU)
		App_State_Menu();
	if (app.state == STATE_LOCALGAME)
		App_State_LocalGame();

	p_state = app.state;
	return app.state;

}

void App_State_Menu() {

	app.ntexture = 1;
	app.texture = malloc(sizeof(Button*) * app.ntexture);

	app.nbutton = 4;
	app.button = malloc(sizeof(Button*) * app.nbutton);

	if (app.texture == NULL) {
		ERROR("Can't allocate memory");
		App_StateClean();
		app.state = STATE_QUIT;
		return;
	}

	if (app.button == NULL) {
		ERROR("Can't allocate memory");
		App_StateClean();
		app.state = STATE_QUIT;
		return;
	}

	SDL_Rect tp1 = { 0,0,800,800 }; // texture position

	app.texture[0] = Texture_Init(app.renderer, "img/board.png", tp1);

	SDL_Rect bp1 = { WINDOW_WIDTH / 2 - 420 / 2,150,420,50 }; 
	SDL_Rect bp2 = { WINDOW_WIDTH / 2 - 420 / 2,225,420,50 }; // button position
	SDL_Rect bp3 = { WINDOW_WIDTH / 2 - 420 / 2,300,420,50 };
	SDL_Rect bp4 = { WINDOW_WIDTH / 2 - 420 / 2,375,420,50 };
	
	SDL_Color bc = {40,40,40,255}; // button color
	SDL_Color btc = { 240,240,240,255}; // button text color

	int bts = 32; // button text size

	app.button[0] = Button_Init(app.renderer, "silkscreen/slkscr.ttf", bts, "Local Game", bp1, bc, btc);
	app.button[1] = Button_Init(app.renderer, "silkscreen/slkscr.ttf", bts, "Join Game", bp2, bc, btc);
	app.button[2] = Button_Init(app.renderer, "silkscreen/slkscr.ttf", bts, "Create Game", bp3, bc, btc);
	app.button[3] = Button_Init(app.renderer, "silkscreen/slkscr.ttf", bts, "Exit", bp4, bc, btc);

	for (int i = 0; i < app.ntexture; i++) {
		if (app.texture[i] == NULL) {
			App_StateClean();
			app.state = STATE_QUIT;
			return;
		}
	}

	for (int i = 0; i < app.nbutton; i++) {
		if (app.button[i] == NULL) {
			App_StateClean();
			app.state = STATE_QUIT;
			return;
		}
	}

	Button_SetEvent(app.button[0], App_Event_GoToLocalGame);
	Button_SetEvent(app.button[1], App_Event_GoToJoinGame);
	Button_SetEvent(app.button[2], App_Event_GoToCreateGame);
	Button_SetEvent(app.button[3], App_Event_Exit);

}

void App_State_LocalGame() {

	app.ntexture = 0;
	app.texture = malloc(sizeof(Button*) * app.ntexture);

	app.nbutton = 0;
	app.button = malloc(sizeof(Button*) * app.nbutton);

	app.nchess = 1;
	app.chess = malloc(sizeof(Chess*) * app.nchess);

	if (app.texture == NULL) {
		ERROR("Can't allocate memory");
		App_StateClean();
		app.state = STATE_QUIT;
		return;
	}

	if (app.button == NULL) {
		ERROR("Can't allocate memory");
		App_StateClean();
		app.state = STATE_QUIT;
		return;
	}

	if (app.chess == NULL) {
		ERROR("Can't allocate memory");
		App_StateClean();
		app.state = STATE_QUIT;
		return;
	}

	SDL_Rect board_pos = { 0,0,WINDOW_HEIGHT,WINDOW_HEIGHT };

	app.chess[0] = Board_Init(app.renderer,board_pos);

	for (int i = 0; i < app.ntexture; i++) {
		if (app.texture[i] == NULL) {
			App_StateClean();
			app.state = STATE_QUIT;
			return;
		}
	}

	for (int i = 0; i < app.nbutton; i++) {
		if (app.button[i] == NULL) {
			App_StateClean();
			app.state = STATE_QUIT;
			return;
		}
	}

	for (int i = 0; i < app.nchess; i++) {
		if (app.chess[i] == NULL) {
			App_StateClean();
			app.state = STATE_QUIT;
			return;
		}
	}

}

void App_StateClean() {

	if (app.texture != NULL) {

		for (int i = 0; i < app.ntexture; i++) {
			if (app.texture[i] != NULL) {
				Texture_Destroy(app.texture[i]);
			}
		}

		app.ntexture = 0;
		free(app.texture);

	}

	if (app.button != NULL) {

		for (int i = 0; i < app.nbutton; i++) {
			if (app.button[i] != NULL) {
				Button_Destroy(app.button[i]);
			}
		}

		app.nbutton = 0;
		free(app.button);

	}

	if (app.chess != NULL) {

		for (int i = 0; i < app.nchess; i++) {
			if (app.chess[i] != NULL) {
				Board_Destroy(app.chess[i]);
			}
		}

		app.nchess = 0;
		free(app.chess);

	}

}

void App_Event_Exit() {
	app.state = STATE_QUIT;
}

void App_Event_GoToMenu() {
	app.state = STATE_MENU;
}

void App_Event_GoToLocalGame() {
	app.state = STATE_LOCALGAME;
}

void App_Event_GoToJoinGame() {
	app.state = STATE_JOINGAME;
}

void App_Event_GoToCreateGame() {
	app.state = STATE_CREATEGAME;
}