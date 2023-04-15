#include "renderer.h"

static SDL_Renderer* renderer = NULL;
static SDL_Window* window = NULL;
static SDL_Texture* textures[TEXTURE_COUNT] = { NULL };

bool init_window()
{
	SDL_LogSetAllPriority(SDL_LOG_PRIORITY_VERBOSE);
	LOG_INFO(SDL_LOG_CATEGORY_VIDEO, "Initializing SDL2");

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		goto error_sdl;

	if (IMG_Init(IMG_INIT_PNG) == 0)
		goto error_sdl_img;

	if (TTF_Init() == -1)
		goto error_sdl_ttf;

	LOG_VERBOSE(SDL_LOG_CATEGORY_VIDEO, "Creating window '%s' %dx%d", WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT);
	window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

	if (window == NULL)
		goto error_window;

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (renderer == NULL)
		goto error_renderer;

	set_window_default_background_color();

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
	LOG_CRITICAL(SDL_LOG_CATEGORY_VIDEO, SDL_GetError());
	return false;
}

void destroy_window()
{
	LOG_INFO(SDL_LOG_CATEGORY_VIDEO, "Quiting SDL2 subsystem");

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void display() 
{
	SDL_RenderPresent(renderer);
	SDL_RenderClear(renderer);
}

void set_window_default_background_color()
{
	SDL_SetRenderDrawColor(renderer, 
		WINDOW_BACKGROUND_COLOR.r, 
		WINDOW_BACKGROUND_COLOR.g, 
		WINDOW_BACKGROUND_COLOR.b, 
		WINDOW_BACKGROUND_COLOR.a);
}

void delay()
{
	SDL_Delay(1000 / 60); // 60 FPS
}

void render(SDL_Texture* tex, const SDL_Rect* src, const SDL_Rect* dst)
{
	SDL_RenderCopy(renderer, tex, src, dst);
}

SDL_Texture* load_texture(const char* path)
{
	SDL_Texture* tex = IMG_LoadTexture(renderer, path);

	if (tex == NULL) {
		LOG_INFO(SDL_LOG_CATEGORY_RENDER, SDL_GetError());
		return NULL;
	}

	return tex;
}

SDL_Texture* create_empty_texture(SDL_Rect pos)
{
	SDL_Texture* tex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, pos.w, pos.h);
	SDL_SetTextureBlendMode(tex, SDL_BLENDMODE_BLEND);

	if (tex == NULL) {
		LOG_ERROR(SDL_LOG_CATEGORY_RENDER, SDL_GetError());
		return NULL;
	}

	return tex;
}

SDL_Texture* create_border(SDL_Rect pos, SDL_Color color, int width)
{
	SDL_Texture* tex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, pos.w, pos.h);
	SDL_SetTextureBlendMode(tex, SDL_BLENDMODE_BLEND);

	if (tex == NULL) {
		LOG_ERROR(SDL_LOG_CATEGORY_RENDER,SDL_GetError());
		return NULL;
	}

	SDL_SetRenderTarget(renderer, tex);
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

	for (int i = 0; i < width; i++) {
		SDL_Rect rect = { 0 + i,0 + i,pos.w - i * 2,pos.h - i * 2 };
		SDL_RenderDrawRect(renderer, &rect);
	}

	SDL_SetRenderTarget(renderer, NULL);
	set_window_default_background_color();

	return tex;
}

SDL_Texture* create_text(const char* title, SDL_Color color, unsigned int size, unsigned int wrapping_len)
{
	TTF_Font* font = TTF_OpenFont(FONT_FAMILY, size);

	if (font == NULL)
		goto error;

	SDL_Surface* surface = NULL;

	if (wrapping_len == 0)
		surface = TTF_RenderText_Solid(font, title, color);
	else 
		surface = TTF_RenderText_Solid_Wrapped(font, title, color, wrapping_len);
	
	TTF_CloseFont(font);

	if (surface == NULL)
		goto error;

	SDL_Texture* textures = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_SetTextureBlendMode(textures, SDL_BLENDMODE_BLEND);
	SDL_FreeSurface(surface);

	if (textures == NULL)
		goto error;

	return textures;

error:
	LOG_ERROR(SDL_LOG_CATEGORY_RENDER, SDL_GetError());
	return NULL;
}

SDL_Texture* create_rect(SDL_Rect pos, SDL_Color color)
{
	SDL_Texture* textures = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, pos.w, pos.h);
	SDL_SetTextureBlendMode(textures, SDL_BLENDMODE_BLEND);

	if (textures == NULL) {
		LOG_ERROR(SDL_LOG_CATEGORY_RENDER,SDL_GetError());
		return NULL;
	}

	SDL_SetRenderTarget(renderer, textures);
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(renderer, NULL);
	SDL_SetRenderTarget(renderer, NULL);
	set_window_default_background_color();

	return textures;
}

void merge_textures(SDL_Texture* src, SDL_Rect* src_r, SDL_Texture* dst, SDL_Rect* dst_r)
{
	SDL_SetRenderTarget(renderer, dst);
	SDL_RenderCopy(renderer, src, src_r, dst_r);
	SDL_SetRenderTarget(renderer, NULL);
}

void merge_textures_r(SDL_Texture* src, SDL_Rect* src_r, SDL_Texture* dst, SDL_Rect* dst_r)
{
	merge_textures(src, src_r, dst, dst_r);
	SDL_DestroyTexture(src);
}



bool load_textures()
{
	textures[TEXTURE_BOARD] =			load_texture("img/board.png");
	textures[TEXTURE_BLACK_BISHOP] =	load_texture("img/black_bishop.png");
	textures[TEXTURE_BLACK_KING] =		load_texture("img/black_king.png");
	textures[TEXTURE_BLACK_KNIGHT] =	load_texture("img/black_knight.png");
	textures[TEXTURE_BLACK_PAWN] =		load_texture("img/black_pawn.png");
	textures[TEXTURE_BLACK_QUEEN] =		load_texture("img/black_queen.png");
	textures[TEXTURE_BLACK_ROOK] =		load_texture("img/black_rook.png");
	textures[TEXTURE_WHITE_BISHOP] =	load_texture("img/white_bishop.png");
	textures[TEXTURE_WHITE_KING] =		load_texture("img/white_king.png");
	textures[TEXTURE_WHITE_KNIGHT] =	load_texture("img/white_knight.png");
	textures[TEXTURE_WHITE_PAWN] =		load_texture("img/white_pawn.png");
	textures[TEXTURE_WHITE_QUEEN] =		load_texture("img/white_queen.png");
	textures[TEXTURE_WHITE_ROOK] =		load_texture("img/white_rook.png");

	for (int i = 0; i < TEXTURE_COUNT; i++) {
		if (textures[i] == NULL) {
			goto error_texture;
		}
	}

	return true;

error_texture:
	LOG_ERROR(SDL_LOG_CATEGORY_APPLICATION, "Can't load textures");
	destroy_textures();
	return false;
}

void destroy_textures()
{
	for (int i = 0; i < TEXTURE_COUNT; i++) {
		if (textures[i] == NULL)
			continue;
		SDL_DestroyTexture(textures[i]);
	}
}

SDL_Texture* get_texture(TextureID id)
{
	if (id >= TEXTURE_COUNT || id < 0) {
		LOG_WARN(SDL_LOG_CATEGORY_APPLICATION, "Trying to access memomry out of array scope");
		return NULL;
	}
	return textures[id];
}