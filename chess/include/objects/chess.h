#pragma once
#include <stdbool.h>
#include "renderer.h"
#include "objects/object.h"
#include "objects/texture.h"
#include "math.h"

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

typedef struct Chess Chess;

Chess* c_create();
void c_destroy(Chess* chess);
void c_render(Chess* chess);
void c_handle(Chess* chess);
TextureID c_get_texture_id(ChessType type, ChessTeam team);
Object* c_get_object(Chess* chess);
ChessTeam c_get_turn(Chess* chess);
Move c_get_last_move(Chess* chess);
void c_newgame(Chess* board);
bool c_gameover(Chess* chess);

void Board_Copy(Chess* src, Chess* dst);
void Board_TestGameOver(Chess* board);

void Board_Move(Chess* board, Move move);
bool Board_CanMove(Chess* board, Move move);
bool Board_Pattern(Chess* board, Move move, MoveType move_type);
bool Board_IsMoveBlocked(Chess* board,Move move);

void Board_ChangeTurn(Chess* board);

void Board_FindKing(Chess* board, ChessTeam team, int* x, int* y);
void Board_UpdateDangerZone(Chess* board);
void Board_ChangePawn(Chess* board, ChessType chess);