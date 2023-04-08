#include "objects/messagebox.h"

typedef struct MessageBox {
	SDL_Texture* texture;
	Button* button;
	Object o;
} MessageBox;

MessageBox* mb_create(const char* title, SDL_Rect pos)
{
	MessageBox* mb = malloc(sizeof(MessageBox));
	if (mb == NULL) {
		LOG_ERROR("Can't allocate memory");
		goto error_messagebox;
	}

	SDL_Texture* texture = create_rect(pos, COLOR_WHITE);
	if (texture == NULL) {
		LOG_ERROR("Can't create rect");
		goto error_texture;
	}

	SDL_Texture* contour = create_contour(pos, COLOR_BLACK, 3);
	if (contour == NULL) {
		LOG_ERROR("Can't create contour");
		goto error_contour;
	}

	SDL_Texture* text = create_text(title, FONT_COLOR, pos.w);
	if (text == NULL) {
		LOG_ERROR("Can't create text");
		goto error_text;
	}

	merge_textures_r(contour, NULL, texture, NULL);

	SDL_Rect tex_pos = { 0,0,0,0 };
	SDL_QueryTexture(text, NULL, NULL, &tex_pos.w, &tex_pos.h);
	center_x_to(&tex_pos, (SDL_Rect) { 0, 0, pos.w, pos.h });
	merge_textures_r(text, NULL, texture, &tex_pos);

	SDL_Rect button_pos = { pos.w,pos.y + pos.h - HALF(pos.h) - 3,HALF(pos.w) + QUARTER(pos.w),HALF(pos.h) };
	center_x_to(&button_pos, pos);
	mb->button = b_create("Ok", button_pos, NULL);

	if (mb->button == NULL) {
		LOG_ERROR("Can't create button");
		goto error_button;
	}

	mb->texture = texture;
	mb->o.pos = pos;

	return mb;

error_text:
	SDL_DestroyTexture(contour);
error_contour:
	SDL_DestroyTexture(texture);
error_texture:
error_button:
	free(mb);
error_messagebox:
	return NULL;
}

void mb_destroy(MessageBox* mb)
{
	if (mb == NULL)
		return;
	SDL_DestroyTexture(mb->texture);
	b_destroy(mb->button);
	free(mb);
}

void mb_render(MessageBox* mb)
{
	SDL_RenderCopy(renderer, mb->texture, NULL, &mb->o.pos);
	b_render(mb->button);
}

void mb_handle(MessageBox* mb)
{
	if (b_handle(mb->button)) {
		mb_destroy(mb);
	}
}