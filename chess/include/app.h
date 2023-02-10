#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdbool.h>
#include "log.h"
#include "button.h"
#include "texture.h"
#include "chess.h"

#define WINDOW_TITLE "Chess"
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define STATE_QUIT 0
#define STATE_MENU 1
#define STATE_LOCALGAME 2
#define STATE_JOINGAME 3
#define STATE_CREATEGAME 4

typedef struct App {

	int state;
	SDL_Renderer* renderer;
	SDL_Window* window;
	SDL_Event events;
	Uint32 window_flags;

	Texture** texture;
	int ntexture;
	Button** button;
	int nbutton;
	Chess** chess;
	int nchess;

} App;

void App_Init();
void App_Destroy();
void App_Render();
void App_HandleEvent();
void App_Delay();
int App_State();
void App_StateClean();

void App_State_Menu();
void App_State_LocalGame();

void App_Event_Exit();
void App_Event_GoToMenu();
void App_Event_GoToLocalGame();
void App_Event_GoToJoinGame();
void App_Event_GoToCreateGame();
