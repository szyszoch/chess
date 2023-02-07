#include "board.h"

typedef struct Piece {
	int type;
	int team;
} Piece;

typedef struct Board {
	Piece piece[8][8];
	Texture* sprite[TEAMS_COUNT][CHESSES_COUNT];
	Texture* select_sprite;
	Texture* board;
	SDL_Rect position;
	int select_x, select_y;
	int turn;
	int winner;
	bool gameover;
} Board;

Board* Board_Init(SDL_Renderer* renderer, SDL_Rect position) {

	Board* board = malloc(sizeof(Board));

	if (board == NULL) {
		ERROR("Can't allocate memory");
		return NULL;
	}

	board->position = position;

	Board_Restart(board);

	SDL_Rect chess_pos = { 0,0,position.w / 8,position.h / 8 };

	board->sprite[TEAM_BLACK][CHESS_BISHOP] = Texture_Init(renderer, "img/black_bishop.png",	chess_pos);
	board->sprite[TEAM_BLACK][CHESS_KING]	= Texture_Init(renderer, "img/black_king.png",		chess_pos);
	board->sprite[TEAM_BLACK][CHESS_KNIGHT] = Texture_Init(renderer, "img/black_knight.png",	chess_pos);
	board->sprite[TEAM_BLACK][CHESS_PAWN]	= Texture_Init(renderer, "img/black_pawn.png",		chess_pos);
	board->sprite[TEAM_BLACK][CHESS_QUEEN]	= Texture_Init(renderer, "img/black_queen.png",		chess_pos);
	board->sprite[TEAM_BLACK][CHESS_ROOK]	= Texture_Init(renderer, "img/black_rook.png",		chess_pos);
	board->sprite[TEAM_WHITE][CHESS_BISHOP] = Texture_Init(renderer, "img/white_bishop.png",	chess_pos);
	board->sprite[TEAM_WHITE][CHESS_KING]	= Texture_Init(renderer, "img/white_king.png",		chess_pos);
	board->sprite[TEAM_WHITE][CHESS_KNIGHT] = Texture_Init(renderer, "img/white_knight.png",	chess_pos);
	board->sprite[TEAM_WHITE][CHESS_PAWN]	= Texture_Init(renderer, "img/white_pawn.png",		chess_pos);
	board->sprite[TEAM_WHITE][CHESS_QUEEN]	= Texture_Init(renderer, "img/white_queen.png",		chess_pos);
	board->sprite[TEAM_WHITE][CHESS_ROOK]	= Texture_Init(renderer, "img/white_rook.png",		chess_pos);

	board->board = Texture_Init(renderer, "img/board.png", position);
	board->select_sprite = Texture_Init(renderer, "img/select.png", chess_pos);

	for (int i = 0; i < TEAMS_COUNT; i++) {
		for (int j = 0; j < CHESSES_COUNT; j++) {
			if (board->sprite[i][j] == NULL) {
				ERROR(SDL_GetError());
				Board_Destroy(board);
				return NULL;
			}
		}
	}

	if (board->board == NULL) {
		ERROR(SDL_GetError());
		Board_Destroy(board);
		return NULL;
	}

	if (board->select_sprite == NULL) {
		ERROR(SDL_GetError());
		Board_Destroy(board);
		return NULL;
	}

	return board;

}

void Board_Destroy(Board* board) {

	for (int i = 0; i < TEAMS_COUNT; i++) {
		for (int j = 0; j < CHESSES_COUNT; j++) {
			if (board->sprite[i][j] != NULL) {
				Texture_Destroy(board->sprite[i][j]);
			}
		}
	}

	if (board->board != NULL) {
		Texture_Destroy(board->board);
	}

	if (board->select_sprite != NULL) {
		Texture_Destroy(board->select_sprite);
	}

	if (board != NULL)
		free(board);

}

void Board_Render(Board* board) {

	Texture_Render(board->board);

	for (int y = 0; y < 8; y++) {
		
		for (int x = 0; x < 8; x++) {
			
			if (board->piece[x][y].team == TEAM_NONE || board->piece[x][y].type == CHESS_NONE)
				continue;

			Texture_ChangePosition(board->sprite[board->piece[x][y].team][board->piece[x][y].type], x*(board->position.w/8), y * (board->position.h/8));
			Texture_Render(board->sprite[board->piece[x][y].team][board->piece[x][y].type]);

		}

	}

	Texture_ChangePosition(board->select_sprite, (board->select_x*(board->position.w/8)), (board->select_y* (board->position.h / 8)) );
	Texture_Render(board->select_sprite);

}

