#pragma once
#include <memory.h>

#include "network.h"
#include "renderer.h"
#include "events.h"
#include "objects/board.h"

typedef enum GameMode {
	GAMEMODE_LOCAL,
	GAMEMODE_NETWORK
} GameMode;

typedef struct Chess Chess;

Chess* chess_create(const SDL_Rect* pos, GameMode gm);
void chess_destroy(Chess* chess);
void chess_render(Chess* chess);
void chess_handle(Chess* chess);
ChessTeam chess_get_turn(Chess* chess);
TextureID chess_get_texture_id(ChessType type, ChessTeam team);
bool chess_is_gameover(Chess* chess);

static Move chess_move_piece(Chess* chess);
static ChessTeam chess_team_of_player_on_network_mode(Chess* chess);
static void chess_send_move_throught_network(Move move);
static Move chess_receive_move_from_network();