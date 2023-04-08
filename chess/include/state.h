#pragma once
#include "log.h"
#include "objects/object_container.h"
#include "network.h"

#define STATE_QUIT 0
#define STATE_MENU 1
#define STATE_LOCALGAME 2
#define STATE_NETWORKGAME 3
#define STATE_JOINGAME 4
#define STATE_CREATEGAME 5

extern int app_state;

void menu();
void local_game();
void network_game();
void join_game();
void create_game();

void ev_exit_program();
void ev_goto_menu();
void ev_goto_localgame();
void App_Event_GoToNetworkGame();
void ev_goto_joingame();
void ev_goto_creategame();
