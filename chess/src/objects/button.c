#include "objects/button.h"

typedef struct Button {
	void_func_ptr func;
	SDL_Texture* texture[2];
	SDL_Rect pos;
} Button;

Button* create_button(const char* title, SDL_Rect pos, void_func_ptr func)
{
	Button* new_bn = malloc(sizeof(Button));
	if (new_bn == NULL) {
		LOG_ERROR(SDL_LOG_CATEGORY_SYSTEM,"Can't allocate memory");
		goto error_button;
	}

	SDL_Texture* normal_tex = create_rect(pos, BUTTON_BACKGROUND_COLOR);
	if (normal_tex == NULL) {
		LOG_ERROR(SDL_LOG_CATEGORY_RENDER, "Can't create rect");
		goto error_normal_texture;
	}

	SDL_Texture* hover_tex = create_rect(pos, BUTTON_HOVER_BACKGROUND_COLOR);
	if (hover_tex == NULL) {
		LOG_ERROR(SDL_LOG_CATEGORY_RENDER, "Can't create rect");
		goto error_hover_texture;
	}

	SDL_Texture* text = create_text(title, BUTTON_TEXT_COLOR, 32, pos.w);
	if (text == NULL) {
		LOG_ERROR(SDL_LOG_CATEGORY_RENDER, "Can't create text");
		goto error_text;
	}

	SDL_Rect text_pos = { 0,0,0,0 };
	SDL_Rect r = { 0,0,pos.w,pos.h };

	SDL_QueryTexture(text, NULL, NULL, &text_pos.w, &text_pos.h);
	center_rect_to_rect(&text_pos, &r);
	center_rect_to_rect(&text_pos, &r);

	merge_textures(text, NULL, normal_tex, &text_pos);
	merge_textures_r(text, NULL, hover_tex, &text_pos);
	
	new_bn->texture[BUTTON_STATE_NORMAL] = normal_tex;
	new_bn->texture[BUTTON_STATE_HOVER] = hover_tex;
	new_bn->pos = pos;
	new_bn->func = func;

	return new_bn;

error_text:
	SDL_DestroyTexture(hover_tex);
error_hover_texture:
	SDL_DestroyTexture(normal_tex);
error_normal_texture:
	free(new_bn);
error_button:
	return NULL;
}

void destroy_button(Button* bn)
{
	if (bn == NULL)
		return;
	SDL_DestroyTexture(bn->texture[BUTTON_STATE_NORMAL]);
	SDL_DestroyTexture(bn->texture[BUTTON_STATE_HOVER]);
	free(bn);
}

void render_button(Button* bn)
{
	if (hover_rect(&bn->pos))
		render(bn->texture[BUTTON_STATE_HOVER], NULL, &bn->pos);
	else 
		render(bn->texture[BUTTON_STATE_NORMAL], NULL, &bn->pos);
}

void handle_button(Button* bn)
{
	if (clicked_rect(&bn->pos)) {
		if (bn->func != NULL) 
			bn->func();
	}
}