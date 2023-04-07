#include "renderer.h"

SDL_Renderer* renderer = NULL;
SDL_Window* window = NULL;
SDL_Event event_handler;

bool init_window()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		goto error_sdl;

	if (IMG_Init(IMG_INIT_PNG) == 0)
		goto error_sdl_img;

	if (TTF_Init() == -1)
		goto error_sdl_ttf;

	window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

	if (window == NULL)
		goto error_window;

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (renderer == NULL)
		goto error_renderer;

	SDL_Color clr = WINDOW_BACKGROUND_COLOR;
	SDL_SetRenderDrawColor(renderer, clr.r, clr.g, clr.b, clr.a);

	return true;

error_renderer:
	SDL_DestroyWindow(window);
error_window:
	TTF_Quit();
error_sdl_ttf:
	IMG_Quit();
error_sdl_img:
	SDL_Quit();
error_sdl:
	LOG_ERROR(SDL_GetError());
	return false;
}

void destroy_window()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void set_window_default_background_color()
{
	SDL_SetRenderDrawColor(renderer, 
		WINDOW_BACKGROUND_COLOR.r, 
		WINDOW_BACKGROUND_COLOR.g, 
		WINDOW_BACKGROUND_COLOR.b, 
		WINDOW_BACKGROUND_COLOR.a);
}

bool pressed_key(SDL_Scancode code)
{
	const Uint8* keys = SDL_GetKeyboardState(NULL);
	return keys[code];
}

bool pressed_quit()
{
	return (event_handler.type == SDL_QUIT);
}

void delay()
{
	SDL_Delay(1000 / 60);
}
