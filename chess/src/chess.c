#include "chess.h"

typedef struct Piece {
	int type;
	int team;
} Piece;

typedef struct Board {
	Piece piece[8][8];
} Board;

typedef struct Chess {
	Board board;
	Texture* sprite[TEAMS_COUNT][CHESSES_COUNT];
	Texture* select_sprite;
	Texture* chess;
	SDL_Rect position;
	int select_x, select_y;
	int turn;
	int winner;
	bool gameover;
	bool king_danger_zone[TEAMS_COUNT][8][8];
	ptr_to_pattern pattern[CHESSES_COUNT];
} Chess;

Chess* Board_Init(SDL_Renderer* renderer, SDL_Rect position) {

	Chess* chess = malloc(sizeof(Chess));

	if (chess == NULL) {
		ERROR("Can't allocate memory");
		return NULL;
	}

	chess->position = position;

	SDL_Rect chess_pos = { 0,0,position.w / 8,position.h / 8 };

	chess->sprite[TEAM_BLACK][CHESS_BISHOP] = Texture_Init(renderer, "img/black_bishop.png",	chess_pos);
	chess->sprite[TEAM_BLACK][CHESS_KING]	= Texture_Init(renderer, "img/black_king.png",		chess_pos);
	chess->sprite[TEAM_BLACK][CHESS_KNIGHT] = Texture_Init(renderer, "img/black_knight.png",	chess_pos);
	chess->sprite[TEAM_BLACK][CHESS_PAWN]	= Texture_Init(renderer, "img/black_pawn.png",		chess_pos);
	chess->sprite[TEAM_BLACK][CHESS_QUEEN]	= Texture_Init(renderer, "img/black_queen.png",		chess_pos);
	chess->sprite[TEAM_BLACK][CHESS_ROOK]	= Texture_Init(renderer, "img/black_rook.png",		chess_pos);
	chess->sprite[TEAM_WHITE][CHESS_BISHOP] = Texture_Init(renderer, "img/white_bishop.png",	chess_pos);
	chess->sprite[TEAM_WHITE][CHESS_KING]	= Texture_Init(renderer, "img/white_king.png",		chess_pos);
	chess->sprite[TEAM_WHITE][CHESS_KNIGHT] = Texture_Init(renderer, "img/white_knight.png",	chess_pos);
	chess->sprite[TEAM_WHITE][CHESS_PAWN]	= Texture_Init(renderer, "img/white_pawn.png",		chess_pos);
	chess->sprite[TEAM_WHITE][CHESS_QUEEN]	= Texture_Init(renderer, "img/white_queen.png",		chess_pos);
	chess->sprite[TEAM_WHITE][CHESS_ROOK]	= Texture_Init(renderer, "img/white_rook.png",		chess_pos);

	chess->chess = Texture_Init(renderer, "img/board.png", position);
	chess->select_sprite = Texture_Init(renderer, "img/select.png", chess_pos);

	chess->pattern[CHESS_BISHOP]	= Board_Pattern_Bishop;
	chess->pattern[CHESS_KING]		= Board_Pattern_King;
	chess->pattern[CHESS_KNIGHT]	= Board_Pattern_Knight;
	chess->pattern[CHESS_PAWN]		= Board_Pattern_Pawn;
	chess->pattern[CHESS_QUEEN]		= Board_Pattern_Queen;
	chess->pattern[CHESS_ROOK]		= Board_Pattern_Rook;

	for (int i = 0; i < TEAMS_COUNT; i++) {
		for (int j = 0; j < CHESSES_COUNT; j++) {
			if (chess->sprite[i][j] == NULL) {
				ERROR(SDL_GetError());
				Board_Destroy(chess);
				return NULL;
			}
		}
	}

	if (chess->chess == NULL) {
		ERROR(SDL_GetError());
		Board_Destroy(chess);
		return NULL;
	}

	if (chess->select_sprite == NULL) {
		ERROR(SDL_GetError());
		Board_Destroy(chess);
		return NULL;
	}

	Board_Restart(&chess->board);
	chess->gameover = false;
	chess->turn = TEAM_WHITE;
	chess->winner = TEAM_NONE;
	chess->select_x = -1;
	chess->select_y = -1;

	return chess;

}

