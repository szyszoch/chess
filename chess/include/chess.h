#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdbool.h>

#include "log.h"
#include "object.h"
#include "board.h"
#include "network.h"

#define STATE_QUIT 0
#define STATE_MENU 1
#define STATE_LOCALGAME 2
#define STATE_NETWORKGAME 3
#define STATE_JOINGAME 4
#define STATE_CREATEGAME 5

extern app_state;

void App_Init();
void App_Destroy();
void App_Delay();

void App_State_Menu();
void App_State_LocalGame();
void App_State_NetworkGame();
void App_State_JoinGame();
void App_State_CreateGame();

void App_Event_Exit();
void App_Event_GoToMenu();
void App_Event_GoToLocalGame();
void App_Event_GoToJoinGame();
void App_Event_GoToCreateGame();
