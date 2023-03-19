#include "board.h"

enum TextureID {
	TEXTURE_BLACK_BISHOP,
	TEXTURE_BLACK_KING,
	TEXTURE_BLACK_KNIGHT,
	TEXTURE_BLACK_PAWN,
	TEXTURE_BLACK_QUEEN,
	TEXTURE_BLACK_ROOK,
	TEXTURE_WHITE_BISHOP,
	TEXTURE_WHITE_KING,
	TEXTURE_WHITE_KNIGHT,
	TEXTURE_WHITE_PAWN,
	TEXTURE_WHITE_QUEEN,
	TEXTURE_WHITE_ROOK,
	TEXTURE_BOARD,
	TEXTURE_COUNT
};

const bool bishop_pattern[15][15] = {
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{0,1,0,0,0,0,0,0,0,0,0,0,0,1,0},
	{0,0,1,0,0,0,0,0,0,0,0,0,1,0,0},
	{0,0,0,1,0,0,0,0,0,0,0,1,0,0,0},
	{0,0,0,0,1,0,0,0,0,0,1,0,0,0,0},
	{0,0,0,0,0,1,0,0,0,1,0,0,0,0,0},
	{0,0,0,0,0,0,1,0,1,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,1,0,1,0,0,0,0,0,0},
	{0,0,0,0,0,1,0,0,0,1,0,0,0,0,0},
	{0,0,0,0,1,0,0,0,0,0,1,0,0,0,0},
	{0,0,0,1,0,0,0,0,0,0,0,1,0,0,0},
	{0,0,1,0,0,0,0,0,0,0,0,0,1,0,0},
	{0,1,0,0,0,0,0,0,0,0,0,0,0,1,0},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1}
};

const bool king_pattern[15][15] = {
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,1,1,1,0,0,0,0,0,0},
	{0,0,0,0,0,0,1,0,1,0,0,0,0,0,0},
	{0,0,0,0,0,0,1,1,1,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
};