void Board_Destroy(Chess* chess) {

	for (int i = 0; i < TEAMS_COUNT; i++) {
		for (int j = 0; j < CHESSES_COUNT; j++) {
			if (chess->sprite[i][j] != NULL) {
				Texture_Destroy(chess->sprite[i][j]);
			}
		}
	}

	if (chess->chess != NULL) {
		Texture_Destroy(chess->chess);
	}

	if (chess->select_sprite != NULL) {
		Texture_Destroy(chess->select_sprite);
	}

	if (chess != NULL)
		free(chess);

}

void Board_Render(Chess* chess) {

	Texture_Render(chess->chess);

	for (int y = 0; y < 8; y++) {
		
		for (int x = 0; x < 8; x++) {
			
			if (chess->board.piece[x][y].team == TEAM_NONE || chess->board.piece[x][y].type == CHESS_NONE)
				continue;

			Texture_ChangePosition(chess->sprite[chess->board.piece[x][y].team][chess->board.piece[x][y].type], x*(chess->position.w/8), y * (chess->position.h/8));
			Texture_Render(chess->sprite[chess->board.piece[x][y].team][chess->board.piece[x][y].type]);

		}

	}

	Texture_ChangePosition(chess->select_sprite, (chess->select_x*(chess->position.w/8)), (chess->select_y* (chess->position.h / 8)) );
	Texture_Render(chess->select_sprite);

}

void Board_Event(Chess* chess, SDL_Event* events) {

	static bool HOVER = false;

	if (events->type == SDL_MOUSEMOTION) {
		int x = 0;
		int y = 0;
		SDL_GetMouseState(&x, &y);
		SDL_Rect point = { x,y,1,1 };
		if (SDL_HasIntersection(&chess->position, &point)) {
			if (HOVER == false) {
				HOVER = true;
			}
		}
		else {
			HOVER = false;
		}
	}

	if (events->button.button == SDL_BUTTON_LEFT && events->type == SDL_MOUSEBUTTONDOWN) {

		if (HOVER == false) {
			return;
		}
		if (chess->gameover == true)
			return;

		int x = 0;
		int y = 0;
		SDL_GetMouseState(&x, &y);
		x = x / (chess->position.w / 8) - chess->position.x;
		y = y / (chess->position.h / 8) - chess->position.y;

		if (chess->select_x == x && chess->select_y == y) { // Unselecting piece
			chess->select_x = -1;
			chess->select_y = -1;
			return;
		}

		if (chess->select_x == -1 || chess->select_y == -1) { // Selecting piece

			if (chess->board.piece[x][y].team == chess->turn) {
				chess->select_x = x;
				chess->select_y = y;
			}

			return;

		}

		if (chess->board.piece[x][y].team == chess->board.piece[chess->select_x][chess->select_y].team) { // Changing piece
			chess->select_x = x;
			chess->select_y = y;
			return;
		}

		if (Board_CanMove(chess, chess->select_x, chess->select_y, x, y) == true) {  // Moving
			Board_Move(chess, chess->select_x, chess->select_y, x, y);
			Board_ChangeTurn(chess);
			Board_UpdateKingDangerZone(chess);
			Board_IsGameOver(chess);
			chess->select_x = -1;
			chess->select_y = -1;
			return;
		}
	}

}

