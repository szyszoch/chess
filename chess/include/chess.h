#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdbool.h>
#include "log.h"
#include "renderer.h"
#include "board.h"

#define WINDOW_TITLE "Chess"
#define WINDOW_WIDTH 900
#define WINDOW_HEIGHT 600

#define STATE_QUIT 0
#define STATE_MENU 1
#define STATE_GAME 2
#define STATE_JOINGAME 3
#define STATE_CREATEGAME 4

extern app_state;

void App_Init();
void App_Destroy();
void App_Delay();

void App_State_Menu();
void App_State_Game();
void App_State_JoinGame();
void App_State_CreateGame();

void App_Event_Exit();
void App_Event_GoToMenu();
void App_Event_GoToLocalGame();
void App_Event_GoToJoinGame();
void App_Event_GoToCreateGame();
