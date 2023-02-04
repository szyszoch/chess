#include "chess.h"

typedef struct Chess {
	int state;
	SDL_Renderer* renderer;
	SDL_Window* window;
	SDL_Event events;
	SDL_Texture* texture[TEXTURE_COUNT];
	Button* button[3];
	TTF_Font* font;
} Chess;

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

	chess.font = TTF_OpenFont("silkscreen/slkscr.ttf", 32);

	if (chess.font == NULL) {
		ERROR(SDL_GetError());
		return;
	}

	chess.texture[TEXTURE_BLACK_BISHOP] = IMG_LoadTexture(chess.renderer, "img/black_bishop.png");
	chess.texture[TEXTURE_BLACK_KING]	= IMG_LoadTexture(chess.renderer, "img/black_king.png");
	chess.texture[TEXTURE_BLACK_KNIGHT] = IMG_LoadTexture(chess.renderer, "img/black_knight.png");
	chess.texture[TEXTURE_BLACK_PAWN]	= IMG_LoadTexture(chess.renderer, "img/black_pawn.png");
	chess.texture[TEXTURE_BLACK_QUEEN]	= IMG_LoadTexture(chess.renderer, "img/black_queen.png");
	chess.texture[TEXTURE_BLACK_ROOK]	= IMG_LoadTexture(chess.renderer, "img/black_rook.png");
	chess.texture[TEXTURE_WHITE_BISHOP] = IMG_LoadTexture(chess.renderer, "img/white_bishop.png");
	chess.texture[TEXTURE_WHITE_KING]	= IMG_LoadTexture(chess.renderer, "img/white_king.png");
	chess.texture[TEXTURE_WHITE_KNIGHT] = IMG_LoadTexture(chess.renderer, "img/white_knight.png");
	chess.texture[TEXTURE_WHITE_PAWN]	= IMG_LoadTexture(chess.renderer, "img/white_pawn.png");
	chess.texture[TEXTURE_WHITE_QUEEN]	= IMG_LoadTexture(chess.renderer, "img/white_queen.png");
	chess.texture[TEXTURE_WHITE_ROOK]	= IMG_LoadTexture(chess.renderer, "img/white_rook.png");

	for (int i = 0; i < TEXTURE_COUNT; i++) {
		if (chess.texture[i] == NULL) {
			ERROR(SDL_GetError());
			return;
		}
	}

	chess.button[0] = Button_Init(chess.renderer,chess.font,"Test",(SDL_Rect){100,100,200,100},(SDL_Color){40,40,40,255}, (SDL_Color) { 240, 240, 240,255 });

	

	chess.state = STATE_MENU;

}

void Chess_Destroy() {

	static bool quit = false;

	if (quit == true)
		return;

	quit = true;
	INFO("Closing");

	TTF_CloseFont(chess.font);

	Button_Destroy(chess.button[0]);

	for (int i = 0; i < TEXTURE_COUNT; i++) {
		if (chess.texture[i] != NULL) {
			SDL_DestroyTexture(chess.texture[i]);
		}
	}

	SDL_DestroyRenderer(chess.renderer);
	SDL_DestroyWindow(chess.window);

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();

	INFO("Goodbye");

	Log_Quit();

}

void Chess_Render() {
	Button_Render(chess.button[0]);
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

	Button_Event(chess.button[0], &chess.events);

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