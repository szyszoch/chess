#include "texture.h"

typedef struct Texture {
	SDL_Texture* texture;
	SDL_Rect dst;
	SDL_Renderer* renderer;
} Texture;

Texture* Texture_LoadFrom(SDL_Renderer* renderer, const char* path, SDL_Rect position) {

	SDL_Surface* surface = IMG_Load(path);

	if (surface == NULL) {
		LOG_ERROR(SDL_GetError());
		return NULL;
	}
	
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	if (texture == NULL) {
		LOG_ERROR(SDL_GetError());
		return NULL;
	}

	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
	SDL_SetTextureScaleMode(texture, SDL_ScaleModeLinear);

	Texture* new_texture = malloc(sizeof(Texture));

	if (new_texture == NULL) {
		LOG_ERROR("Can't allocate memory");
		SDL_DestroyTexture(texture);
		return NULL;
	}

	new_texture->texture = texture;
	new_texture->dst = position;
	new_texture->renderer = renderer;

	return new_texture;

}

Texture* Texture_CreateText(SDL_Renderer* renderer, const char* font_path, int font_size, const char* title, SDL_Color color, int x, int y) {

	TTF_Font* font = TTF_OpenFont(font_path, font_size);

	if (font == NULL) {
		LOG_ERROR(SDL_GetError());
		return NULL;
	}

	SDL_Surface* surface = TTF_RenderText_Solid(font, title, color);
	TTF_CloseFont(font);

	if (surface == NULL) {
		LOG_ERROR(SDL_GetError());
		return NULL;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	if (texture == NULL) {
		LOG_ERROR(SDL_GetError());
		return NULL;
	}

	Texture* new_texture = malloc(sizeof(Texture));

	if (new_texture == NULL) {
		LOG_ERROR("Can't allocate memory");
		SDL_DestroyTexture(texture);
		return NULL;
	}

	new_texture->renderer = renderer;
	new_texture->texture = texture;
	new_texture->dst.x = x;
	new_texture->dst.y = y;

	SDL_QueryTexture(new_texture->texture, NULL, NULL, &new_texture->dst.w, &new_texture->dst.h);

	return new_texture;

}

void Texture_Destroy(Texture* texture) {
	Texture_Clean(texture);
	free(texture);
}

void Texture_Render(Texture* texture) {
	SDL_RenderCopy(texture->renderer, texture->texture, NULL, &texture->dst);
}

void Texture_ChangePosition(Texture* texture, int x, int y) {
	texture->dst.x = x;
	texture->dst.y = y;
}

void Texture_Clean(Texture* texture) {
	if (texture->texture != NULL)
		SDL_DestroyTexture(texture->texture);
	texture->dst.x = 0;
	texture->dst.y = 0;
	texture->dst.w = 0;
	texture->dst.h = 0;
	texture->renderer = NULL;
}