const bool knight_pattern[15][15] = {
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,1,0,1,0,0,0,0,0,0},
	{0,0,0,0,0,1,0,0,0,1,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,1,0,0,0,1,0,0,0,0,0},
	{0,0,0,0,0,0,1,0,1,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

const bool pawn_move_pattern[15][15] = {
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

const bool pawn_first_move_pattern[15][15] = {
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

const bool pawn_capture_pattern[15][15] = {
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,1,0,1,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,1,0,1,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

const bool queen_pattern[15][15] = {
	{1,0,0,0,0,0,0,1,0,0,0,0,0,0,1},
	{0,1,0,0,0,0,0,1,0,0,0,0,0,1,0},
	{0,0,1,0,0,0,0,1,0,0,0,0,1,0,0},
	{0,0,0,1,0,0,0,1,0,0,0,1,0,0,0},
	{0,0,0,0,1,0,0,1,0,0,1,0,0,0,0},
	{0,0,0,0,0,1,0,1,0,1,0,0,0,0,0},
	{0,0,0,0,0,0,1,1,1,0,0,0,0,0,0},
	{1,1,1,1,1,1,1,0,1,1,1,1,1,1,1},
	{0,0,0,0,0,0,1,1,1,0,0,0,0,0,0},
	{0,0,0,0,0,1,0,1,0,1,0,0,0,0,0},
	{0,0,0,0,1,0,0,1,0,0,1,0,0,0,0},
	{0,0,0,1,0,0,0,1,0,0,0,1,0,0,0},
	{0,0,1,0,0,0,0,1,0,0,0,0,1,0,0},
	{0,1,0,0,0,0,0,1,0,0,0,0,0,1,0},
	{1,0,0,0,0,0,0,1,0,0,0,0,0,0,1}
};

const bool rook_pattern[15][15] = {
	{0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
	{1,1,1,1,1,1,1,0,1,1,1,1,1,1,1},
	{0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,1,0,0,0,0,0,0,0}
};

const bool up_mask_pattern[15][15] = {
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
};

const bool down_mask_pattern[15][15] = {
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
};

unsigned int texture[TEXTURE_COUNT];


bool Board_InitTextures() {

	SDL_Rect none = {0,0,0,0};				// chesses position
	
	texture[TEXTURE_BOARD]			= LoadTexture("img/board.png");
	texture[TEXTURE_BLACK_BISHOP]	= LoadTexture("img/black_bishop.png");
	texture[TEXTURE_BLACK_KING]		= LoadTexture("img/black_king.png");
	texture[TEXTURE_BLACK_KNIGHT]	= LoadTexture("img/black_knight.png");
	texture[TEXTURE_BLACK_PAWN]		= LoadTexture("img/black_pawn.png");
	texture[TEXTURE_BLACK_QUEEN]	= LoadTexture("img/black_queen.png");
	texture[TEXTURE_BLACK_ROOK]		= LoadTexture("img/black_rook.png");
	texture[TEXTURE_WHITE_BISHOP]	= LoadTexture("img/white_bishop.png");
	texture[TEXTURE_WHITE_KING]		= LoadTexture("img/white_king.png");
	texture[TEXTURE_WHITE_KNIGHT]	= LoadTexture("img/white_knight.png");
	texture[TEXTURE_WHITE_PAWN]		= LoadTexture("img/white_pawn.png");
	texture[TEXTURE_WHITE_QUEEN]	= LoadTexture("img/white_queen.png");
	texture[TEXTURE_WHITE_ROOK]		= LoadTexture("img/white_rook.png");

	for (int i = 0; i < TEXTURE_COUNT; i++) {
		if (texture[i] == INVALID_OBJECT) {
			Board_DestroyTextures();
		}
	}

	return true;

}

void Board_Handle_Events(Board* board, SDL_Rect* board_pos, Move* move) {
	
	static bool HOVER = false;

	if (event_handler.type == SDL_MOUSEMOTION) {
		int x = 0;
		int y = 0;
		SDL_GetMouseState(&x, &y);
		SDL_Rect point = { x,y,1,1 };
		if (SDL_HasIntersection(board_pos, &point)) {
			HOVER = true;
		}
		else {
			HOVER = false;
		}
	}

	if (event_handler.button.button == SDL_BUTTON_LEFT) {

		if (HOVER == false) {
			board->select_x = -1;
			board->select_y = -1;
			return;
		}

		if (event_handler.type == SDL_MOUSEBUTTONUP) {

			if (board->select_x != -1 && board->select_y != -1) {
				int x = 0;
				int y = 0;
				SDL_GetMouseState(&x, &y);

				x = (x - board_pos->x) / (board_pos->w / 8);
				y = (y - board_pos->y) / (board_pos->h / 8);

				if (x < 0 || x > 7 || y < 0 || y > 7) {
					board->select_x = -1;
					board->select_y = -1;
					return;
				}
				move->src_x = board->select_x;
				move->src_y = board->select_y;
				move->dst_x = x;
				move->dst_y = y;

				board->select_x = -1;
				board->select_y = -1;
			}
			
		}

		if (event_handler.type == SDL_MOUSEBUTTONDOWN) {
			int x = 0;
			int y = 0;
			SDL_GetMouseState(&x, &y);

			x = (x - board_pos->x) / (board_pos->w / 8);
			y = (y - board_pos->y) / (board_pos->h / 8);

			if (x < 0 || x > 7 || y < 0 || y > 7) {
				return;
			}

			if (board->piece[x][y].team == board->turn) {
				board->select_x = x;
				board->select_y = y;
				return;
			}
		}

	}

}

void Board_Render(Board* board, SDL_Rect* board_pos) {

	SetObjectPositionAndDimensions(texture[TEXTURE_BOARD], board_pos->x,board_pos->y, board_pos->w, board_pos->h);
	RenderObject(texture[TEXTURE_BOARD]);

	int chess_width = (board_pos->w / 8);
	int chess_height = (board_pos->h / 8);


	for (int x = 0; x < 8; x++) {
		for (int y = 0; y < 8; y++) {

			if (board->piece[x][y].team == TEAM_NONE || board->piece[x][y].state == CHESS_NONE)
				continue;

			if (x == board->select_x && y == board->select_y)
				continue;

			int texture_id = Board_TextureId(board->piece[x][y].state, board->piece[x][y].team);

			SetObjectPositionAndDimensions(texture[texture_id], x * chess_width, y * chess_height, chess_width, chess_height);
			RenderObject(texture[texture_id]);

		}
	}

	if (board->select_x != -1 && board->select_y != -1) {

		int mx, my;
		SDL_GetMouseState(&mx, &my);

		int texture_id = Board_TextureId(board->piece[board->select_x][board->select_y].state, board->piece[board->select_x][board->select_y].team);;
		SetObjectPositionAndDimensions(texture[texture_id], mx - chess_width / 2, my - chess_height / 2, chess_width, chess_height);
		RenderObject(texture[texture_id]);
	}

}

int Board_TextureId(int state, int team) {

	switch (team) {
	case TEAM_WHITE: {
		switch (state) {
		case CHESS_BISHOP:	{return TEXTURE_WHITE_BISHOP; break; }
		case CHESS_KING:	{return TEXTURE_WHITE_KING; break; }
		case CHESS_KNIGHT:	{return TEXTURE_WHITE_KNIGHT; break; }
		case CHESS_PAWN:	{return TEXTURE_WHITE_PAWN; break; }
		case CHESS_QUEEN:	{return TEXTURE_WHITE_QUEEN; break; }
		case CHESS_ROOK:	{return TEXTURE_WHITE_ROOK; break; }
		}
		break;
	}
	case TEAM_BLACK: {
		switch (state) {
		case CHESS_BISHOP:	{return TEXTURE_BLACK_BISHOP; break; }
		case CHESS_KING:	{return TEXTURE_BLACK_KING; break; }
		case CHESS_KNIGHT:	{return TEXTURE_BLACK_KNIGHT; break; }
		case CHESS_PAWN:	{return TEXTURE_BLACK_PAWN; break; }
		case CHESS_QUEEN:	{return TEXTURE_BLACK_QUEEN; break; }
		case CHESS_ROOK:	{return TEXTURE_BLACK_ROOK; break; }
		}
		break;
	}
	}

	LOG_WARN("There is no texture with that type or team");

	return 0;
}

void Board_DestroyTextures() {

	for (int i = 0; i < TEXTURE_COUNT; i++) {
		DestroyObject(texture[i]);
	}

}




void Board_ChangeTurn(Board* board) {
	board->turn = (board->turn == TEAM_WHITE) ? TEAM_BLACK : TEAM_WHITE;
}

bool Board_KingCannotMove(Board* board, ChessTeam team) {

	int king_pos_x = 0;
	int king_pos_y = 0;

	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			if (board->piece[x][y].state == CHESS_KING && board->piece[x][y].team == team) {
				king_pos_x = x;
				king_pos_y = y;
				break;
			}
		}
	}

	bool88 king_danger_zone;
	Board_GetKingDangerZone(board, team, king_danger_zone);


	if (king_pos_x > 0 && king_pos_y > 0)
		if (Board_CanMove(board, king_pos_x, king_pos_y, king_pos_x - 1, king_pos_y - 1) && king_danger_zone[king_pos_x - 1][king_pos_y - 1] == false)
			return false;
	if (king_pos_x > 0)
		if (Board_CanMove(board, king_pos_x, king_pos_y, king_pos_x - 1, king_pos_y    ) && king_danger_zone[king_pos_x - 1][king_pos_y    ] == false)
			return false;
	if (king_pos_x > 0 && king_pos_y < 7)
		if (Board_CanMove(board, king_pos_x, king_pos_y, king_pos_x - 1, king_pos_y + 1) && king_danger_zone[king_pos_x - 1][king_pos_y + 1] == false)
			return false;
	if (king_pos_x < 7 && king_pos_y > 0)
		if (Board_CanMove(board, king_pos_x, king_pos_y, king_pos_x + 1, king_pos_y - 1) && king_danger_zone[king_pos_x + 1][king_pos_y - 1] == false)
			return false;
	if (king_pos_x < 7)
		if (Board_CanMove(board, king_pos_x, king_pos_y, king_pos_x + 1, king_pos_y    ) && king_danger_zone[king_pos_x + 1][king_pos_y    ] == false)
			return false;
	if (king_pos_x < 7 && king_pos_y < 7)
		if (Board_CanMove(board, king_pos_x, king_pos_y, king_pos_x + 1, king_pos_y + 1) && king_danger_zone[king_pos_x + 1][king_pos_y + 1] == false)
			return false;
	if (king_pos_y < 7)
		if (Board_CanMove(board, king_pos_x, king_pos_y, king_pos_x    , king_pos_y + 1) && king_danger_zone[king_pos_x    ][king_pos_y + 1] == false)
			return false;
	if (king_pos_y > 0)
		if (Board_CanMove(board, king_pos_x, king_pos_y, king_pos_x    , king_pos_y - 1) && king_danger_zone[king_pos_x    ][king_pos_y - 1] == false)
			return false;

	return true;

}

bool Board_CanProtectKing(Board* board, int src_x, int src_y, int dst_x, int dst_y, ChessTeam team) {

	if (board->piece[src_x][src_y].team != team) {
		return false;
	}

	Board test_board;
	Board_Copy(board, &test_board);
	
	if (!Board_CanMove(&test_board, src_x, src_y, dst_x, dst_y)) {
		return false;
	}

	Board_Move(&test_board, src_x, src_y, dst_x, dst_y);
	if (Board_IsKingInDanger(&test_board, team) == true) {
		return false;
	}

	return true;

}

void Board_Restart(Board* board_data) {

	board_data->turn = TEAM_WHITE;
	board_data->winner = TEAM_NONE;
	board_data->gameover = false;
	board_data->select_x = -1;
	board_data->select_y = -1;

	board_data->piece[0][0].state = CHESS_ROOK;		board_data->piece[0][0].team = TEAM_BLACK;
	board_data->piece[1][0].state = CHESS_KNIGHT;	board_data->piece[1][0].team = TEAM_BLACK;
	board_data->piece[2][0].state = CHESS_BISHOP;	board_data->piece[2][0].team = TEAM_BLACK;
	board_data->piece[3][0].state = CHESS_QUEEN;		board_data->piece[3][0].team = TEAM_BLACK;
	board_data->piece[4][0].state = CHESS_KING;		board_data->piece[4][0].team = TEAM_BLACK;
	board_data->piece[5][0].state = CHESS_BISHOP;	board_data->piece[5][0].team = TEAM_BLACK;
	board_data->piece[6][0].state = CHESS_KNIGHT;	board_data->piece[6][0].team = TEAM_BLACK;
	board_data->piece[7][0].state = CHESS_ROOK;		board_data->piece[7][0].team = TEAM_BLACK;

	board_data->piece[0][1].state = CHESS_PAWN;   board_data->piece[0][1].team = TEAM_BLACK;
	board_data->piece[1][1].state = CHESS_PAWN;   board_data->piece[1][1].team = TEAM_BLACK;
	board_data->piece[2][1].state = CHESS_PAWN;   board_data->piece[2][1].team = TEAM_BLACK;
	board_data->piece[3][1].state = CHESS_PAWN;   board_data->piece[3][1].team = TEAM_BLACK;
	board_data->piece[4][1].state = CHESS_PAWN;   board_data->piece[4][1].team = TEAM_BLACK;
	board_data->piece[5][1].state = CHESS_PAWN;   board_data->piece[5][1].team = TEAM_BLACK;
	board_data->piece[6][1].state = CHESS_PAWN;   board_data->piece[6][1].team = TEAM_BLACK;
	board_data->piece[7][1].state = CHESS_PAWN;   board_data->piece[7][1].team = TEAM_BLACK;
										    
	board_data->piece[0][2].state = CHESS_NONE;   board_data->piece[0][2].team = TEAM_NONE;
	board_data->piece[1][2].state = CHESS_NONE;   board_data->piece[1][2].team = TEAM_NONE;
	board_data->piece[2][2].state = CHESS_NONE;   board_data->piece[2][2].team = TEAM_NONE;
	board_data->piece[3][2].state = CHESS_NONE;   board_data->piece[3][2].team = TEAM_NONE;
	board_data->piece[4][2].state = CHESS_NONE;   board_data->piece[4][2].team = TEAM_NONE;
	board_data->piece[5][2].state = CHESS_NONE;   board_data->piece[5][2].team = TEAM_NONE;
	board_data->piece[6][2].state = CHESS_NONE;   board_data->piece[6][2].team = TEAM_NONE;
	board_data->piece[7][2].state = CHESS_NONE;   board_data->piece[7][2].team = TEAM_NONE;
										    
	board_data->piece[0][3].state = CHESS_NONE;   board_data->piece[0][3].team = TEAM_NONE;
	board_data->piece[1][3].state = CHESS_NONE;   board_data->piece[1][3].team = TEAM_NONE;
	board_data->piece[2][3].state = CHESS_NONE;   board_data->piece[2][3].team = TEAM_NONE;
	board_data->piece[3][3].state = CHESS_NONE;   board_data->piece[3][3].team = TEAM_NONE;
	board_data->piece[4][3].state = CHESS_NONE;   board_data->piece[4][3].team = TEAM_NONE;
	board_data->piece[5][3].state = CHESS_NONE;   board_data->piece[5][3].team = TEAM_NONE;
	board_data->piece[6][3].state = CHESS_NONE;   board_data->piece[6][3].team = TEAM_NONE;
	board_data->piece[7][3].state = CHESS_NONE;   board_data->piece[7][3].team = TEAM_NONE;
										    
	board_data->piece[0][4].state = CHESS_NONE;   board_data->piece[0][4].team = TEAM_NONE;
	board_data->piece[1][4].state = CHESS_NONE;   board_data->piece[1][4].team = TEAM_NONE;
	board_data->piece[2][4].state = CHESS_NONE;   board_data->piece[2][4].team = TEAM_NONE;
	board_data->piece[3][4].state = CHESS_NONE;   board_data->piece[3][4].team = TEAM_NONE;
	board_data->piece[4][4].state = CHESS_NONE;   board_data->piece[4][4].team = TEAM_NONE;
	board_data->piece[5][4].state = CHESS_NONE;   board_data->piece[5][4].team = TEAM_NONE;
	board_data->piece[6][4].state = CHESS_NONE;   board_data->piece[6][4].team = TEAM_NONE;
	board_data->piece[7][4].state = CHESS_NONE;   board_data->piece[7][4].team = TEAM_NONE;
										    
	board_data->piece[0][5].state = CHESS_NONE;   board_data->piece[0][5].team = TEAM_NONE;
	board_data->piece[1][5].state = CHESS_NONE;   board_data->piece[1][5].team = TEAM_NONE;
	board_data->piece[2][5].state = CHESS_NONE;   board_data->piece[2][5].team = TEAM_NONE;
	board_data->piece[3][5].state = CHESS_NONE;   board_data->piece[3][5].team = TEAM_NONE;
	board_data->piece[4][5].state = CHESS_NONE;   board_data->piece[4][5].team = TEAM_NONE;
	board_data->piece[5][5].state = CHESS_NONE;   board_data->piece[5][5].team = TEAM_NONE;
	board_data->piece[6][5].state = CHESS_NONE;   board_data->piece[6][5].team = TEAM_NONE;
	board_data->piece[7][5].state = CHESS_NONE;   board_data->piece[7][5].team = TEAM_NONE;
										    
	board_data->piece[0][6].state = CHESS_PAWN;  board_data->piece[0][6].team = TEAM_WHITE;
	board_data->piece[1][6].state = CHESS_PAWN;  board_data->piece[1][6].team = TEAM_WHITE;
	board_data->piece[2][6].state = CHESS_PAWN;  board_data->piece[2][6].team = TEAM_WHITE;
	board_data->piece[3][6].state = CHESS_PAWN;  board_data->piece[3][6].team = TEAM_WHITE;
	board_data->piece[4][6].state = CHESS_PAWN;  board_data->piece[4][6].team = TEAM_WHITE;
	board_data->piece[5][6].state = CHESS_PAWN;  board_data->piece[5][6].team = TEAM_WHITE;
	board_data->piece[6][6].state = CHESS_PAWN;  board_data->piece[6][6].team = TEAM_WHITE;
	board_data->piece[7][6].state = CHESS_PAWN;  board_data->piece[7][6].team = TEAM_WHITE;

	board_data->piece[0][7].state = CHESS_ROOK;		board_data->piece[0][7].team = TEAM_WHITE;
	board_data->piece[1][7].state = CHESS_KNIGHT;	board_data->piece[1][7].team = TEAM_WHITE;
	board_data->piece[2][7].state = CHESS_BISHOP;	board_data->piece[2][7].team = TEAM_WHITE;
	board_data->piece[3][7].state = CHESS_QUEEN;		board_data->piece[3][7].team = TEAM_WHITE;
	board_data->piece[4][7].state = CHESS_KING;		board_data->piece[4][7].team = TEAM_WHITE;
	board_data->piece[5][7].state = CHESS_BISHOP;	board_data->piece[5][7].team = TEAM_WHITE;
	board_data->piece[6][7].state = CHESS_KNIGHT;	board_data->piece[6][7].team = TEAM_WHITE;
	board_data->piece[7][7].state = CHESS_ROOK;		board_data->piece[7][7].team = TEAM_WHITE;

}

void Board_Move(Board* board, int src_x, int src_y, int dst_x, int dst_y) {

	board->piece[dst_x][dst_y] = board->piece[src_x][src_y];
	board->piece[src_x][src_y].team = TEAM_NONE;
	board->piece[src_x][src_y].state = CHESS_NONE;

	if (board->piece[dst_x][dst_y].state == CHESS_PAWN) {
		if (board->piece[dst_x][dst_y].team == TEAM_WHITE && dst_y == 0) {
			board->piece[dst_x][dst_y].state = CHESS_QUEEN;
		}
		else if (board->piece[dst_x][dst_y].team == TEAM_BLACK && dst_y == 7) {
			board->piece[dst_x][dst_y].state = CHESS_QUEEN;
		}
	}

}

bool Board_CanMove(Board* board, int src_x, int src_y, int dst_x, int dst_y) {

	if (src_x < 0 || src_x > 7 || src_y < 0 || src_y > 7)
		return false;
	if (dst_x < 0 || dst_x > 7 || dst_y < 0 || dst_y > 7)
		return false;

	if (src_x == dst_x && src_y == dst_y)
		return false;
	else if (board->piece[dst_x][dst_y].team == board->piece[src_x][src_y].team)
		return false;
		
	if (board->piece[dst_x][dst_y].team > TEAM_NONE)
		return Board_Pattern(board, (Move) { src_x, src_y, dst_x, dst_y },MOVE_CAPTURE);
	else 
		return Board_Pattern(board, (Move) { src_x, src_y, dst_x, dst_y }, MOVE_MOVE);
}

bool Board_IsKingInDanger(Board* board, ChessTeam team) {

	int king_pos_x=-1, king_pos_y=-1;

	for (int x = 0; x < 8; x++) {
		for (int y = 0; y < 8; y++) {
			if (board->piece[x][y].team == team) {
				if (board->piece[x][y].state == CHESS_KING) {
					king_pos_x = x; king_pos_y = y;
					break;
				}
			}
		}
	}

	bool88 king_danger_zone;
	Board_GetKingDangerZone(board, team, king_danger_zone);

	return king_danger_zone[king_pos_x][king_pos_y];

}

void Board_GetKingDangerZone(Board* board, ChessTeam team, bool88 king_danger_zone) {

	for (int x = 0; x < 8; x++) {
		for (int y = 0; y < 8; y++) {
			king_danger_zone[x][y] = false;
		}
	}

	for (int x = 0; x < 8; x++) {
		for (int y = 0; y < 8; y++) {
			if (board->piece[x][y].team > TEAM_NONE && board->piece[x][y].team != team) {

				for (int px = 0; px < 8; px++) {
					for (int py = 0; py < 8; py++) {

						if (x == px && y == py) {
							continue;
						}

						if (Board_Pattern(board, (Move) { x, y, px, py },MOVE_CAPTURE) == true) {
							king_danger_zone[px][py] = true;
						}

					}
				}

			}
		}
	}
	
}

void Board_Copy(Board* src, Board* dst) {

	for (int x = 0; x < 8; x++) {
		for (int y = 0; y < 8; y++) {
			dst->piece[x][y].team = src->piece[x][y].team;
			dst->piece[x][y].state = src->piece[x][y].state;
		}
	}

}

// Chess Patterns
bool Board_Pattern(Board* board, Move move, MoveType move_type) {

	switch (move_type) {
	case MOVE_MOVE: {
		switch (board->piece[move.src_x][move.src_y].state) {
		case CHESS_BISHOP: {
			if (bishop_pattern[7 - (move.src_y - move.dst_y)][7 - (move.src_x - move.dst_x)])
				return !Board_IsMoveBlocked(board, move);
			return false;
			break;
		}
		case CHESS_KING: {
			return king_pattern[7 - (move.src_y - move.dst_y)][7 - (move.src_x - move.dst_x)];
			break;
		}
		case CHESS_KNIGHT: {
			return knight_pattern[7 - (move.src_y - move.dst_y)][7 - (move.src_x - move.dst_x)];
			break;
		}
		case CHESS_PAWN: {
			if (board->piece[move.src_x][move.src_y].team == TEAM_WHITE)
				if (move.src_y > 5)
					return pawn_first_move_pattern[7 - (move.src_y - move.dst_y)][7 - (move.src_x - move.dst_x)] && up_mask_pattern[7 - (move.src_y - move.dst_y)][7 - (move.src_x - move.dst_x)];
				else
					return pawn_move_pattern[7 - (move.src_y - move.dst_y)][7 - (move.src_x - move.dst_x)] && up_mask_pattern[7 - (move.src_y - move.dst_y)][7 - (move.src_x - move.dst_x)];

			if (board->piece[move.src_x][move.src_y].team == TEAM_BLACK) {
				if (move.src_y < 2)
					return pawn_first_move_pattern[7 - (move.src_y - move.dst_y)][7 - (move.src_x - move.dst_x)] && down_mask_pattern[7 - (move.src_y - move.dst_y)][7 - (move.src_x - move.dst_x)];
				else
					return pawn_move_pattern[7 - (move.src_y - move.dst_y)][7 - (move.src_x - move.dst_x)] && down_mask_pattern[7 - (move.src_y - move.dst_y)][7 - (move.src_x - move.dst_x)];
				}

				return false;
			break;
			}
		}
		case CHESS_QUEEN: {
			return queen_pattern[7 - (move.src_y - move.dst_y)][7 - (move.src_x - move.dst_x)];
			break;
		}
		case CHESS_ROOK: {
			if (rook_pattern[7 - (move.src_y - move.dst_y)][7 - (move.src_x - move.dst_x)])
				return !Board_IsMoveBlocked(board, move);
			return false;
			break;
		}
		default: {LOG_ERROR("Uknown Chess Pattern"); return false; }
		}
	case MOVE_CAPTURE: {
		switch (board->piece[move.src_x][move.src_y].state) {
		case CHESS_BISHOP: {
			if (bishop_pattern[7 - (move.src_y - move.dst_y)][7 - (move.src_x - move.dst_x)])
				return !Board_IsMoveBlocked(board, move);
			return false;
			break;
		}
		case CHESS_KING: {
			return king_pattern[7 - (move.src_y - move.dst_y)][7 - (move.src_x - move.dst_x)];
			break;
		}
		case CHESS_KNIGHT: {
			return knight_pattern[7 - (move.src_y - move.dst_y)][7 - (move.src_x - move.dst_x)];
			break;
		}
		case CHESS_PAWN: {
			
			if (board->piece[move.src_x][move.src_y].team == TEAM_WHITE)
				return pawn_capture_pattern[7 - (move.src_y - move.dst_y)][7 - (move.src_x - move.dst_x)] && up_mask_pattern[7 - (move.src_y - move.dst_y)][7 - (move.src_x - move.dst_x)];

			if (board->piece[move.src_x][move.src_y].team == TEAM_BLACK)
				return pawn_capture_pattern[7 - (move.src_y - move.dst_y)][7 - (move.src_x - move.dst_x)] && down_mask_pattern[7 - (move.src_y - move.dst_y)][7 - (move.src_x - move.dst_x)];

			return false;
			break;
		}
		case CHESS_QUEEN: {
			return queen_pattern[7 - (move.src_y - move.dst_y)][7 - (move.src_x - move.dst_x)];
			break;
		}
		case CHESS_ROOK: {
			if (rook_pattern[7 - (move.src_y - move.dst_y)][7 - (move.src_x - move.dst_x)])
				return !Board_IsMoveBlocked(board, move);
			return false;
			break;
		}
		default: {LOG_ERROR("Uknown Chess Pattern"); return false; }
		}
	}
	}
	
}

void Board_TestGameOver(Board* board_data) {

	board_data->piece[0][0].state = CHESS_KING;	board_data->piece[0][0].team = TEAM_BLACK;
	board_data->piece[1][0].state = CHESS_NONE;	board_data->piece[1][0].team = TEAM_NONE;
	board_data->piece[2][0].state = CHESS_NONE;	board_data->piece[2][0].team = TEAM_NONE;
	board_data->piece[3][0].state = CHESS_NONE;	board_data->piece[3][0].team = TEAM_NONE;
	board_data->piece[4][0].state = CHESS_NONE;	board_data->piece[4][0].team = TEAM_NONE;
	board_data->piece[5][0].state = CHESS_NONE;	board_data->piece[5][0].team = TEAM_NONE;
	board_data->piece[6][0].state = CHESS_NONE;	board_data->piece[6][0].team = TEAM_NONE;
	board_data->piece[7][0].state = CHESS_NONE;	board_data->piece[7][0].team = TEAM_NONE;

	board_data->piece[0][1].state = CHESS_NONE;   board_data->piece[0][1].team = TEAM_NONE;
	board_data->piece[1][1].state = CHESS_NONE;   board_data->piece[1][1].team = TEAM_NONE;
	board_data->piece[2][1].state = CHESS_NONE;   board_data->piece[2][1].team = TEAM_NONE;
	board_data->piece[3][1].state = CHESS_NONE;   board_data->piece[3][1].team = TEAM_NONE;
	board_data->piece[4][1].state = CHESS_NONE;   board_data->piece[4][1].team = TEAM_NONE;
	board_data->piece[5][1].state = CHESS_NONE;   board_data->piece[5][1].team = TEAM_NONE;
	board_data->piece[6][1].state = CHESS_NONE;   board_data->piece[6][1].team = TEAM_NONE;
	board_data->piece[7][1].state = CHESS_NONE;   board_data->piece[7][1].team = TEAM_NONE;

	board_data->piece[0][2].state = CHESS_NONE;   board_data->piece[0][2].team = TEAM_NONE;
	board_data->piece[1][2].state = CHESS_NONE;   board_data->piece[1][2].team = TEAM_NONE;
	board_data->piece[2][2].state = CHESS_NONE;   board_data->piece[2][2].team = TEAM_NONE;
	board_data->piece[3][2].state = CHESS_NONE;   board_data->piece[3][2].team = TEAM_NONE;
	board_data->piece[4][2].state = CHESS_NONE;   board_data->piece[4][2].team = TEAM_NONE;
	board_data->piece[5][2].state = CHESS_NONE;   board_data->piece[5][2].team = TEAM_NONE;
	board_data->piece[6][2].state = CHESS_NONE;   board_data->piece[6][2].team = TEAM_NONE;
	board_data->piece[7][2].state = CHESS_NONE;   board_data->piece[7][2].team = TEAM_NONE;

	board_data->piece[0][3].state = CHESS_NONE;   board_data->piece[0][3].team = TEAM_NONE;
	board_data->piece[1][3].state = CHESS_NONE;   board_data->piece[1][3].team = TEAM_NONE;
	board_data->piece[2][3].state = CHESS_NONE;   board_data->piece[2][3].team = TEAM_NONE;
	board_data->piece[3][3].state = CHESS_NONE;   board_data->piece[3][3].team = TEAM_NONE;
	board_data->piece[4][3].state = CHESS_NONE;   board_data->piece[4][3].team = TEAM_NONE;
	board_data->piece[5][3].state = CHESS_NONE;   board_data->piece[5][3].team = TEAM_NONE;
	board_data->piece[6][3].state = CHESS_NONE;   board_data->piece[6][3].team = TEAM_NONE;
	board_data->piece[7][3].state = CHESS_NONE;   board_data->piece[7][3].team = TEAM_NONE;

	board_data->piece[0][4].state = CHESS_NONE;   board_data->piece[0][4].team = TEAM_NONE;
	board_data->piece[1][4].state = CHESS_NONE;   board_data->piece[1][4].team = TEAM_NONE;
	board_data->piece[2][4].state = CHESS_NONE;   board_data->piece[2][4].team = TEAM_NONE;
	board_data->piece[3][4].state = CHESS_NONE;   board_data->piece[3][4].team = TEAM_NONE;
	board_data->piece[4][4].state = CHESS_NONE;   board_data->piece[4][4].team = TEAM_NONE;
	board_data->piece[5][4].state = CHESS_NONE;   board_data->piece[5][4].team = TEAM_NONE;
	board_data->piece[6][4].state = CHESS_NONE;   board_data->piece[6][4].team = TEAM_NONE;
	board_data->piece[7][4].state = CHESS_NONE;   board_data->piece[7][4].team = TEAM_NONE;

	board_data->piece[0][5].state = CHESS_NONE;   board_data->piece[0][5].team = TEAM_NONE;
	board_data->piece[1][5].state = CHESS_NONE;   board_data->piece[1][5].team = TEAM_NONE;
	board_data->piece[2][5].state = CHESS_NONE;   board_data->piece[2][5].team = TEAM_NONE;
	board_data->piece[3][5].state = CHESS_NONE;   board_data->piece[3][5].team = TEAM_NONE;
	board_data->piece[4][5].state = CHESS_NONE;   board_data->piece[4][5].team = TEAM_NONE;
	board_data->piece[5][5].state = CHESS_NONE;   board_data->piece[5][5].team = TEAM_NONE;
	board_data->piece[6][5].state = CHESS_NONE;   board_data->piece[6][5].team = TEAM_NONE;
	board_data->piece[7][5].state = CHESS_NONE;   board_data->piece[7][5].team = TEAM_NONE;

	board_data->piece[0][6].state = CHESS_QUEEN;  board_data->piece[0][6].team = TEAM_BLACK;
	board_data->piece[1][6].state = CHESS_NONE;  board_data->piece[1][6].team = TEAM_NONE;
	board_data->piece[2][6].state = CHESS_NONE;  board_data->piece[2][6].team = TEAM_NONE;
	board_data->piece[3][6].state = CHESS_NONE;  board_data->piece[3][6].team = TEAM_NONE;
	board_data->piece[4][6].state = CHESS_NONE;  board_data->piece[4][6].team = TEAM_NONE;
	board_data->piece[5][6].state = CHESS_NONE;  board_data->piece[5][6].team = TEAM_NONE;
	board_data->piece[6][6].state = CHESS_NONE;  board_data->piece[6][6].team = TEAM_NONE;
	board_data->piece[7][6].state = CHESS_NONE;  board_data->piece[7][6].team = TEAM_NONE;

	board_data->piece[0][7].state = CHESS_KING;	board_data->piece[0][7].team = TEAM_WHITE;
	board_data->piece[1][7].state = CHESS_QUEEN;	board_data->piece[1][7].team = TEAM_BLACK;
	board_data->piece[2][7].state = CHESS_NONE;	board_data->piece[2][7].team = TEAM_NONE;
	board_data->piece[3][7].state = CHESS_NONE;	board_data->piece[3][7].team = TEAM_NONE;
	board_data->piece[4][7].state = CHESS_NONE;	board_data->piece[4][7].team = TEAM_NONE;
	board_data->piece[5][7].state = CHESS_NONE;	board_data->piece[5][7].team = TEAM_NONE;
	board_data->piece[6][7].state = CHESS_NONE;	board_data->piece[6][7].team = TEAM_NONE;
	board_data->piece[7][7].state = CHESS_NONE;	board_data->piece[7][7].team = TEAM_NONE;
}

bool Board_IsMoveBlocked(Board* board, Move move) {
	int xlen = move.src_x - move.dst_x;
	int ylen = move.src_y - move.dst_y;
	int xk = (xlen == 0) ? 0 : (xlen < 0) ? -1 : 1;
	int yk = (ylen == 0) ? 0 : (ylen < 0) ? -1 : 1;
	float k = (ylen == 0.0f) ? 1.0f : ABS((float)xlen / ylen);

	for (float x = (float)move.src_x - xk * k, y = (float)move.src_y - yk; x != move.dst_x || y != move.dst_y; x -= xk * k, y -= yk) {
		if (board->piece[(int)x][(int)y].team > TEAM_NONE) 
			return true;
	}

	return false;
}

