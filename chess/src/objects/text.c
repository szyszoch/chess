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
	
	text_update(text);

	return text;
}

void text_update(Text* text)
{
	if (text->texture != NULL)
		SDL_DestroyTexture(text->texture);
	text->texture = create_empty_texture(text->pos);

	SDL_Texture* tex = create_text(text->title, TEXT_COLOR, TEXT_SIZE, 0);
	SDL_Rect tex_pos = { 0,0,0,0 };
	SDL_Rect rect_pos = { 0,0,text->pos.w,text->pos.h };
	SDL_QueryTexture(tex, NULL, NULL, &tex_pos.w, &tex_pos.h);
	center_rect_to_rect(&tex_pos, &rect_pos);

	SDL_Texture* border = create_border(text->pos, TEXT_BORDER_COLOR, TEXT_BORDER_SIZE);
	SDL_Texture* background = create_rect(text->pos, TEXT_BACKGROUND_COLOR);

	merge_textures_r(background, NULL, text->texture, NULL);
	merge_textures_r(border, NULL, text->texture, NULL);
	merge_textures_r(tex, NULL, text->texture, &tex_pos);
}

void text_rename(Text* text, const char* title)
{
	text->title = title;
	text_update(text);
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