#include "objects/texture.h"

static SDL_Texture* textures[TEXTURE_COUNT];

bool load_textures()
{
	textures[TEXTURE_BOARD] =		 IMG_LoadTexture(renderer, "img/board.png");
	textures[TEXTURE_BLACK_BISHOP] = IMG_LoadTexture(renderer, "img/black_bishop.png");
	textures[TEXTURE_BLACK_KING] =	 IMG_LoadTexture(renderer, "img/black_king.png");
	textures[TEXTURE_BLACK_KNIGHT] = IMG_LoadTexture(renderer, "img/black_knight.png");
	textures[TEXTURE_BLACK_PAWN] =	 IMG_LoadTexture(renderer, "img/black_pawn.png");
	textures[TEXTURE_BLACK_QUEEN] =	 IMG_LoadTexture(renderer, "img/black_queen.png");
	textures[TEXTURE_BLACK_ROOK] =	 IMG_LoadTexture(renderer, "img/black_rook.png");
	textures[TEXTURE_WHITE_BISHOP] = IMG_LoadTexture(renderer, "img/white_bishop.png");
	textures[TEXTURE_WHITE_KING] =	 IMG_LoadTexture(renderer, "img/white_king.png");
	textures[TEXTURE_WHITE_KNIGHT] = IMG_LoadTexture(renderer, "img/white_knight.png");
	textures[TEXTURE_WHITE_PAWN] =	 IMG_LoadTexture(renderer, "img/white_pawn.png");
	textures[TEXTURE_WHITE_QUEEN] =	 IMG_LoadTexture(renderer, "img/white_queen.png");
	textures[TEXTURE_WHITE_ROOK] =	 IMG_LoadTexture(renderer, "img/white_rook.png");

	for (int i = 0; i < TEXTURE_COUNT; i++) {
		if (textures[i] == NULL) {
			goto error_texture;
		}
	}

	return true;

error_texture:
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
	return textures[id];
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

SDL_Texture* create_contour(SDL_Rect pos, SDL_Color color, int width)
{
	SDL_Texture* textures = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, pos.w, pos.h);
	SDL_SetTextureBlendMode(textures, SDL_BLENDMODE_BLEND);

	if (textures == NULL) {
		LOG_ERROR(SDL_GetError());
		return NULL;
	}

	SDL_SetRenderTarget(renderer, textures);
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

	for (int i = 0; i < width; i++) {
		SDL_Rect rect = { 0 + i,0 + i,pos.w - i * 2,pos.h - i * 2 };
		SDL_RenderDrawRect(renderer, &rect);
	}

	SDL_SetRenderTarget(renderer, NULL);
	set_window_default_background_color();

	return textures;
}

SDL_Texture* create_text(const char* title, SDL_Color color, unsigned int wrapping_length)
{
	TTF_Font* font = TTF_OpenFont(FONT_PATH, FONT_SIZE);

	if (font == NULL)
		goto error;

	SDL_Surface* surface = TTF_RenderText_Solid_Wrapped(font, title, color, wrapping_length);
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
	LOG_ERROR(SDL_GetError());
	return NULL;
}

SDL_Texture* create_rect(SDL_Rect pos, SDL_Color color)
{
	SDL_Texture* textures = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, pos.w, pos.h);
	SDL_SetTextureBlendMode(textures, SDL_BLENDMODE_BLEND);

	if (textures == NULL) {
		LOG_ERROR(SDL_GetError());
		return NULL;
	}

	SDL_SetRenderTarget(renderer, textures);
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(renderer, NULL);
	SDL_SetRenderTarget(renderer, NULL);
	set_window_default_background_color();

	return textures;
}

void center_x_to(SDL_Rect* object_to_center, SDL_Rect object)
{
	object_to_center->x = object.x + object.w / 2 - object_to_center->w / 2;
}

void center_y_to(SDL_Rect* object_to_center, SDL_Rect object)
{
	object_to_center->y = object.y + object.h / 2 - object_to_center->h / 2;
}



typedef struct Texture {
	SDL_Texture* texture;
	Object o;
} Texture;

Texture* t_create(TextureID id)
{
	Texture* new_texture = malloc(sizeof(Texture));

	if (new_texture == NULL) {
		LOG_ERROR("Can't allocate memory");
		return NULL;
	}

	new_texture->texture = textures[id];
	new_texture->o.pos = (SDL_Rect){ 0,0,0,0 };
	SDL_QueryTexture(new_texture->texture, NULL, NULL, &new_texture->o.pos.w, &new_texture->o.pos.h);

	return new_texture;
}

void t_destroy(Texture* texture)
{
	if (texture == NULL)
		return;
	free(texture);
}

void t_render(Texture* texture)
{
	SDL_RenderCopy(renderer, texture->texture, NULL, &texture->o.pos);
}

void t_setpos(Texture* texture, int x, int y)
{
	texture->o.pos.x = x;
	texture->o.pos.y = y;
}