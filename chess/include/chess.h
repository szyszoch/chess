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
typedef bool (*ptr_to_pattern)(Board*,int,int,int,int);
typedef bool bool88[8][8];

void Board_Render(Chess* chess);
void Board_Event(Chess* chess, SDL_Event* events);
Chess* Board_Init(SDL_Renderer* renderer, SDL_Rect position);
void Board_Destroy(Chess* chess);

void Board_Restart(Board* board);
void Board_Move(Chess* chess, int src_x, int src_y, int dst_x, int dst_y);
inline void Board_ChangeTurn(Chess* chess);
bool Board_CanMove(Chess* chess, int src_x, int src_y, int dst_x, int dst_y);
bool Board_IsKingInDanger(Chess* chess, ChessTeam team);
void Board_UpdateKingDangerZone(Chess* chess);
bool Board_IsGameOver(Chess* chess);
void Board_GetKingDangerZone(Chess* chess, ChessTeam team, bool88 king_danger_zone);

bool Board_Pattern_Bishop(		Board* board, int src_x, int src_y, int dst_x, int dst_y);
bool Board_Pattern_King(		Board* board, int src_x, int src_y, int dst_x, int dst_y);
bool Board_Pattern_Knight(		Board* board, int src_x, int src_y, int dst_x, int dst_y);
bool Board_Pattern_Pawn(		Board* board, int src_x, int src_y, int dst_x, int dst_y);
bool Board_Pattern_Pawn_Move(	Board* board, int src_x, int src_y, int dst_x, int dst_y);
bool Board_Pattern_Pawn_Capture(Board* board, int src_x, int src_y, int dst_x, int dst_y);
bool Board_Pattern_Queen(		Board* board, int src_x, int src_y, int dst_x, int dst_y);
bool Board_Pattern_Rook(		Board* board,  int src_x, int src_y, int dst_x, int dst_y);