bool Board_IsGameOver(Chess* chess) {

	for (int i = 0; i < TEAMS_COUNT; i++) {
		if (Board_IsKingInDanger(chess, i) == true) {

			int king_pos_x = 0;
			int king_pos_y = 0;

			for (int y = 0; y < 8; y++) {
				for (int x = 0; x < 8; x++) {
					if (chess->board.piece[x][y].type == CHESS_KING && chess->board.piece[x][y].team == i) {
						king_pos_x = x;
						king_pos_y = y;
						break;
					}
				}
			}

			if (Board_CanMove(chess, king_pos_x, king_pos_y, king_pos_x - 1, king_pos_y - 1) == true ||
				Board_CanMove(chess, king_pos_x, king_pos_y, king_pos_x - 1, king_pos_y    ) == true ||
				Board_CanMove(chess, king_pos_x, king_pos_y, king_pos_x - 1, king_pos_y + 1) == true ||
				Board_CanMove(chess, king_pos_x, king_pos_y, king_pos_x + 1, king_pos_y - 1) == true ||
				Board_CanMove(chess, king_pos_x, king_pos_y, king_pos_x + 1, king_pos_y	   ) == true ||
				Board_CanMove(chess, king_pos_x, king_pos_y, king_pos_x + 1, king_pos_y + 1) == true ||
				Board_CanMove(chess, king_pos_x, king_pos_y, king_pos_x,	 king_pos_y + 1) == true ||
				Board_CanMove(chess, king_pos_x, king_pos_y, king_pos_x,	 king_pos_y - 1) == true) {
				continue;
			}
			else {
				chess->winner = (i == TEAM_WHITE) ? TEAM_BLACK : TEAM_WHITE;
				chess->gameover = true;
				return true;
			}
			
		}
	}

	return false;

}

