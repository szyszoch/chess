#include "events.h"

static SDL_Event events;
static const Uint8* keys;
static SDL_Point cursor_pos;

void update()
{
	SDL_PollEvent(&events);
	keys = SDL_GetKeyboardState(NULL);
	SDL_GetMouseState(&cursor_pos.x, &cursor_pos.y);
}

bool pressed_key(SDL_Scancode code)
{
	return keys[code];
}

bool pressed_quit()
{
	return (events.type == SDL_QUIT);
}

bool hover_rect(const SDL_Rect* rect)
{
	return SDL_PointInRect(&cursor_pos, rect);
}

bool clicked_rect(const SDL_Rect* rect)
{
	return (hover_rect(rect) && events.button.clicks);
}

bool clicked()
{
	return events.button.clicks;
}

void center_to_cursor(SDL_Rect* rect)
{
	rect->x = cursor_pos.x - rect->w;
	rect->y = cursor_pos.y - rect->h;
}

void center_x_to_rect(int* x, const SDL_Rect* rect)
{
	*x = rect->x + rect->w / 2;
}

void center_y_to_rect(int* y, const SDL_Rect* rect)
{
	*y = rect->y + rect->h / 2;
}

void center_rect_to_rect_x(SDL_Rect* src, const SDL_Rect* dst)
{
	src->x = dst->x + dst->w / 2 - src->w / 2;
}

void center_rect_to_rect_y(SDL_Rect* src, const SDL_Rect* dst)
{
	src->y = dst->y + dst->h / 2 - src->h / 2;
}

void center_rect_to_rect(SDL_Rect* src, const SDL_Rect* dst)
{
	center_rect_to_rect_x(src, dst);
	center_rect_to_rect_y(src, dst);
}

void change_rect_dim(SDL_Rect* rect, int w, int h)
{
	rect->w = w;
	rect->h = h;
}

void change_rect_pos(SDL_Rect* rect, int x, int y)
{
	rect->x = x;
	rect->y = y;
}

void get_mouse_pos(int* x, int* y)
{
	*x = cursor_pos.x;
	*y = cursor_pos.y;
}

bool pressed_left_button()
{
	return (events.button.button == SDL_BUTTON_LEFT && events.type == SDL_MOUSEBUTTONDOWN);
}

bool released_left_button()
{
	return (events.button.button == SDL_BUTTON_LEFT && events.type == SDL_MOUSEBUTTONUP);
}

char get_text_input()
{
	return events.text.text[0];
}

bool is_input_event()
{
	return (events.type == SDL_TEXTINPUT);
}