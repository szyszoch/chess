#include "objects/object_container.h"

typedef struct ObjectContainer {
	int type;
	Objects o;
} ObjectContainer;

static ObjectContainer* object = NULL;
static unsigned int object_count = 0;

static unsigned int create_object()
{
	unsigned int id = check_for_empty_space_in_object_container();

	if (id == INVALID_OBJECT) {
		id = object_count;
		if (!reserve_object_memory(1))
			return INVALID_OBJECT;
	}

	memset(&object[id], 0, sizeof(ObjectContainer));
	return id;
}

bool reserve_object_memory(unsigned int count)
{
	ObjectContainer* new_object = realloc(object, (object_count + count) * sizeof(ObjectContainer));

	if (new_object == NULL) {
		LOG_ERROR("Can't allocate memory");
		return false;
	}

	object = new_object;

	for (unsigned int i = object_count; i < object_count + count; i++) {
		memset(&object[i], 0, sizeof(ObjectContainer));
	}

	object_count += count;
	return true;
}

static unsigned int check_for_empty_space_in_object_container()
{
	for (unsigned int i = 0; i < object_count; i++) {
		if (object[i].type == OBJECT_NONE)
			return i;
	}

	return INVALID_OBJECT;
}

inline static bool check_validation_of_object(unsigned int id)
{
	return	(id >= object_count) ? false : (object[id].type == OBJECT_NONE) ? false : true;
}

static void destroy_object(unsigned int id)
{
	if (!check_validation_of_object(id)) {
		return;
	}

	switch (object[id].type) {
	case OBJECT_TEXTURE:	{t_destroy(object[id].o.texture);			break; }
	case OBJECT_BUTTON:		{b_destroy(object[id].o.button);			break; }
	case OBJECT_MESSAGEBOX: {mb_destroy(object[id].o.message_box);	break; }
	case OBJECT_CHESS:		{c_destroy(object[id].o.chess);			break; }
	}

	object[id].type = OBJECT_NONE;
}

void destroy_objects()
{
	for (unsigned int i = 0; i < object_count; i++)
		destroy_object(i);
	free(object);
	object = NULL;
	object_count = 0;
}

void render_objects()
{
	for (unsigned int i = 0; i < object_count; i++) {
		render_object(i);
	}
	SDL_RenderPresent(renderer);
	SDL_RenderClear(renderer);
}

static void render_object(unsigned int id)
{
	if (!check_validation_of_object(id)) {
		return;
	}

	switch (object[id].type) {
	case OBJECT_TEXTURE:	{t_render(object[id].o.texture);			break; }
	case OBJECT_BUTTON:		{b_render((object[id].o.button));			break; }
	case OBJECT_MESSAGEBOX: {mb_render((object[id].o.message_box));	break; }
	case OBJECT_CHESS:		{c_render((object[id].o.chess));			break; }
	}
}

void handle_objects()
{
	SDL_PollEvent(&event_handler);

	for (unsigned int i = 0; i < object_count; i++) {
		handle_object(i);
	}
}

static void handle_object(unsigned int id)
{
	if (!check_validation_of_object(id)) {
		return;
	}

	switch (object[id].type) {
	case OBJECT_BUTTON:		{b_handle(object[id].o.button);		break; }
	case OBJECT_MESSAGEBOX: {mb_handle(object[id].o.message_box);	break; }
	case OBJECT_CHESS:		{c_handle(object[id].o.chess);		break; }
	}
}

Objects* get_object(unsigned int id)
{
	if (!check_validation_of_object(id))
		return NULL;

	switch (object[id].type) {
	case OBJECT_TEXTURE:	{return &object[id].o;			break; }
	case OBJECT_BUTTON:		{return &object[id].o;			break; }
	case OBJECT_MESSAGEBOX: {return	&object[id].o;		break; }
	case OBJECT_CHESS:		{return &object[id].o;				break; }
	}

	return NULL;
}



unsigned int create_texture(TextureID id)
{
	unsigned int t_id = create_object();

	if (t_id == INVALID_OBJECT) {
		LOG_ERROR("Can't create object");
		goto error_object;
	}

	object[t_id].o.texture = t_create(id);

	if (object[t_id].o.texture == NULL) {
		LOG_ERROR("Can't create texture");
		goto error_texture;
	}

	object[t_id].type = OBJECT_TEXTURE;

	return t_id;

error_texture:
	destroy_object(t_id);
error_object:
	return INVALID_OBJECT;
}

unsigned int create_button(const char* title, SDL_Rect pos, void_func_ptr func)
{
	unsigned int id = create_object();
	if (id == INVALID_OBJECT) {
		LOG_ERROR("Can't create object");
		goto error_object;
	}
		
	object[id].o.button = b_create(title, pos, func);
	if (object[id].o.button == NULL) {
		LOG_ERROR("Can't create button");
		goto error_button;
	}

	object[id].type = OBJECT_BUTTON;

	return id;

error_button:
	destroy_object(id);
error_object:
	return INVALID_OBJECT;
}

unsigned int create_messagebox(const char* title, SDL_Rect pos)
{
	unsigned int id = create_object();
	if (id == INVALID_OBJECT) {
		LOG_ERROR("Can't create object");
		goto error_object;
	}

	object[id].o.message_box = mb_create(title,pos);
	if (object[id].o.message_box == NULL) {
		LOG_ERROR("Can't create message box");
		goto error_messagebox;
	}

	object[id].type = OBJECT_BUTTON;

	return id;

error_messagebox:
	destroy_object(id);
error_object:
	return INVALID_OBJECT;
}

unsigned int create_chess(SDL_Rect pos)
{
	unsigned int id = create_object();
	if (id == INVALID_OBJECT) {
		LOG_ERROR("Can't create object");
		goto error_object;
	}

	object[id].o.chess = c_create();
	if (object[id].o.chess == NULL) {
		LOG_ERROR("Can't create chess");
		goto error_chess;
	}

	object[id].type = OBJECT_CHESS;
	c_get_object(object[id].o.chess)->pos = pos;

	return id;

error_chess:
	destroy_object(id);
error_object:
	return INVALID_OBJECT;
}
