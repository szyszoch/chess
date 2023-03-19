#include "renderer.h"

typedef enum ObjectType {
	OBJECT_NONE,
	OBJECT_TEXTURE,
	OBJECT_BUTTON,
	OBJECT_MESSAGEBOX
} ObjectType;

SDL_Renderer* renderer = NULL;
SDL_Window* window = NULL;
SDL_Event event_handler;

int error = 0;

typedef struct Texture {
	SDL_Texture* texture;
} Texture;

typedef struct Button {
	void_func_ptr func;
	bool click;
	SDL_Texture* texture[2];
	int button_state;
	int event_type;
} Button;

typedef struct MessageBox {
	unsigned int texture;
	unsigned int button;
} MessageBox;


typedef struct Object {
	int type;
	union object {
		Texture texture;
		Button button;
		MessageBox message_box;
	};
	SDL_Rect dst;
} Object;


Object* object = NULL;
unsigned int objectn = 0;

int InitRenderer() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		LOG_ERROR(SDL_GetError());
		error++;
		return -1;
	}

	if (IMG_Init(IMG_INIT_PNG) == 0) {
		LOG_ERROR(SDL_GetError());
		error++;
		return -2;
	}

	if (TTF_Init() == -1) {
		LOG_ERROR(SDL_GetError());
		error++;
		return -3;
	}

	window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

	if (window == NULL) {
		LOG_ERROR(SDL_GetError());
		error++;
		return -4;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (renderer == NULL) {
		LOG_ERROR(SDL_GetError());
		error++;
		return -5;
	}

	return 0;
}

void CleanRenderer() {
	for (unsigned int i = 0; i < objectn; i++) {
		DestroyObject(i);
	}
}

