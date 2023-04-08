#pragma once
#include "objects/object.h"

#define FONT_PATH "rubik/static/Rubik-Regular.ttf"
#define FONT_SIZE 32
#define FONT_COLOR (SDL_Color){ 0,0,0,255 }

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
void merge_textures(SDL_Texture* src, SDL_Rect* src_r, SDL_Texture* dst, SDL_Rect* dst_r);
void merge_textures_r(SDL_Texture* src, SDL_Rect* src_r, SDL_Texture* dst, SDL_Rect* dst_r);
SDL_Texture* create_contour(SDL_Rect pos, SDL_Color color, int width);
SDL_Texture* create_text(const char* title, SDL_Color color, unsigned int wrapping_length);
SDL_Texture* create_rect(SDL_Rect pos, SDL_Color color);
void center_x_to(SDL_Rect* object_to_center, SDL_Rect object);
void center_y_to(SDL_Rect* object_to_center, SDL_Rect object);



typedef struct Texture Texture;

Texture* t_create(TextureID id);
void t_destroy(Texture* texture);
void t_render(Texture* texture);
void t_setpos(Texture* texture, int x, int y);