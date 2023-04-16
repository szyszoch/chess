#include "objects/inputbox.h"

typedef struct InputBox {
	SDL_Texture* texture;
	SDL_Rect pos;
	char* text;
	unsigned int len;
	unsigned int max_lettes;
	bool focus;
} InputBox;

InputBox* inputbox_create(SDL_Rect pos, unsigned int max_letters)
{
	InputBox* inb = malloc(sizeof(InputBox));

	if (inb == NULL) {
		LOG_ERROR(SDL_LOG_CATEGORY_SYSTEM, "Can't allocate memory");
		return NULL;
	}

	memset(inb, 0, sizeof(InputBox));
	inb->max_lettes = max_letters;
	inb->pos = pos;

	inb->text = malloc(sizeof(char)* (max_letters+1));

	if (inb->text == NULL) {
		LOG_ERROR(SDL_LOG_CATEGORY_SYSTEM, "Can't allocate memory");
		free(inb);
		return NULL;
	}

	memset(inb->text, 0, sizeof(char) * (max_letters + 1));

	inputbox_update(inb);
	return inb;
}

void inputbox_destroy(InputBox* inb)
{
	free(inb->text);
	free(inb);
}

void inputbox_render(InputBox* inb)
{
	render(inb->texture, NULL, &inb->pos);
}

void inputbox_handle(InputBox* inb)
{
	if (clicked())
		inb->focus = clicked_rect(&inb->pos);
	
	if (!inb->focus)
		return;

	if (pressed_key(SDL_SCANCODE_BACKSPACE)) {
		if (inb->len == 0)
			return;
		inb->len--;
		inb->text[inb->len] = 0;
	}

	else {
		if (inb->max_lettes == inb->len)
			return;

		if (!is_input_event())
			return;

		char c = get_text_input();

		if (!c)
			return;

		inb->text[inb->len] = c;
		inb->len++;
	}

	inputbox_update(inb);
}

const char* inputbox_get_input(InputBox* inb)
{
	return inb->text;
}

void inputbox_update(InputBox* inb)
{
	if (inb->texture != NULL)
		SDL_DestroyTexture(inb->texture);
	inb->texture = create_empty_texture(inb->pos);
	add_background(inb->texture, COLOR_WHITE);
	add_border(inb->texture, COLOR_BLACK, 3);
	if (inb->len)
		add_text_centered_y(inb->texture, inb->text, COLOR_BLACK,inb->pos.h*2/3,0);
}