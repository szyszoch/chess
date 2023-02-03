#include "chess.h"

typedef struct Chess {
	int state;
	SDL_Renderer* renderer;
	SDL_Window* window;
	SDL_Event events;
} Chess;

Chess chess = { 0,NULL,NULL,0 };

void Chess_Init() {

	static bool init = false;

	if (init == true) {
		WARN("Trying to initialize program again");
		return;
	}

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

	init = true;
	chess.state = STATE_MENU;

}

void Chess_Destroy() {

	static bool quit = false;

	if (quit == true)
		return;

	INFO("Closing");

	SDL_DestroyRenderer(chess.renderer);
	SDL_DestroyWindow(chess.window);

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();

	INFO("Goodbye");

	Log_Quit();

	quit = true;

}

void Chess_Render() {
	SDL_RenderPresent(chess.renderer);
}

void Chess_HandleEvent() {
	
	SDL_PollEvent(&chess.events);
	
	if (chess.events.type == SDL_QUIT) 
		chess.state = STATE_QUIT;

	if (chess.events.key.state == SDL_PRESSED) {
		
		const Uint8* keys = SDL_GetKeyboardState(NULL);

		if (keys[SDL_SCANCODE_ESCAPE] == true)
			chess.state = STATE_QUIT;

	}

	
}

void Chess_Delay() {
	SDL_Delay(1000 / 60);
}

int Chess_State() {

	static p_state = 0;

	if (p_state == chess.state)
		return chess.state;

	if (chess.state == STATE_MENU)
		Chess_State_Menu();

	p_state = chess.state;
	return chess.state;

}

void Chess_State_Menu() {

}