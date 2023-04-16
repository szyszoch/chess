#include "objects/text.h"

typedef struct Text {
	const char* title;
	SDL_Texture* texture;
	SDL_Rect pos;
} Text;

Text* text_create(const char* title, SDL_Rect pos)
{
	Text* text = malloc(sizeof(Text));

	if (text == NULL) {
		LOG_ERROR(SDL_LOG_CATEGORY_SYSTEM, "Can't allocate memory");
		return NULL;
	}

	memset(text, 0, sizeof(Text));
	text->pos = pos;
	text->title = title;
	text->texture = create_empty_texture(text->pos);
	add_background(text->texture, TEXT_BACKGROUND_COLOR);
	add_border(text->texture, TEXT_BORDER_COLOR, TEXT_BORDER_SIZE);
	add_text_centered(text->texture, text->title, TEXT_COLOR, TEXT_SIZE, 0);

	return text;
}

void text_destroy(Text* text)
{
	if (text == NULL)
		return;
	if (text->texture != NULL)
		SDL_DestroyTexture(text->texture);
	free(text);
}

void text_render(Text* text)
{
	render(text->texture, NULL, &text->pos);
}