void Board_Restart(Board* board_data) {

	board_data->piece[0][0].type = CHESS_ROOK;		board_data->piece[0][0].team = TEAM_BLACK;
	board_data->piece[1][0].type = CHESS_KNIGHT;	board_data->piece[1][0].team = TEAM_BLACK;
	board_data->piece[2][0].type = CHESS_BISHOP;	board_data->piece[2][0].team = TEAM_BLACK;
	board_data->piece[3][0].type = CHESS_QUEEN;		board_data->piece[3][0].team = TEAM_BLACK;
	board_data->piece[4][0].type = CHESS_KING;		board_data->piece[4][0].team = TEAM_BLACK;
	board_data->piece[5][0].type = CHESS_BISHOP;	board_data->piece[5][0].team = TEAM_BLACK;
	board_data->piece[6][0].type = CHESS_KNIGHT;	board_data->piece[6][0].team = TEAM_BLACK;
	board_data->piece[7][0].type = CHESS_ROOK;		board_data->piece[7][0].team = TEAM_BLACK;

	board_data->piece[0][1].type = CHESS_PAWN;   board_data->piece[0][1].team = TEAM_BLACK;
	board_data->piece[1][1].type = CHESS_PAWN;   board_data->piece[1][1].team = TEAM_BLACK;
	board_data->piece[2][1].type = CHESS_PAWN;   board_data->piece[2][1].team = TEAM_BLACK;
	board_data->piece[3][1].type = CHESS_PAWN;   board_data->piece[3][1].team = TEAM_BLACK;
	board_data->piece[4][1].type = CHESS_PAWN;   board_data->piece[4][1].team = TEAM_BLACK;
	board_data->piece[5][1].type = CHESS_PAWN;   board_data->piece[5][1].team = TEAM_BLACK;
	board_data->piece[6][1].type = CHESS_PAWN;   board_data->piece[6][1].team = TEAM_BLACK;
	board_data->piece[7][1].type = CHESS_PAWN;   board_data->piece[7][1].team = TEAM_BLACK;
										    
	board_data->piece[0][2].type = CHESS_NONE;   board_data->piece[0][2].team = TEAM_NONE;
	board_data->piece[1][2].type = CHESS_NONE;   board_data->piece[1][2].team = TEAM_NONE;
	board_data->piece[2][2].type = CHESS_NONE;   board_data->piece[2][2].team = TEAM_NONE;
	board_data->piece[3][2].type = CHESS_NONE;   board_data->piece[3][2].team = TEAM_NONE;
	board_data->piece[4][2].type = CHESS_NONE;   board_data->piece[4][2].team = TEAM_NONE;
	board_data->piece[5][2].type = CHESS_NONE;   board_data->piece[5][2].team = TEAM_NONE;
	board_data->piece[6][2].type = CHESS_NONE;   board_data->piece[6][2].team = TEAM_NONE;
	board_data->piece[7][2].type = CHESS_NONE;   board_data->piece[7][2].team = TEAM_NONE;
										    
	board_data->piece[0][3].type = CHESS_NONE;   board_data->piece[0][3].team = TEAM_NONE;
	board_data->piece[1][3].type = CHESS_NONE;   board_data->piece[1][3].team = TEAM_NONE;
	board_data->piece[2][3].type = CHESS_NONE;   board_data->piece[2][3].team = TEAM_NONE;
	board_data->piece[3][3].type = CHESS_NONE;   board_data->piece[3][3].team = TEAM_NONE;
	board_data->piece[4][3].type = CHESS_NONE;   board_data->piece[4][3].team = TEAM_NONE;
	board_data->piece[5][3].type = CHESS_NONE;   board_data->piece[5][3].team = TEAM_NONE;
	board_data->piece[6][3].type = CHESS_NONE;   board_data->piece[6][3].team = TEAM_NONE;
	board_data->piece[7][3].type = CHESS_NONE;   board_data->piece[7][3].team = TEAM_NONE;
										    
	board_data->piece[0][4].type = CHESS_NONE;   board_data->piece[0][4].team = TEAM_NONE;
	board_data->piece[1][4].type = CHESS_NONE;   board_data->piece[1][4].team = TEAM_NONE;
	board_data->piece[2][4].type = CHESS_NONE;   board_data->piece[2][4].team = TEAM_NONE;
	board_data->piece[3][4].type = CHESS_NONE;   board_data->piece[3][4].team = TEAM_NONE;
	board_data->piece[4][4].type = CHESS_NONE;   board_data->piece[4][4].team = TEAM_NONE;
	board_data->piece[5][4].type = CHESS_NONE;   board_data->piece[5][4].team = TEAM_NONE;
	board_data->piece[6][4].type = CHESS_NONE;   board_data->piece[6][4].team = TEAM_NONE;
	board_data->piece[7][4].type = CHESS_NONE;   board_data->piece[7][4].team = TEAM_NONE;
										    
	board_data->piece[0][5].type = CHESS_NONE;   board_data->piece[0][5].team = TEAM_NONE;
	board_data->piece[1][5].type = CHESS_NONE;   board_data->piece[1][5].team = TEAM_NONE;
	board_data->piece[2][5].type = CHESS_NONE;   board_data->piece[2][5].team = TEAM_NONE;
	board_data->piece[3][5].type = CHESS_NONE;   board_data->piece[3][5].team = TEAM_NONE;
	board_data->piece[4][5].type = CHESS_NONE;   board_data->piece[4][5].team = TEAM_NONE;
	board_data->piece[5][5].type = CHESS_NONE;   board_data->piece[5][5].team = TEAM_NONE;
	board_data->piece[6][5].type = CHESS_NONE;   board_data->piece[6][5].team = TEAM_NONE;
	board_data->piece[7][5].type = CHESS_NONE;   board_data->piece[7][5].team = TEAM_NONE;
										    
	board_data->piece[0][6].type = CHESS_PAWN;  board_data->piece[0][6].team = TEAM_WHITE;
	board_data->piece[1][6].type = CHESS_PAWN;  board_data->piece[1][6].team = TEAM_WHITE;
	board_data->piece[2][6].type = CHESS_PAWN;  board_data->piece[2][6].team = TEAM_WHITE;
	board_data->piece[3][6].type = CHESS_PAWN;  board_data->piece[3][6].team = TEAM_WHITE;
	board_data->piece[4][6].type = CHESS_PAWN;  board_data->piece[4][6].team = TEAM_WHITE;
	board_data->piece[5][6].type = CHESS_PAWN;  board_data->piece[5][6].team = TEAM_WHITE;
	board_data->piece[6][6].type = CHESS_PAWN;  board_data->piece[6][6].team = TEAM_WHITE;
	board_data->piece[7][6].type = CHESS_PAWN;  board_data->piece[7][6].team = TEAM_WHITE;

	board_data->piece[0][7].type = CHESS_ROOK;		board_data->piece[0][7].team = TEAM_WHITE;
	board_data->piece[1][7].type = CHESS_KNIGHT;	board_data->piece[1][7].team = TEAM_WHITE;
	board_data->piece[2][7].type = CHESS_BISHOP;	board_data->piece[2][7].team = TEAM_WHITE;
	board_data->piece[3][7].type = CHESS_QUEEN;		board_data->piece[3][7].team = TEAM_WHITE;
	board_data->piece[4][7].type = CHESS_KING;		board_data->piece[4][7].team = TEAM_WHITE;
	board_data->piece[5][7].type = CHESS_BISHOP;	board_data->piece[5][7].team = TEAM_WHITE;
	board_data->piece[6][7].type = CHESS_KNIGHT;	board_data->piece[6][7].team = TEAM_WHITE;
	board_data->piece[7][7].type = CHESS_ROOK;		board_data->piece[7][7].team = TEAM_WHITE;

}

