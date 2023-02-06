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

	texture->texture = IMG_LoadTexture(renderer, path);

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