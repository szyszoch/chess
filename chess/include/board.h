#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdbool.h>
#include "texture.h"


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


typedef struct Board Board;
typedef struct Piece Piece;

Board* Board_Init(SDL_Renderer* renderer, SDL_Rect position);
void Board_Destroy(Board* board);
void Board_Render(Board* board);
void Board_Event(Board* board, SDL_Event* events);
void Board_Restart(Board* board);
void Board_Move(Board* board, int src_x, int src_y, int dst_x, int dst_y);