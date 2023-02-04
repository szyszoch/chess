#include "button.h"

typedef struct Button {
	void_func_ptr events;
	SDL_Texture* sprite[2];
	SDL_Rect position;
	SDL_Renderer* renderer;
	int type;
} Button;

Button* Button_Init(SDL_Renderer* renderer, TTF_Font* font, const char* title, SDL_Rect position, SDL_Color background_color, SDL_Color text_color) {
	
	Button* button = malloc(sizeof(Button));
	
	if (button == NULL) {
		ERROR("Can't allocate memory");
		return NULL;
	}

	SDL_Surface* text = TTF_RenderText_Solid(font, title, text_color);

	if (text == NULL) {
		ERROR(SDL_GetError());
		free(button);
		return NULL;
	}

	SDL_Surface* normal_sprite = SDL_CreateRGBSurface(0, position.w, position.h, 32, 0xFF000000,0x00FF0000, 0x0000FF00, 0x000000FF);

	if (normal_sprite == NULL) {
		ERROR(SDL_GetError());
		SDL_FreeSurface(text);
		free(button);
		return NULL;
	}

	SDL_Surface* hover_sprite = SDL_CreateRGBSurface(0, position.w, position.h, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);

	if (hover_sprite == NULL) {
		ERROR(SDL_GetError());
		SDL_FreeSurface(text);
		SDL_FreeSurface(normal_sprite);
		free(button);
		return NULL;
	}

	Uint32 normal_sprite_color = (background_color.r << 24) | (background_color.g << 16) | (background_color.b << 8) | (background_color.a);
	Uint32 hover_sprite_color = ((background_color.r + 30) << 24) | ((background_color.g + 30) << 16) | ((background_color.b + 30) << 8) | (background_color.a);

	SDL_FillRect(normal_sprite, NULL, normal_sprite_color);
	SDL_FillRect(hover_sprite, NULL, hover_sprite_color);

	SDL_Rect center_text = {position.w/2 - text->w/2, position.h / 2 - text->h/2,text->w,text->h};

	SDL_BlitSurface(text, NULL, normal_sprite, &center_text);
	SDL_BlitSurface(text, NULL, hover_sprite, &center_text);

	button->sprite[BUTTON_NORMAL] = SDL_CreateTextureFromSurface(renderer, normal_sprite);
	button->sprite[BUTTON_HOVER] = SDL_CreateTextureFromSurface(renderer, hover_sprite);

	SDL_FreeSurface(normal_sprite);
	SDL_FreeSurface(hover_sprite);
	SDL_FreeSurface(text);

	if (button->sprite[BUTTON_NORMAL] == NULL || button->sprite[BUTTON_HOVER] == NULL) {
		ERROR(SDL_GetError());
		SDL_DestroyTexture(button->sprite[BUTTON_NORMAL]);
		SDL_DestroyTexture(button->sprite[BUTTON_HOVER]);
		free(button);
		return NULL;
	}

	button->renderer = renderer;
	button->position = position;
	button->type = BUTTON_NORMAL;
	button->events = Empty_Function;

	return button;
}

void Button_Destroy(Button* button) {
	
	if (button == NULL)
		return;
	if (button->sprite[BUTTON_NORMAL] != NULL)
		SDL_DestroyTexture(button->sprite[BUTTON_NORMAL]);
	if (button->sprite[BUTTON_HOVER] != NULL)
		SDL_DestroyTexture(button->sprite[BUTTON_HOVER]);

	free(button);
}

void Button_Render(Button* button) {
	SDL_RenderCopy(button->renderer, button->sprite[button->type], NULL, &button->position);
}

void Button_Event(Button* button, SDL_Event* events) {
	
	if (events->type == SDL_MOUSEMOTION) {
		int x = 0;
		int y = 0;
		SDL_GetMouseState(&x, &y);
		SDL_Rect point = { x,y,1,1 };
		if (SDL_HasIntersection(&button->position,&point)) {
			button->type = BUTTON_HOVER;
		}
		else {
			button->type = BUTTON_NORMAL;
		}
	}

	if (events->button.button == SDL_BUTTON_LEFT && events->type == SDL_MOUSEBUTTONDOWN) {
		if (button->type == BUTTON_HOVER) {
			button->events();
		}
	}
	
}

void Button_SetEvent(Button* button, void_func_ptr function) {
	button->events = function;
}

void Empty_Function() {}