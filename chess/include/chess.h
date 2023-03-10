#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdbool.h>
#include "texture.h"
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

typedef struct Chess Chess;
typedef struct Board Board;
typedef struct Piece Piece;
typedef bool bool88[8][8];

void Chess_Render(Chess* chess);
void Chess_Event(Chess* chess, SDL_Event* events);
Chess* Chess_Init(SDL_Renderer* renderer, SDL_Rect position);
void Chess_Destroy(Chess* chess);
int Chess_GetTurn(Chess* chess);

bool Board_IsKingInDanger(Board* board, ChessTeam team);
bool Board_KingCannotMove(Board* board, ChessTeam team);
bool Board_GameOver(Chess* chess);
bool Board_CanProtectKing(Board* board, int src_x, int src_y, int dst_x, int dst_y, ChessTeam team);
void Board_GetKingDangerZone(Board* board, ChessTeam team, bool88 king_danger_zone);
void Board_Restart(Board* board);
void Board_Move(Board* board, int src_x, int src_y, int dst_x, int dst_y);
bool Board_CanMove(Board* board, int src_x, int src_y, int dst_x, int dst_y);
void Board_Copy(Board* src, Board* dst);
bool Board_Pattern(		Board* board, int src_x, int src_y, int dst_x, int dst_y);
bool Board_Pattern_Bishop(		Board* board, int src_x, int src_y, int dst_x, int dst_y);
bool Board_Pattern_King(		Board* board, int src_x, int src_y, int dst_x, int dst_y);
bool Board_Pattern_Knight(		Board* board, int src_x, int src_y, int dst_x, int dst_y);
bool Board_Pattern_Pawn_Move(	Board* board, int src_x, int src_y, int dst_x, int dst_y);
bool Board_Pattern_Pawn_Capture(Board* board, int src_x, int src_y, int dst_x, int dst_y);
bool Board_Pattern_Queen(		Board* board, int src_x, int src_y, int dst_x, int dst_y);
bool Board_Pattern_Rook(		Board* board,  int src_x, int src_y, int dst_x, int dst_y);