void Board_Move(Chess* chess, int src_x, int src_y, int dst_x, int dst_y) {

	chess->board.piece[dst_x][dst_y] = chess->board.piece[src_x][src_y];
	chess->board.piece[src_x][src_y].team = TEAM_NONE;
	chess->board.piece[src_x][src_y].type = CHESS_NONE;

	if (chess->board.piece[dst_x][dst_y].type == CHESS_PAWN) {
		if (chess->board.piece[dst_x][dst_y].team == TEAM_WHITE && dst_y == 0) {
			chess->board.piece[dst_x][dst_y].type = CHESS_QUEEN;
		}
		else if (chess->board.piece[dst_x][dst_y].team == TEAM_BLACK && dst_y == 7) {
			chess->board.piece[dst_x][dst_y].type = CHESS_QUEEN;
		}
	}

}

inline void Board_ChangeTurn(Chess* chess) {
	chess->turn = (chess->turn == TEAM_WHITE) ? TEAM_BLACK : TEAM_WHITE;
}

bool Board_CanMove(Chess* chess, int src_x, int src_y, int dst_x, int dst_y) {

	if (src_x < 0 || src_x > 7 || src_y < 0 || src_y > 7)
		return false;
	if (dst_x < 0 || dst_x > 7 || dst_y < 0 || dst_y > 7)
		return false;

	if (chess->board.piece[src_x][src_y].type == CHESS_KING) {
		if (chess->king_danger_zone[chess->board.piece[src_x][src_y].team][dst_x][dst_y] == true) {
			// Display message king can't move here
			return false;
		}
	}
	else if (Board_IsKingInDanger(chess, chess->turn) == true) {
		// King need to move
		return false;
	}

	if (src_x == dst_x && src_y == dst_y)
		return false;
	else if (chess->board.piece[dst_x][dst_y].team == chess->board.piece[src_x][src_y].team)
		return false;
		
	return chess->pattern[chess->board.piece[src_x][src_y].type](chess, src_x, src_y, dst_x, dst_y);

}

bool Board_Pattern_Bishop(Board* board, int src_x, int src_y, int dst_x, int dst_y) {

	if (src_x - dst_x == src_y - dst_y || dst_x - src_x == src_y - dst_y) {

		int tx = dst_x - src_x;
		int ty = dst_y - src_y;

		if (tx < 0 && ty < 0) {
			for (int i = 1; i < ABS(tx); i++) {
				if (board->piece[src_x - i][src_y - i].team > TEAM_NONE) {
					return false;
				}
			}
		}

		else if (tx < 0 && ty > 0) {
			for (int i = 1; i < ABS(tx); i++) {
				if (board->piece[src_x - i][src_y + i].team > TEAM_NONE) {
					return false;
				}
			}
		}

		else if (tx > 0 && ty < 0) {
			for (int i = 1; i < ABS(tx); i++) {
				if (board->piece[src_x + i][src_y - i].team > TEAM_NONE) {
					return false;
				}
			}
		}

		else if (tx > 0 && ty > 0) {
			for (int i = 1; i < ABS(tx); i++) {
				if (board->piece[src_x + i][src_y + i].team > TEAM_NONE) {
					return false;
				}
			}
		}

		else {
			ERROR("Wrong values");
			return false;
		}

		return true;

	}

	return false;
}

