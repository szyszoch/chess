#include "objects/object.h"

bool is_object_hover(Object* o)
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	SDL_Point mouse_point = { x, y };
	return (SDL_PointInRect(&mouse_point, &o->pos));
}

bool is_object_clicked(Object* o)
{
	return (is_object_hover(o) && event_handler.button.button == SDL_BUTTON_LEFT);
}

void set_object_position(Object* o, int x, int y)
{
	o->pos.x = x;
	o->pos.y = y;
}

void set_object_position_and_dimensions(Object* o, int x, int y, int w, int h) 
{
	o->pos.x = x;
	o->pos.y = y;
	o->pos.w = w;
	o->pos.h = h;
}

void hide_object(Object* o)
{
	o->hidden = true;
}

void freeze_object(Object* o)
{
	o->frozen = true;
}

void unfreeze_object(Object* o)
{
	o->frozen = false;
}
