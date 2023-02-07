#include "texture.h"

typedef struct Texture {
	SDL_Texture* texture;
	SDL_Rect dst;
	SDL_Renderer* renderer;
} Texture;

Texture* Texture_Init(SDL_Renderer* renderer, const char* path, SDL_Rect position) {

	Texture* texture = malloc(sizeof(Texture));

	if (texture == NULL) {
		ERROR("Can't allocate memory");
		return NULL;
	}

	SDL_Surface* source_surface = IMG_Load(path);

	if (source_surface == NULL) {
		ERROR(SDL_GetError());
		free(texture);
		return NULL;
	}

	SDL_Surface* optimalized_surface = SDL_CreateRGBSurface(0, position.w, position.h, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);

	if (optimalized_surface == NULL) {
		ERROR(SDL_GetError());
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
		ERROR(SDL_GetError());
		free(texture);
		return NULL;
	}

	texture->dst = position;
	texture->renderer = renderer;

	return texture;

}

void Texture_Destroy(Texture* texture) {
	SDL_DestroyTexture(texture->texture);
	free(texture);
}

void Texture_Render(Texture* texture) {
	SDL_RenderCopy(texture->renderer, texture->texture, NULL, &texture->dst);
}

void Texture_ChangePosition(Texture* texture, int x, int y) {
	texture->dst.x = x;
	texture->dst.y = y;
}