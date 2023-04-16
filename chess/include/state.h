#pragma once
#include <stdbool.h>

#include "network.h"

#include "objects/button.h"
#include "objects/chess.h"
#include "objects/text.h"
#include "objects/inputbox.h"

enum States {
	STATE_QUIT,
	STATE_MENU,
	STATE_LOCALGAME,
	STATE_NETWORKGAME,
	STATE_JOINGAME,
	STATE_CREATEGAME
};

extern int app_state;

bool init();
void quit();
void menu();
void local_game();
void network_game();
void join_game();
void create_game();

void ev_exit_program();
void ev_goto_menu();
void ev_goto_localgame();
void ev_goto_networkgame();
void ev_goto_joingame();
void ev_goto_creategame();
