#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdbool.h>
#include "math.h"
#include "log.h"

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

typedef struct Piece {
	int chess_type;
	int team;
} Piece;

typedef struct Board {
	Piece piece[8][8];
	int turn;
	int winner;
	bool gameover;
	int select_x;
	int select_y;
	Move last_move;
} Board;

typedef bool bool88[8][8];

void Board_Restart(Board* board);
void Board_Copy(Board* src, Board* dst);
void Board_TestGameOver(Board* board);

void Board_Move(Board* board, Move move);
bool Board_CanMove(Board* board, Move move);
bool Board_Pattern(Board* board, Move move, MoveType move_type);
bool Board_IsMoveBlocked(Board* board,Move move);

void Board_ChangeTurn(Board* board);

bool Board_IsKingInDanger(Board* board, ChessTeam team);
bool Board_KingCannotMove(Board* board, ChessTeam team);
bool Board_CanProtectKing(Board* board, Move move, ChessTeam team);
void Board_GetKingDangerZone(Board* board, ChessTeam team, bool88 king_danger_zone);
bool Board_GameOver(Board* board, ChessTeam team);