void Board_Event(Board* board, SDL_Event* events) {

	static bool HOVER = false;

	if (events->type == SDL_MOUSEMOTION) {
		int x = 0;
		int y = 0;
		SDL_GetMouseState(&x, &y);
		SDL_Rect point = { x,y,1,1 };
		if (SDL_HasIntersection(&board->position, &point)) {
			if (HOVER == false) {
				HOVER = true;
			}
		}
		else {
			HOVER = false;
		}
	}

	if (events->button.button == SDL_BUTTON_LEFT && events->type == SDL_MOUSEBUTTONDOWN) {
		if (HOVER) {
			int x = 0;
			int y = 0;
			SDL_GetMouseState(&x, &y);
			x = x / (board->position.w / 8) - board->position.x; 
			y = y / (board->position.h / 8) - board->position.y;

			if (x < 0 || x > 7 || y < 0 || y > 7) {
				ERROR("Array out of scope");
				return;
			}

			if (board->select_x == -1 && board->select_y == -1) {

				if (board->piece[x][y].team == board->turn) {
					board->select_x = x;
					board->select_y = y;
				}

			}

			else {

				if (board->select_x == x && board->select_y == y) {
					board->select_x = -1;
					board->select_y = -1;
				}

				else if (board->piece[x][y].team == board->piece[board->select_x][board->select_y].team) {
					board->select_x = x;
					board->select_y = y;
				}

				else if (board->piece[x][y].team == TEAM_NONE) {
					board->select_x = -1;
					board->select_y = -1;
					return;
				}

			}

		}
	}

}

