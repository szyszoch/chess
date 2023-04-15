#pragma once
#include <SDL.h>
#include <stdbool.h>
#include <memory.h>

#include "log.h"

typedef struct Board {
	int type[8][8];
	int team[8][8];
} Board;

typedef enum ChessTeam {
	TEAM_NONE = -1,
	TEAM_WHITE,
	TEAM_BLACK,
	TEAMS_COUNT
} ChessTeam;

typedef enum ChessType {
	CHESS_NONE = -1,
	CHESS_BISHOP,
	CHESS_KING,
	CHESS_KNIGHT,
	CHESS_PAWN,
	CHESS_QUEEN,
	CHESS_ROOK,
	CHESSES_COUNT
}  ChessType;

typedef enum MoveType {
	MOVE_MOVE,
	MOVE_CAPTURE
} MoveType;

typedef struct Move {
	int src_x;
	int src_y;
	int dst_x;
	int dst_y;
} Move;

void board_restart(Board* board);
void board_test_gameover(Board* board);
bool board_is_move_blocked(const Board* board, Move move);
void board_find_king(const Board* board, ChessTeam team, int* x, int* y);
void board_get_dangerzone(const Board* board, ChessTeam team, bool danger_zone[8][8]);
bool board_is_gameover(const Board* board, ChessTeam team);

void board_move(Board* board, Move move);
bool board_can_move(const Board* board, Move move);
bool board_check_move_validation(Move move);
bool board_can_protect_king(const Board* board, Move move);

bool board_pattern(const Board* board, MoveType move_type, Move move);
bool board_pattern_bishop(const Board* board, MoveType move_type, Move move);
bool board_pattern_king(const Board* board, MoveType move_type, Move move);
bool board_pattern_knight(const Board* board, MoveType move_type, Move move);
bool board_pattern_pawn(const Board* board, MoveType move_type, Move move);
bool board_pattern_queen(const Board* board, MoveType move_type, Move move);
bool board_pattern_rook(const Board* board, MoveType move_type, Move move);