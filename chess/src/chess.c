#include "chess.h"

Chess chess = {0,NULL,NULL,0,NULL};

void Chess_Init() {

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

	chess.window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

	if (chess.window == NULL) {
		ERROR(SDL_GetError());
		return;
	}

	chess.renderer = SDL_CreateRenderer(chess.window, -1, SDL_RENDERER_ACCELERATED);

	if (chess.renderer == NULL) {
		ERROR(SDL_GetError());
		return;
	}

	chess.state = STATE_MENU;
	chess.texture = NULL;
	chess.ntexture = 0;
	chess.button = NULL;
	chess.nbutton = 0;
	chess.window_flags = SDL_GetWindowFlags(chess.window);

}

void Chess_Destroy() {

	static bool quit = false;

	if (quit == true)
		return;

	quit = true;
	INFO("Closing");

	SDL_DestroyRenderer(chess.renderer);
	SDL_DestroyWindow(chess.window);

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();

	INFO("Goodbye");

	Log_Quit();

}

void Chess_Render() {

	if (chess.window_flags & SDL_WINDOW_MINIMIZED)
		return;

	SDL_RenderClear(chess.renderer);

	for (int i = 0; i < chess.ntexture; i++)
		Texture_Render(chess.texture[i]);
	for (int i = 0; i < chess.nbutton; i++)
		Button_Render(chess.button[i]);

	SDL_RenderPresent(chess.renderer);

}

void Chess_HandleEvent() {
	
	SDL_PollEvent(&chess.events);
	
	chess.window_flags = SDL_GetWindowFlags(chess.window);
	if (chess.window_flags & SDL_WINDOW_MINIMIZED)
		return;

	if (chess.events.type == SDL_QUIT) 
		chess.state = STATE_QUIT;

	if (chess.events.key.state == SDL_PRESSED) {
		
		const Uint8* keys = SDL_GetKeyboardState(NULL);

		if (keys[SDL_SCANCODE_ESCAPE] == true)
			chess.state = STATE_QUIT;

	}

	for(int i=0; i<chess.nbutton; i++) 
		Button_Event(chess.button[i], &chess.events);

}

void Chess_Delay() {
	SDL_Delay(1000 / 60);
}

int Chess_State() {

	static p_state = 0;

	if (p_state == chess.state)
		return chess.state;

	Chess_StateClean();

	if (chess.state == STATE_MENU)
		Chess_State_Menu();

	p_state = chess.state;
	return chess.state;

}

void Chess_State_Menu() {

	chess.ntexture = 1;
	chess.texture = malloc(sizeof(Button*) * chess.ntexture);

	chess.nbutton = 4;
	chess.button = malloc(sizeof(Button*) * chess.nbutton);

	if (chess.texture == NULL) {
		ERROR("Can't allocate memory");
		Chess_StateClean();
		chess.state = STATE_QUIT;
		return;
	}

	if (chess.button == NULL) {
		ERROR("Can't allocate memory");
		Chess_StateClean();
		chess.state = STATE_QUIT;
		return;
	}

	SDL_Rect tp1 = { 0,0,800,800 }; // texture position

	chess.texture[0] = Texture_Init(chess.renderer, "img/board.png", tp1);

	SDL_Rect bp1 = { WINDOW_WIDTH / 2 - 420 / 2,150,420,50 }; 
	SDL_Rect bp2 = { WINDOW_WIDTH / 2 - 420 / 2,225,420,50 }; // button position
	SDL_Rect bp3 = { WINDOW_WIDTH / 2 - 420 / 2,300,420,50 };
	SDL_Rect bp4 = { WINDOW_WIDTH / 2 - 420 / 2,375,420,50 };
	
	SDL_Color bc = {40,40,40,255}; // button color
	SDL_Color btc = { 240,240,240,255}; // button text color

	int bts = 32; // button text size

	chess.button[0] = Button_Init(chess.renderer, "silkscreen/slkscr.ttf", bts, "Local Game", bp1, bc, btc);
	chess.button[1] = Button_Init(chess.renderer, "silkscreen/slkscr.ttf", bts, "Join Game", bp2, bc, btc);
	chess.button[2] = Button_Init(chess.renderer, "silkscreen/slkscr.ttf", bts, "Create Game", bp3, bc, btc);
	chess.button[3] = Button_Init(chess.renderer, "silkscreen/slkscr.ttf", bts, "Exit", bp4, bc, btc);

	Button_SetEvent(chess.button[0], Chess_Event_GoToLocalGame);
	Button_SetEvent(chess.button[1], Chess_Event_GoToJoinGame);
	Button_SetEvent(chess.button[2], Chess_Event_GoToCreateGame);
	Button_SetEvent(chess.button[3], Chess_Event_Exit);

	for (int i = 0; i < chess.ntexture; i++) {
		if (chess.texture[i] == NULL) {
			Chess_StateClean();
			chess.state = STATE_QUIT;
			return;
		}
	}

	for (int i = 0; i < chess.nbutton; i++) {
		if (chess.button[i] == NULL) {
			Chess_StateClean();
			chess.state = STATE_QUIT;
			return;
		}
	}

}

void Chess_StateClean() {

	if (chess.texture != NULL) {

		for (int i = 0; i < chess.ntexture; i++) {
			if (chess.texture[i] != NULL) {
				Texture_Destroy(chess.texture[i]);
			}
		}

		chess.ntexture = 0;
		free(chess.texture);

	}

	if (chess.button != NULL) {

		for (int i = 0; i < chess.nbutton; i++) {
			if (chess.button[i] != NULL) {
				Button_Destroy(chess.button[i]);
			}
		}

		chess.nbutton = 0;
		free(chess.button);

	}

}

void Chess_Event_Exit() {
	chess.state = STATE_QUIT;
}

void Chess_Event_GoToMenu() {
	chess.state = STATE_MENU;
}

void Chess_Event_GoToLocalGame() {
	chess.state = STATE_LOCALGAME;
}

void Chess_Event_GoToJoinGame() {
	chess.state = STATE_JOINGAME;
}

void Chess_Event_GoToCreateGame() {
	chess.state = STATE_CREATEGAME;
}