bool Board_Pattern_King(Board* board, int src_x, int src_y, int dst_x, int dst_y) {
	
	if ( (src_x + 1 == dst_x && src_y + 1 == dst_y) || 
		 (src_x + 1 == dst_x && src_y - 1 == dst_y) ||
		 (src_x - 1 == dst_x && src_y - 1 == dst_y) ||
		 (src_x - 1 == dst_x && src_y + 1 == dst_y) ||
		 (src_x + 1 == dst_x && src_y == dst_y) ||
		 (src_x - 1 == dst_x && src_y == dst_y) ||
		 (src_y + 1 == dst_y && src_x == dst_x) ||
		 (src_y - 1 == dst_y && src_x == dst_x) 
		
		) {

		return true;

	}
	
	return false;
}

bool Board_Pattern_Knight(Board* board, int src_x, int src_y, int dst_x, int dst_y) {


	if (src_x + 2 == dst_x || src_x - 2 == dst_x) {
		
		if (src_y + 1 == dst_y || src_y - 1 == dst_y) {
			return true;
		}

	}

	else if (src_y + 2 == dst_y || src_y - 2 == dst_y) {

		if (src_x + 1 == dst_x || src_x - 1 == dst_x) {
			return true;
		}

	}

	return false;
}

bool Board_Pattern_Pawn(Board* board, int src_x, int src_y, int dst_x, int dst_y) {
	if (board->piece[dst_x][dst_y].team > TEAM_NONE && board->piece[dst_x][dst_y].team != board->piece[src_x][src_y].team)
		return  Board_Pattern_Pawn_Capture(board, src_x, src_y, dst_x, dst_y);
	else 
		return Board_Pattern_Pawn_Move(board, src_x, src_y, dst_x, dst_y);
}

bool Board_Pattern_Pawn_Move(Board* board, int src_x, int src_y, int dst_x, int dst_y) {
	
	int t = (board->piece[src_x][src_y].team == TEAM_WHITE) ? 1 : -1;

	if (t < 0) {

		if (src_y < 2) {

			if (src_y - t * 2 == dst_y && src_x == dst_x) {
				return true;
			}

		}

	}
	else {

		if (src_y > 5) {

			if (src_y - t * 2 == dst_y && src_x == dst_x) {
				return true;
			}

		}

	}

	if (src_y - t == dst_y && src_x == dst_x) {
		return true;
	}

	return false;

}

bool Board_Pattern_Pawn_Capture(Board* board, int src_x, int src_y, int dst_x, int dst_y) {

	if (board->piece[src_x][src_y].team == TEAM_WHITE) {
		if (src_y - 1 == dst_y && (src_x - 1 == dst_x || src_x + 1 == dst_x)) {
			return true;
		}
	}

	if (board->piece[src_x][src_y].team == TEAM_BLACK) {
		if (src_y + 1 == dst_y && (src_x - 1 == dst_x || src_x + 1 == dst_x)) {
				return true;
		}
	}

	return false;

}

bool Board_Pattern_Queen(Board* board, int src_x, int src_y, int dst_x, int dst_y) {
	return (Board_Pattern_Bishop(board, src_x, src_y, dst_x, dst_y) == true || Board_Pattern_Rook(board, src_x, src_y, dst_x, dst_y) == true);
}

