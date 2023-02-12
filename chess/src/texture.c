#include "texture.h"

typedef struct Texture {
	SDL_Texture* texture;
	SDL_Rect dst;
	SDL_Renderer* renderer;
} Texture;

Texture* Texture_LoadFrom(SDL_Renderer* renderer, const char* path, SDL_Rect position) {

	Texture* texture = malloc(sizeof(Texture));

	if (texture == NULL) {
		LOG_ERROR("Can't allocate memory");
		return NULL;
	}

	SDL_Surface* source_surface = IMG_Load(path);

	if (source_surface == NULL) {
		LOG_ERROR(SDL_GetError());
		free(texture);
		return NULL;
	}

	SDL_Surface* optimalized_surface = SDL_CreateRGBSurface(0, position.w, position.h, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);

	if (optimalized_surface == NULL) {
		LOG_ERROR(SDL_GetError());
		SDL_FreeSurface(source_surface);
		free(texture);
		return NULL;
	}

	optimalized_surface = SDL_ConvertSurface(source_surface, optimalized_surface->format,0);

	texture->texture = SDL_CreateTextureFromSurface(renderer, optimalized_surface);

	SDL_SetTextureBlendMode(texture->texture, SDL_BLENDMODE_BLEND);
	SDL_SetTextureScaleMode(texture->texture, SDL_ScaleModeLinear);

	SDL_FreeSurface(source_surface);
	SDL_FreeSurface(optimalized_surface);

	if (texture->texture == NULL) {
		LOG_ERROR(SDL_GetError());
		free(texture);
		return NULL;
	}

	texture->dst = position;
	texture->renderer = renderer;

	return texture;

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
}