void DestroyRenderer() {

	CleanRenderer();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void DestroyObject(unsigned int id) {

	if (id >= objectn)
		return;
	if (object[id].type != OBJECT_NONE) {
		
		switch (object[id].type) {
		case OBJECT_TEXTURE: {
			if (object[id].texture.texture != NULL)
				SDL_DestroyTexture(object[id].texture.texture);
			break;
		}
		case OBJECT_BUTTON: {
			if (object[id].button.texture[BUTTONSTATE_NORMAL] != NULL)
				SDL_DestroyTexture(object[id].button.texture[BUTTONSTATE_NORMAL]);
			if (object[id].button.texture[BUTTONSTATE_HOVER] != NULL)
				SDL_DestroyTexture(object[id].button.texture[BUTTONSTATE_HOVER]);
			object[id].button.click = false;
			object[id].button.func = NULL;
			object[id].button.event_type = 0;
			object[id].button.button_state = 0;
			break;
		}
		case OBJECT_MESSAGEBOX: {
			DestroyObject(object[id].message_box.texture);
			DestroyObject(object[id].message_box.button);
		}
		}

	}
	object[id].dst = (SDL_Rect){ 0,0,0,0 };
	object[id].type = OBJECT_NONE;
}

void ReserveObjectMemory(unsigned int num) {
	
	if (object == NULL) {
		object = calloc(num, sizeof(Object));
	}
	else {
		Object* new_object = realloc(object, objectn * sizeof(Object));
		if (new_object == NULL) {
			free(new_object);
			LOG_ERROR("Can't allocate memory");
			return;
		}
		object = new_object;

	}
	objectn = num;
}

void RenderObjects() {

	for (unsigned int i = 0; i < objectn; i++) {

		switch(object[i].type) {
		case OBJECT_NONE: {
			continue;
			break;
		}
		case OBJECT_TEXTURE: {
			SDL_RenderCopy(renderer, object[i].texture.texture, NULL, &object[i].dst);
			break;
		}
		case OBJECT_BUTTON: {
			SDL_RenderCopy(renderer, object[i].button.texture[object[i].button.button_state], NULL, &object[i].dst);
			break;
		}
		}

	}

}

void RenderObject(unsigned int id) {

	if (id >= objectn)
		return;
	switch (object[id].type) {
	case OBJECT_NONE: {
		break;
	}
	case OBJECT_TEXTURE: {
		SDL_RenderCopy(renderer, object[id].texture.texture, NULL, &object[id].dst);
		break;
	}
	case OBJECT_BUTTON: {
		SDL_RenderCopy(renderer, object[id].button.texture[object[id].button.button_state], NULL, &object[id].dst);
		break;
	}
	case OBJECT_MESSAGEBOX: {
		RenderObject(object[id].message_box.texture);
		RenderObject(object[id].message_box.button);
		break;
	}
	}
}

unsigned int CreateObject() {

	unsigned int o_id = INVALID_OBJECT;

	for(unsigned int i=0; i < objectn; i++)
		if (object[i].type == OBJECT_NONE) {
			o_id = i;
			break;
		}
	if (o_id == INVALID_OBJECT) {
		o_id = objectn;
		objectn++;
		ReserveObjectMemory(objectn);
	}
	return o_id;
}

void SetObjectPosition(unsigned int id, int x, int y) {
	if (id >= objectn)
		return;

	if (object[id].type == OBJECT_MESSAGEBOX) {
		object[id].dst.x = x;
		object[id].dst.y = y;
		object[object[id].message_box.texture].dst.x = x;
		object[object[id].message_box.texture].dst.y = y;
		object[object[id].message_box.button].dst.x = object[id].dst.w/2 - object[id].dst.w/3;
		object[object[id].message_box.button].dst.y = object[id].dst.h / 2;
	}

	else {
		object[id].dst.x = x;
		object[id].dst.y = y;
	}

	
}

void SetObjectPositionAndDimensions(unsigned int id, int x, int y, int w, int h) {
	if (id >= objectn)
		return;

	if (object[id].type == OBJECT_MESSAGEBOX) {
		object[id].dst.x = x;
		object[id].dst.y = y;
		object[id].dst.h = h;
		object[id].dst.w = w;
		object[object[id].message_box.texture].dst.x = x;
		object[object[id].message_box.texture].dst.y = y;
		object[object[id].message_box.texture].dst.w = w;
		object[object[id].message_box.texture].dst.h = h;
		object[object[id].message_box.button].dst.x = x + w/2 - w / 4;
		object[object[id].message_box.button].dst.y = y + h / 2;
		object[object[id].message_box.button].dst.w = w / 2;
		object[object[id].message_box.button].dst.h = h / 3;
	}

	else {
		object[id].dst.x = x;
		object[id].dst.y = y;
		object[id].dst.h = h;
		object[id].dst.w = w;
	}
	
}

unsigned int LoadTexture(const char* path) {
	
	SDL_Surface* surface = IMG_Load(path);

	if (surface == NULL) {
		LOG_ERROR(SDL_GetError());
		error++;
		return INVALID_OBJECT;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	if (texture == NULL) {
		LOG_ERROR(SDL_GetError());
		error++;
		return INVALID_OBJECT;
	}

	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
	SDL_SetTextureScaleMode(texture, SDL_ScaleModeLinear);

	unsigned int tex_id = CreateObject();

	object[tex_id].texture.texture = texture;
	object[tex_id].type = OBJECT_TEXTURE;
	SDL_QueryTexture(texture, NULL, NULL, &object[tex_id].dst.w, &object[tex_id].dst.h);

	return tex_id;

}

unsigned int CreateButton(const char* title, SDL_Rect position, Button_F* button_form, int event_type) {

	TTF_Font* font = TTF_OpenFont(button_form->font_path, button_form->font_size);

	if (font == NULL) {
		LOG_ERROR(SDL_GetError());
		error++;
		return INVALID_OBJECT;
	}

	SDL_Surface* text = TTF_RenderText_Solid(font, title, button_form->text_color);
	TTF_CloseFont(font);

	if (text == NULL) {
		LOG_ERROR(SDL_GetError());
		error++;
		return INVALID_OBJECT;
	}

	SDL_Surface* normal_sprite = SDL_CreateRGBSurface(0, position.w, position.h, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);

	if (normal_sprite == NULL) {
		LOG_ERROR(SDL_GetError());
		SDL_FreeSurface(text);
		error++;
		return INVALID_OBJECT;
	}

	SDL_Surface* hover_sprite = SDL_CreateRGBSurface(0, position.w, position.h, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);

	if (hover_sprite == NULL) {
		LOG_ERROR(SDL_GetError());
		SDL_FreeSurface(text);
		SDL_FreeSurface(normal_sprite);
		error++;
		return INVALID_OBJECT;
	}

	Uint32 normal_sprite_color = (button_form->background_color.r << 24) | (button_form->background_color.g << 16) | (button_form->background_color.b << 8) | (button_form->background_color.a);
	Uint32 hover_sprite_color = (button_form->background_color_hover.r << 24) | (button_form->background_color_hover.g << 16) | (button_form->background_color_hover.b << 8) | (button_form->background_color_hover.a);

	SDL_FillRect(normal_sprite, NULL, normal_sprite_color);
	SDL_FillRect(hover_sprite, NULL, hover_sprite_color);

	SDL_Rect center_text = { position.w / 2 - text->w / 2, position.h / 2 - text->h / 2,text->w,text->h };

	SDL_BlitSurface(text, NULL, normal_sprite, &center_text);
	SDL_BlitSurface(text, NULL, hover_sprite, &center_text);

	unsigned int b_id = CreateObject();

	object[b_id].button.texture[BUTTONSTATE_NORMAL] = SDL_CreateTextureFromSurface(renderer, normal_sprite);
	object[b_id].button.texture[BUTTONSTATE_HOVER] = SDL_CreateTextureFromSurface(renderer, hover_sprite);

	SDL_FreeSurface(normal_sprite);
	SDL_FreeSurface(hover_sprite);
	SDL_FreeSurface(text);

	if (object[b_id].button.texture[BUTTONSTATE_NORMAL] == NULL || object[b_id].button.texture[BUTTONSTATE_HOVER] == NULL) {
		LOG_ERROR(SDL_GetError());
		DestroyObject(b_id);
		error++;
		return INVALID_OBJECT;
	}

	object[b_id].type = OBJECT_BUTTON;
	object[b_id].dst = position;
	object[b_id].button.button_state = BUTTONSTATE_NORMAL;
	object[b_id].button.event_type = event_type;

	if (event_type == BUTTONEVENT_FUNC)
		object[b_id].button.func = NULL;
	if (event_type == BUTTONEVENT_BOOL)
		object[b_id].button.click = false;

	return b_id;
}

unsigned int CreateText(const char* title, Text_F* text_form) {
	
	TTF_Font* font = TTF_OpenFont(text_form->font_path, text_form->size);

	if (font == NULL) {
		LOG_ERROR(SDL_GetError());
		return INVALID_OBJECT;
	}

	SDL_Surface* surface = TTF_RenderText_Solid(font, title, text_form->color);
	TTF_CloseFont(font);

	if (surface == NULL) {
		LOG_ERROR(SDL_GetError());
		return INVALID_OBJECT;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	if (texture == NULL) {
		LOG_ERROR(SDL_GetError());
		return INVALID_OBJECT;
	}

	unsigned int tex_id = CreateObject();

	object[tex_id].texture.texture = texture;
	SDL_QueryTexture(object[tex_id].texture.texture, NULL, NULL, &object[tex_id].dst.w, &object[tex_id].dst.h);
	object[tex_id].type = OBJECT_TEXTURE;

	return tex_id;

}

unsigned int CreateRect(Uint32 color, int width, int height) {

	SDL_Surface* surface = SDL_CreateRGBSurface(0, width, height, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);

	if (surface == NULL) {
		LOG_ERROR(SDL_GetError());
		return INVALID_OBJECT;
	}

	SDL_FillRect(surface, NULL, color);

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	if (texture == NULL) {
		LOG_ERROR(SDL_GetError());
		return INVALID_OBJECT;
	}

	unsigned int tex_id = CreateObject();
	
	object[tex_id].texture.texture = texture;
	object[tex_id].dst.w = width;
	object[tex_id].dst.h = height;
	object[tex_id].type = OBJECT_TEXTURE;

	return tex_id;
}

void MergeTextures(unsigned int src, SDL_Rect pos, unsigned int dst) {
	if (src >= objectn || dst >= objectn)
		return;

	SDL_SetRenderTarget(renderer, object[dst].texture.texture);
	SDL_RenderCopy(renderer, object[src].texture.texture, NULL, &pos);
	SDL_SetRenderTarget(renderer, NULL);

}

void SetButtonEvent(unsigned int id, void_func_ptr function) {
	if (id >= objectn)
		return;
	if (object[id].type != OBJECT_BUTTON)
		return;
	object[id].button.event_type = BUTTONEVENT_FUNC;
	object[id].button.func = function;
}

void HandleObjectEvent(unsigned int id) {
	
	if (id >= objectn)
		return;

	switch (object[id].type) {
	case OBJECT_NONE: {
		break;
	}
	case OBJECT_TEXTURE: {
		break;
	}
	case OBJECT_BUTTON: {

		bool HOVER = false;
		bool CLICK = false;

		int x = 0;
		int y = 0;
		SDL_GetMouseState(&x, &y);
		SDL_Rect point = { x,y,1,1 };
		if (SDL_HasIntersection(&object[id].dst, &point))
			HOVER = true;

		if (HOVER && event_handler.button.button == SDL_BUTTON_LEFT && event_handler.type == SDL_MOUSEBUTTONDOWN)
			CLICK = true;

		object[id].button.click = false;
		object[id].button.button_state = (HOVER) ? BUTTONSTATE_HOVER : BUTTONSTATE_NORMAL;

		if (CLICK) {
			if (object[id].button.event_type == BUTTONEVENT_BOOL)
				object[id].button.click = true;
			else
				object[id].button.func();
		}

		break;
	}
	case OBJECT_MESSAGEBOX: {
		HandleObjectEvent(object[id].message_box.texture);
		HandleObjectEvent(object[id].message_box.button);
		if (object[object[id].message_box.button].button.click == true) {
			DestroyObject(id);
		}
	}
	}
}

void HandleObjectsEvent() {

	for (unsigned int i = 0; i < objectn; i++) {
		HandleObjectEvent(i);
	}

}

unsigned int CreateMessageBox(const char* title, SDL_Rect pos, Button_F* button_form, Text_F* text_form) {

	unsigned int texture_id = 0;
	unsigned int button_id = 0;

	{ // texture
		Uint32 white = 0xFFFFFFFF;

		SDL_Surface* background = SDL_CreateRGBSurface(0, pos.w, pos.h, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);

		if (background == NULL) {
			LOG_ERROR(SDL_GetError());
			error++;
			return INVALID_OBJECT;
		}

		SDL_FillRect(background, NULL, white);

		TTF_Font* font = TTF_OpenFont(text_form->font_path, text_form->size);

		if (font == NULL) {
			LOG_ERROR(SDL_GetError());
			error++;
			return INVALID_OBJECT;
		}

		SDL_Surface* text = TTF_RenderText_Solid(font, title, text_form->color);
		TTF_CloseFont(font);

		if (text == NULL) {
			LOG_ERROR(SDL_GetError());
			SDL_FreeSurface(background);
			error++;
			return INVALID_OBJECT;
		}

		SDL_Rect text_pos = {pos.w/2 - text->w/2, 0, text->w, text->h};
		
		SDL_BlitSurface(text, NULL, background, &text_pos);
		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, background);
		SDL_FreeSurface(background);
		SDL_FreeSurface(text);

		if (texture == NULL) {
			LOG_ERROR(SDL_GetError());
			SDL_DestroyTexture(texture);
			error++;
			return INVALID_OBJECT;
		}

		texture_id = CreateObject();
		object[texture_id].texture.texture = texture;
		object[texture_id].type = OBJECT_TEXTURE;
	}

	{ // button
		SDL_Rect button_pos = { pos.x + pos.w / 2 - pos.w / 4,pos.h / 2 - (pos.h / 3),pos.w / 2,pos.h / 3 };

		button_id = CreateButton("Ok", button_pos, button_form, BUTTONEVENT_BOOL);

		if (button_id == INVALID_OBJECT) {
			DestroyObject(texture_id);
			error++;
			return INVALID_OBJECT;
		}
	}

	unsigned int m_id = CreateObject();
	object[m_id].message_box.texture = texture_id;
	object[m_id].message_box.button = button_id;
	object[m_id].type = OBJECT_MESSAGEBOX;
	SetObjectPositionAndDimensions(m_id, pos.x, pos.y, pos.w, pos.h);

	return m_id;

}

int ErrorCount() {
	return error;
}

