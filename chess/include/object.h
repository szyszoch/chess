#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <malloc.h>
#include <stdbool.h>
#include "log.h"
#include "board.h"

#define WINDOW_TITLE "Chess"
#define WINDOW_WIDTH 900
#define WINDOW_HEIGHT 600

#define INVALID_OBJECT 999999



typedef void (*void_func_ptr)();

typedef enum ButtonEvent {
	BUTTONEVENT_FUNC,
	BUTTONEVENT_BOOL
} ButtonEvent;

typedef enum ButtonState {
	BUTTONSTATE_NORMAL,
	BUTTONSTATE_HOVER
} ButtonState;



// Forms

typedef struct Button_F {

	const char* font_path;
	int font_size;
	SDL_Color background_color;
	SDL_Color background_color_hover;
	SDL_Color text_color;
	int event_type;

} Button_F;

typedef struct Text_F {
	int size;
	SDL_Color color;
	const char* font_path;
} Text_F;



extern SDL_Renderer* renderer;
extern SDL_Window* window;
extern SDL_Event event_handler;

int InitRenderer();
void DestroyRenderer();
int ErrorCount();

void CleanRenderer();

void RenderObjects();
void RenderObject(unsigned int id);
void RenderObjectAt(unsigned int id, int x, int y, int w, int h);
void HideObject(unsigned int id); // doesn't matter when call RenderObjectAt() function

void HandleObjectEvent(unsigned int id);
void HandleObjectsEvent();

void ReserveObjectMemory(unsigned int num);
void DestroyObject(unsigned int id);

void SetObjectPosition(unsigned int id, int x, int y);
void SetObjectPositionAndDimensions(unsigned int id, int x, int y, int w, int h);

unsigned int LoadTexture(const char* path);
unsigned int CreateText(const char* title, Text_F* text_form);
unsigned int CreateRect(Uint32 color, int width, int height);
void MergeTextures(unsigned int src, SDL_Rect pos, unsigned int dst);

unsigned int CreateButton(const char* title, SDL_Rect position, Button_F* button_form, int event_type);
void SetButtonEvent(unsigned int id, void_func_ptr function);

unsigned int CreateMessageBox(const char* title, SDL_Rect pos, Button_F* button_form, Text_F* text_form);

unsigned int CreateChess(SDL_Rect pos);

Board* GetChessBoard(unsigned int id);