void Board_Restart(Board* board) {

	board->piece[0][0].type = CHESS_ROOK;	board->piece[0][0].team = TEAM_BLACK;
	board->piece[1][0].type = CHESS_KNIGHT;	board->piece[1][0].team = TEAM_BLACK;
	board->piece[2][0].type = CHESS_BISHOP;	board->piece[2][0].team = TEAM_BLACK;
	board->piece[3][0].type = CHESS_QUEEN;	board->piece[3][0].team = TEAM_BLACK;
	board->piece[4][0].type = CHESS_KING;	board->piece[4][0].team = TEAM_BLACK;
	board->piece[5][0].type = CHESS_BISHOP;	board->piece[5][0].team = TEAM_BLACK;
	board->piece[6][0].type = CHESS_KNIGHT;	board->piece[6][0].team = TEAM_BLACK;
	board->piece[7][0].type = CHESS_ROOK;	board->piece[7][0].team = TEAM_BLACK;

	board->piece[0][1].type = CHESS_PAWN;   board->piece[0][1].team = TEAM_BLACK;
	board->piece[1][1].type = CHESS_PAWN;   board->piece[1][1].team = TEAM_BLACK;
	board->piece[2][1].type = CHESS_PAWN;   board->piece[2][1].team = TEAM_BLACK;
	board->piece[3][1].type = CHESS_PAWN;   board->piece[3][1].team = TEAM_BLACK;
	board->piece[4][1].type = CHESS_PAWN;   board->piece[4][1].team = TEAM_BLACK;
	board->piece[5][1].type = CHESS_PAWN;   board->piece[5][1].team = TEAM_BLACK;
	board->piece[6][1].type = CHESS_PAWN;   board->piece[6][1].team = TEAM_BLACK;
	board->piece[7][1].type = CHESS_PAWN;   board->piece[7][1].team = TEAM_BLACK;
										    
	board->piece[0][2].type = CHESS_NONE;   board->piece[0][2].team = TEAM_NONE;
	board->piece[1][2].type = CHESS_NONE;   board->piece[1][2].team = TEAM_NONE;
	board->piece[2][2].type = CHESS_NONE;   board->piece[2][2].team = TEAM_NONE;
	board->piece[3][2].type = CHESS_NONE;   board->piece[3][2].team = TEAM_NONE;
	board->piece[4][2].type = CHESS_NONE;   board->piece[4][2].team = TEAM_NONE;
	board->piece[5][2].type = CHESS_NONE;   board->piece[5][2].team = TEAM_NONE;
	board->piece[6][2].type = CHESS_NONE;   board->piece[6][2].team = TEAM_NONE;
	board->piece[7][2].type = CHESS_NONE;   board->piece[7][2].team = TEAM_NONE;
										    
	board->piece[0][3].type = CHESS_NONE;   board->piece[0][3].team = TEAM_NONE;
	board->piece[1][3].type = CHESS_NONE;   board->piece[1][3].team = TEAM_NONE;
	board->piece[2][3].type = CHESS_NONE;   board->piece[2][3].team = TEAM_NONE;
	board->piece[3][3].type = CHESS_NONE;   board->piece[3][3].team = TEAM_NONE;
	board->piece[4][3].type = CHESS_NONE;   board->piece[4][3].team = TEAM_NONE;
	board->piece[5][3].type = CHESS_NONE;   board->piece[5][3].team = TEAM_NONE;
	board->piece[6][3].type = CHESS_NONE;   board->piece[6][3].team = TEAM_NONE;
	board->piece[7][3].type = CHESS_NONE;   board->piece[7][3].team = TEAM_NONE;
										    
	board->piece[0][4].type = CHESS_NONE;   board->piece[0][4].team = TEAM_NONE;
	board->piece[1][4].type = CHESS_NONE;   board->piece[1][4].team = TEAM_NONE;
	board->piece[2][4].type = CHESS_NONE;   board->piece[2][4].team = TEAM_NONE;
	board->piece[3][4].type = CHESS_NONE;   board->piece[3][4].team = TEAM_NONE;
	board->piece[4][4].type = CHESS_NONE;   board->piece[4][4].team = TEAM_NONE;
	board->piece[5][4].type = CHESS_NONE;   board->piece[5][4].team = TEAM_NONE;
	board->piece[6][4].type = CHESS_NONE;   board->piece[6][4].team = TEAM_NONE;
	board->piece[7][4].type = CHESS_NONE;   board->piece[7][4].team = TEAM_NONE;
										    
	board->piece[0][5].type = CHESS_NONE;   board->piece[0][5].team = TEAM_NONE;
	board->piece[1][5].type = CHESS_NONE;   board->piece[1][5].team = TEAM_NONE;
	board->piece[2][5].type = CHESS_NONE;   board->piece[2][5].team = TEAM_NONE;
	board->piece[3][5].type = CHESS_NONE;   board->piece[3][5].team = TEAM_NONE;
	board->piece[4][5].type = CHESS_NONE;   board->piece[4][5].team = TEAM_NONE;
	board->piece[5][5].type = CHESS_NONE;   board->piece[5][5].team = TEAM_NONE;
	board->piece[6][5].type = CHESS_NONE;   board->piece[6][5].team = TEAM_NONE;
	board->piece[7][5].type = CHESS_NONE;   board->piece[7][5].team = TEAM_NONE;
										    
	board->piece[0][6].type = CHESS_PAWN;   board->piece[0][6].team = TEAM_WHITE;
	board->piece[1][6].type = CHESS_PAWN;   board->piece[1][6].team = TEAM_WHITE;
	board->piece[2][6].type = CHESS_PAWN;   board->piece[2][6].team = TEAM_WHITE;
	board->piece[3][6].type = CHESS_PAWN;   board->piece[3][6].team = TEAM_WHITE;
	board->piece[4][6].type = CHESS_PAWN;   board->piece[4][6].team = TEAM_WHITE;
	board->piece[5][6].type = CHESS_PAWN;   board->piece[5][6].team = TEAM_WHITE;
	board->piece[6][6].type = CHESS_PAWN;   board->piece[6][6].team = TEAM_WHITE;
	board->piece[7][6].type = CHESS_PAWN;   board->piece[7][6].team = TEAM_WHITE;

	board->piece[0][7].type = CHESS_ROOK;   board->piece[0][7].team = TEAM_WHITE;
	board->piece[1][7].type = CHESS_KNIGHT;	board->piece[1][7].team = TEAM_WHITE;
	board->piece[2][7].type = CHESS_BISHOP;	board->piece[2][7].team = TEAM_WHITE;
	board->piece[3][7].type = CHESS_QUEEN;	board->piece[3][7].team = TEAM_WHITE;
	board->piece[4][7].type = CHESS_KING;	board->piece[4][7].team = TEAM_WHITE;
	board->piece[5][7].type = CHESS_BISHOP;	board->piece[5][7].team = TEAM_WHITE;
	board->piece[6][7].type = CHESS_KNIGHT;	board->piece[6][7].team = TEAM_WHITE;
	board->piece[7][7].type = CHESS_ROOK;	board->piece[7][7].team = TEAM_WHITE;

	board->gameover = false;
	board->turn = TEAM_WHITE;
	board->winner = TEAM_NONE;
	board->select_x = -1;
	board->select_y = -1;

}

void Board_Move(Board* board, int src_x, int src_y, int dst_x, int dst_y) {
	
	board->piece[src_x][src_y] = board->piece[dst_x][dst_y];

}

