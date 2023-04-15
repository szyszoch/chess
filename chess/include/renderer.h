#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdbool.h>

#include "log.h"

#define WINDOW_TITLE "Chess"
#define WINDOW_WIDTH 900
#define WINDOW_HEIGHT 600
#define WINDOW_RECT (SDL_Rect){0,0,WINDOW_WIDTH,WINDOW_HEIGHT}
#define WINDOW_BACKGROUND_COLOR (SDL_Color){150, 150, 150, 255}

#define FONT_FAMILY "rubik/static/Rubik-Regular.ttf"

bool init_window();
void destroy_window();
void display();
void set_window_default_background_color();
void delay();
void render(SDL_Texture* tex, const SDL_Rect* src, const SDL_Rect* dst);
SDL_Texture* load_texture(const char* path);
SDL_Texture* create_empty_texture(SDL_Rect pos);
SDL_Texture* create_border(SDL_Rect pos, SDL_Color color, int width);
SDL_Texture* create_text(const char* title, SDL_Color clr, unsigned int size, unsigned int wrapping_len);
SDL_Texture* create_rect(SDL_Rect pos, SDL_Color color);
void merge_textures(SDL_Texture* src, SDL_Rect* src_r, SDL_Texture* dst, SDL_Rect* dst_r);
void merge_textures_r(SDL_Texture* src, SDL_Rect* src_r, SDL_Texture* dst, SDL_Rect* dst_r);

typedef enum TextureID {
	TEXTURE_BLACK_BISHOP,
	TEXTURE_BLACK_KING,
	TEXTURE_BLACK_KNIGHT,
	TEXTURE_BLACK_PAWN,
	TEXTURE_BLACK_QUEEN,
	TEXTURE_BLACK_ROOK,
	TEXTURE_WHITE_BISHOP,
	TEXTURE_WHITE_KING,
	TEXTURE_WHITE_KNIGHT,
	TEXTURE_WHITE_PAWN,
	TEXTURE_WHITE_QUEEN,
	TEXTURE_WHITE_ROOK,
	TEXTURE_BOARD,
	TEXTURE_COUNT
} TextureID;

bool load_textures();
void destroy_textures();
SDL_Texture* get_texture(TextureID id);