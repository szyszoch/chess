#include "objects/button.h"

typedef struct Button {
	void_func_ptr func;
	SDL_Texture* texture[2];
	Object o;
} Button;

Button* b_create(const char* title, SDL_Rect pos, void_func_ptr func)
{
	Button* new_button = malloc(sizeof(Button));
	if (new_button == NULL) {
		LOG_ERROR("Can't allocate memory");
		goto error_button;
	}

	SDL_Texture* normal_texture = create_rect(pos, BUTTON_BACKGROUND_COLOR);
	if (normal_texture == NULL) {
		LOG_ERROR("Can't create rect");
		goto error_normal_texture;
	}

	SDL_Texture* hover_texture = create_rect(pos, BUTTON_HOVER_BACKGROUND_COLOR);
	if (hover_texture == NULL) {
		LOG_ERROR("Can't create rect");
		goto error_hover_texture;
	}

	SDL_Texture* text = create_text(title, BUTTON_TEXT_COLOR, pos.w);
	if (text == NULL) {
		LOG_ERROR("Can't create text");
		goto error_text;
	}

	SDL_Rect text_pos = { 0,0,0,0 };
	SDL_QueryTexture(text, NULL, NULL, &text_pos.w, &text_pos.h);
	center_x_to(&text_pos, (SDL_Rect) { 0, 0, pos.w, pos.h });
	center_y_to(&text_pos, (SDL_Rect) { 0, 0, pos.w, pos.h });

	merge_textures(text, NULL, normal_texture, &text_pos);
	merge_textures_r(text, NULL, hover_texture, &text_pos);
	
	new_button->texture[BUTTON_STATE_NORMAL] = normal_texture;
	new_button->texture[BUTTON_STATE_HOVER] = hover_texture;
	new_button->o.pos = pos;
	new_button->func = func;

	return new_button;

error_text:
	SDL_DestroyTexture(hover_texture);
error_hover_texture:
	SDL_DestroyTexture(normal_texture);
error_normal_texture:
	free(new_button);
error_button:
	return NULL;
}

void b_destroy(Button* button)
{
	if (button == NULL)
		return;
	SDL_DestroyTexture(button->texture[BUTTON_STATE_NORMAL]);
	SDL_DestroyTexture(button->texture[BUTTON_STATE_HOVER]);
	free(button);
}

void b_render(Button* button)
{
	if (is_object_hover(&button->o))
		SDL_RenderCopy(renderer, button->texture[BUTTON_STATE_HOVER], NULL, &button->o.pos);
	else 
		SDL_RenderCopy(renderer, button->texture[BUTTON_STATE_NORMAL], NULL, &button->o.pos);
}

bool b_handle(Button* button)
{
	if (is_object_clicked(&button->o)) {
		if (button->func != NULL) 
			button->func();
		return true;
	}
	return false;
}