bool Board_Pattern_Rook(Board* board, int src_x, int src_y, int dst_x, int dst_y) {

	if (src_x == dst_x || src_y == dst_y) {

		int tx = dst_x - src_x;
		int ty = dst_y - src_y;

		if (tx == 0) {

			if (ty > 0) {
				for (int i = 1; i < ABS(ty); i++) {
					if (board->piece[src_x][src_y + i].team > TEAM_NONE) {
						return false;
					}
				}
			}
			else {
				for (int i = 1; i < ABS(ty); i++) {
					if (board->piece[src_x][src_y - i].team > TEAM_NONE) {
						return false;
					}
				}
			}

		}

		else if (ty == 0) {

			if (tx > 0) {
				for (int i = 1; i < ABS(tx); i++) {
					if (board->piece[src_x + 1][src_y].team > TEAM_NONE) {
						return false;
					}
				}
			}
			else {
				for (int i = 1; i < ABS(tx); i++) {
					if (board->piece[src_x - 1][src_y].team > TEAM_NONE) {
						return false;
					}
				}
			}

		}

		else {
			ERROR("Wrong values");
			return false;
		}

		return true;
	}

	return false;
}

void Board_UpdateKingDangerZone(Chess* chess) {
	
	for (int i = 0; i < TEAMS_COUNT; i++) {
		for (int x = 0; x < 8; x++) {
			for (int y = 0; y < 8; y++) {
				chess->king_danger_zone[i][x][y] = false;
			}
		}
	}

	for (int i = 0; i < TEAMS_COUNT; i++) {
		for (int x = 0; x < 8; x++) {
			for (int y = 0; y < 8; y++) {
				if (chess->board.piece[x][y].team > TEAM_NONE && chess->board.piece[x][y].team != i) {

					if (chess->board.piece[x][y].type == CHESS_PAWN) {
						for (int px = 0; px < 8; px++) {
							for (int py = 0; py < 8; py++) {
								if (Board_Pattern_Pawn_Capture(chess, x, y, px, py) == true) {
									chess->king_danger_zone[i][px][py] = true;
								}
							}
						}
					}

					else {
						for (int px = 0; px < 8; px++) {
							for (int py = 0; py < 8; py++) {
								if (Board_CanMove(chess, x, y, px, py) == true) {
									chess->king_danger_zone[i][px][py] = true;
								}
							}
						}
					}

				}
			}
		}
	}

}

bool Board_IsKingInDanger(Chess* chess, ChessTeam team) {

	int king_pos_x=-1, king_pos_y=-1;

	for (int x = 0; x < 8; x++) {
		for (int y = 0; y < 8; y++) {
			if (chess->board.piece[x][y].team == team) {
				if (chess->board.piece[x][y].type == CHESS_KING) {
					king_pos_x = x; king_pos_y = y;
					break;
				}
			}
		}
	}

	return chess->king_danger_zone[team][king_pos_x][king_pos_y];

}

void Board_GetKingDangerZone(Chess* chess, ChessTeam team, bool88 king_danger_zone) {

	for (int i = 0; i < TEAMS_COUNT; i++) {
		for (int x = 0; x < 8; x++) {
			for (int y = 0; y < 8; y++) {
				chess->king_danger_zone[i][x][y] = false;
			}
		}
	}

	for (int x = 0; x < 8; x++) {
		for (int y = 0; y < 8; y++) {

			if (chess->board.piece[x][y].team > TEAM_NONE) {
				continue;
			}

			if (chess->board.piece[x][y].team != team) {
				continue;
			}

			for (int px = 0; px < 8; px++) {
				for (int py = 0; py < 8; py++) {

					if (chess->board.piece[x][y].type == CHESS_PAWN) {
						
						if (Board_Pattern_Pawn_Capture(chess, x, y, px, py) == true) {
							king_danger_zone[px][py] = true;
						}

					}

					else {

						if (Board_CanMove(chess, x, y, px, py) == true) {
							king_danger_zone[px][py] = true;
						}

					}
					
				}
			}
			
		}
	}
	
}