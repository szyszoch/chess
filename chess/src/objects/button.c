#include "objects/button.h"

typedef struct Button {
	void_func_ptr func;
	SDL_Texture* texture[2];
	SDL_Rect pos;
} Button;

Button* button_create(const char* title, SDL_Rect pos, void_func_ptr func)
{
	Button* new_bn = malloc(sizeof(Button));
	if (new_bn == NULL) {
		LOG_ERROR(SDL_LOG_CATEGORY_SYSTEM,"Can't allocate memory");
		return NULL;
	}
	new_bn->texture[BUTTON_STATE_NORMAL] = create_empty_texture(pos);
	new_bn->texture[BUTTON_STATE_HOVER] = create_empty_texture(pos);
	add_background(new_bn->texture[BUTTON_STATE_NORMAL],BUTTON_BACKGROUND_COLOR);
	add_background(new_bn->texture[BUTTON_STATE_HOVER], BUTTON_HOVER_BACKGROUND_COLOR);
	add_text_centered(new_bn->texture[BUTTON_STATE_NORMAL], title, BUTTON_TEXT_COLOR, pos.h*2/3, 0);
	add_text_centered(new_bn->texture[BUTTON_STATE_HOVER], title, BUTTON_TEXT_COLOR, pos.h*2/3, 0);
	new_bn->pos = pos;
	new_bn->func = func;

	return new_bn;
}

void button_destroy(Button* bn)
{
	if (bn == NULL)
		return;
	SDL_DestroyTexture(bn->texture[BUTTON_STATE_NORMAL]);
	SDL_DestroyTexture(bn->texture[BUTTON_STATE_HOVER]);
	free(bn);
}

void button_render(Button* bn)
{
	if (hover_rect(&bn->pos))
		render(bn->texture[BUTTON_STATE_HOVER], NULL, &bn->pos);
	else 
		render(bn->texture[BUTTON_STATE_NORMAL], NULL, &bn->pos);
}

void button_handle(Button* bn)
{
	if (button_clicked(bn)) {
		if (bn->func != NULL) 
			bn->func();
	}
}

bool button_clicked(Button* bn)
{
	return clicked_rect(&bn->pos);
}