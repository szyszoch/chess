#include "chess.h"

typedef struct Chess {
	SDL_Renderer* renderer;
	SDL_Window* window;
} Chess;

Chess chess = {NULL,NULL};

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
