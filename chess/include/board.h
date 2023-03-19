#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdbool.h>
#include "renderer.h"
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
	int state;
	int team;
} Piece;

typedef struct Board {
	Piece piece[8][8];
	int turn;
	int winner;
	bool gameover;
	int select_x;
	int select_y;
} Board;

typedef bool bool88[8][8];

bool Board_InitTextures();
void Board_Handle_Events(Board* board, SDL_Rect* board_pos, Move* move);
void Board_Render(Board* board, SDL_Rect* board_pos);
void Board_DestroyTextures();
int Board_TextureId(int state, int team);

void Board_ChangeTurn(Board* board);
bool Board_IsKingInDanger(Board* board, ChessTeam team);
bool Board_KingCannotMove(Board* board, ChessTeam team);
bool Board_CanProtectKing(Board* board, int src_x, int src_y, int dst_x, int dst_y, ChessTeam team);
void Board_GetKingDangerZone(Board* board, ChessTeam team, bool88 king_danger_zone);
void Board_Restart(Board* board);
void Board_Move(Board* board, int src_x, int src_y, int dst_x, int dst_y);
bool Board_CanMove(Board* board, int src_x, int src_y, int dst_x, int dst_y);
void Board_Copy(Board* src, Board* dst);
bool Board_Pattern(Board* board, Move move, MoveType move_type);
void Board_TestGameOver(Board* board);
bool Board_IsMoveBlocked(Board* board,Move move);