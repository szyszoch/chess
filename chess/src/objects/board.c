#include "objects/board.h"

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



typedef struct Chess {
	Object o;
	Piece piece[8][8];
	ChessTeam turn;
	int winner;
	bool gameover;
	bool danger_zone[TEAMS_COUNT][8][8];
	int pawn_at_end_x;
	int pawn_at_end_y;
	SDL_Point select;
	Move last_move;
} Chess;



Chess* c_create()
{
	Chess* chess= malloc(sizeof(Chess));
	if (chess == NULL) {
		LOG_ERROR("Can't allocate memory");
		return NULL;
	}

	b_newgame(chess);
	
	chess->turn = TEAM_WHITE;
	chess->winner = TEAM_NONE;
	chess->gameover = false;
	chess->pawn_at_end_x = -1;
	chess->pawn_at_end_y = -1;
	
	memset(&chess->select, -1, sizeof(SDL_Point));
	memset(&chess->o, 0, sizeof(Object));
	
	return chess;
}

void c_destroy(Chess* chess)
{
	if (chess == NULL)
		return;
	free(chess);
}

void c_render(Chess* chess)
{
	if (chess->o.hidden)
		return;

	SDL_RenderCopy(renderer, get_texture(TEXTURE_BOARD), NULL, &chess->o.pos);

	int chess_width = (chess->o.pos.w / 8);
	int chess_height = (chess->o.pos.h / 8);

	for (int x = 0; x < 8; x++) {
		for (int y = 0; y < 8; y++) {

			if (chess->piece[x][y].team == TEAM_NONE || chess->piece[x][y].chess_type == CHESS_NONE)
				continue;

			int tex_id = c_get_texture_id(chess->piece[x][y].chess_type, chess->piece[x][y].team);

			if (x == chess->select.x && y == chess->select.y)
				continue;

			SDL_Rect chess_pos = { x * chess_width, y * chess_height, chess_width, chess_height };
			SDL_RenderCopy(renderer, get_texture(tex_id), NULL, &chess_pos);
		}
	}

	if (chess->select.x != -1 && chess->select.y != -1) {
		int mx, my;
		SDL_GetMouseState(&mx, &my);

		int x = chess->select.x;
		int y = chess->select.y;

		int tex_id = c_get_texture_id(chess->piece[x][y].chess_type, chess->piece[x][y].team);

		SDL_Rect chess_pos = {mx - chess_width / 2, my - chess_height / 2, chess_width, chess_height };
		SDL_RenderCopy(renderer, get_texture(tex_id), NULL, &chess_pos);
	}

}

void c_handle(Chess* chess)
{
	memset(&chess->last_move, -1, sizeof(Move));

	if (chess->o.frozen)
		return;

	if (!is_object_hover(&chess->o)) {
		memset(&chess->select, -1, sizeof(SDL_Point));
		return;
	}

	if (event_handler.type == SDL_MOUSEBUTTONUP) {

		if (chess->select.x != -1 && chess->select.y != -1) {
			int x = 0;
			int y = 0;
			SDL_GetMouseState(&x, &y);

			x = (x - chess->o.pos.x) / (chess->o.pos.w / 8);
			y = (y - chess->o.pos.y) / (chess->o.pos.h / 8);

			if (x < 0 || x > 7 || y < 0 || y > 7) {
				chess->select.x = -1;
				chess->select.y = -1;
				return;
			}

			Move move = { chess->select.x,
							chess->select.y,
							x,
							y };

			if (Board_CanMove(chess,move)) {
				Board_Move(chess, move);
				Board_ChangeTurn(chess);
			}

			memset(&chess->select, -1, sizeof(SDL_Point));
		}

	}

	if (event_handler.type == SDL_MOUSEBUTTONDOWN) {
		int x = 0;
		int y = 0;
		SDL_GetMouseState(&x, &y);

		x = (x - chess->o.pos.x) / (chess->o.pos.w / 8);
		y = (y - chess->o.pos.y) / (chess->o.pos.h / 8);

		if (x < 0 || x > 7 || y < 0 || y > 7) {
			return;
		}

		if (chess->piece[x][y].team == chess->turn) {
			chess->select.x = x;
			chess->select.y = y;
			return;
		}
	}
}

TextureID c_get_texture_id(ChessType type, ChessTeam team)
{
	switch (team) {
	case TEAM_WHITE: {
		switch (type) {
		case CHESS_BISHOP:	{return TEXTURE_WHITE_BISHOP;	break; }
		case CHESS_KING:	{return TEXTURE_WHITE_KING;		break; }
		case CHESS_KNIGHT:	{return TEXTURE_WHITE_KNIGHT;	break; }
		case CHESS_PAWN:	{return TEXTURE_WHITE_PAWN;		break; }
		case CHESS_QUEEN:	{return TEXTURE_WHITE_QUEEN;	break; }
		case CHESS_ROOK:	{return TEXTURE_WHITE_ROOK;		break; }
		}
		break;
	}
	case TEAM_BLACK: {
		switch (type) {
		case CHESS_BISHOP:	{return TEXTURE_BLACK_BISHOP;	break; }
		case CHESS_KING:	{return TEXTURE_BLACK_KING;		break; }
		case CHESS_KNIGHT:	{return TEXTURE_BLACK_KNIGHT;	break; }
		case CHESS_PAWN:	{return TEXTURE_BLACK_PAWN;		break; }
		case CHESS_QUEEN:	{return TEXTURE_BLACK_QUEEN;	break; }
		case CHESS_ROOK:	{return TEXTURE_BLACK_ROOK;		break; }
		}
		break;
	}
	}

	LOG_WARN("Undefined chess type or team");
	return 0;
}

Object* c_get_object(Chess* chess)
{
	return &chess->o;
}

ChessTeam c_get_turn(Chess* chess)
{
	return chess->turn;
}

Move c_get_last_move(Chess* chess)
{
	return chess->last_move;
}



void Board_ChangeTurn(Chess* board) {
	board->turn = (board->turn == TEAM_WHITE) ? TEAM_BLACK : TEAM_WHITE;
}

void b_newgame(Chess* chess) 
{
	chess->piece[0][0].chess_type = CHESS_ROOK;		chess->piece[0][0].team = TEAM_BLACK;
	chess->piece[1][0].chess_type = CHESS_KNIGHT;	chess->piece[1][0].team = TEAM_BLACK;
	chess->piece[2][0].chess_type = CHESS_BISHOP;	chess->piece[2][0].team = TEAM_BLACK;
	chess->piece[3][0].chess_type = CHESS_QUEEN;		chess->piece[3][0].team = TEAM_BLACK;
	chess->piece[4][0].chess_type = CHESS_KING;		chess->piece[4][0].team = TEAM_BLACK;
	chess->piece[5][0].chess_type = CHESS_BISHOP;	chess->piece[5][0].team = TEAM_BLACK;
	chess->piece[6][0].chess_type = CHESS_KNIGHT;	chess->piece[6][0].team = TEAM_BLACK;
	chess->piece[7][0].chess_type = CHESS_ROOK;		chess->piece[7][0].team = TEAM_BLACK;

	chess->piece[0][1].chess_type = CHESS_PAWN;   chess->piece[0][1].team = TEAM_BLACK;
	chess->piece[1][1].chess_type = CHESS_PAWN;   chess->piece[1][1].team = TEAM_BLACK;
	chess->piece[2][1].chess_type = CHESS_PAWN;   chess->piece[2][1].team = TEAM_BLACK;
	chess->piece[3][1].chess_type = CHESS_PAWN;   chess->piece[3][1].team = TEAM_BLACK;
	chess->piece[4][1].chess_type = CHESS_PAWN;   chess->piece[4][1].team = TEAM_BLACK;
	chess->piece[5][1].chess_type = CHESS_PAWN;   chess->piece[5][1].team = TEAM_BLACK;
	chess->piece[6][1].chess_type = CHESS_PAWN;   chess->piece[6][1].team = TEAM_BLACK;
	chess->piece[7][1].chess_type = CHESS_PAWN;   chess->piece[7][1].team = TEAM_BLACK;
										    
	chess->piece[0][2].chess_type = CHESS_NONE;   chess->piece[0][2].team = TEAM_NONE;
	chess->piece[1][2].chess_type = CHESS_NONE;   chess->piece[1][2].team = TEAM_NONE;
	chess->piece[2][2].chess_type = CHESS_NONE;   chess->piece[2][2].team = TEAM_NONE;
	chess->piece[3][2].chess_type = CHESS_NONE;   chess->piece[3][2].team = TEAM_NONE;
	chess->piece[4][2].chess_type = CHESS_NONE;   chess->piece[4][2].team = TEAM_NONE;
	chess->piece[5][2].chess_type = CHESS_NONE;   chess->piece[5][2].team = TEAM_NONE;
	chess->piece[6][2].chess_type = CHESS_NONE;   chess->piece[6][2].team = TEAM_NONE;
	chess->piece[7][2].chess_type = CHESS_NONE;   chess->piece[7][2].team = TEAM_NONE;
										    
	chess->piece[0][3].chess_type = CHESS_NONE;   chess->piece[0][3].team = TEAM_NONE;
	chess->piece[1][3].chess_type = CHESS_NONE;   chess->piece[1][3].team = TEAM_NONE;
	chess->piece[2][3].chess_type = CHESS_NONE;   chess->piece[2][3].team = TEAM_NONE;
	chess->piece[3][3].chess_type = CHESS_NONE;   chess->piece[3][3].team = TEAM_NONE;
	chess->piece[4][3].chess_type = CHESS_NONE;   chess->piece[4][3].team = TEAM_NONE;
	chess->piece[5][3].chess_type = CHESS_NONE;   chess->piece[5][3].team = TEAM_NONE;
	chess->piece[6][3].chess_type = CHESS_NONE;   chess->piece[6][3].team = TEAM_NONE;
	chess->piece[7][3].chess_type = CHESS_NONE;   chess->piece[7][3].team = TEAM_NONE;
										    
	chess->piece[0][4].chess_type = CHESS_NONE;   chess->piece[0][4].team = TEAM_NONE;
	chess->piece[1][4].chess_type = CHESS_NONE;   chess->piece[1][4].team = TEAM_NONE;
	chess->piece[2][4].chess_type = CHESS_NONE;   chess->piece[2][4].team = TEAM_NONE;
	chess->piece[3][4].chess_type = CHESS_NONE;   chess->piece[3][4].team = TEAM_NONE;
	chess->piece[4][4].chess_type = CHESS_NONE;   chess->piece[4][4].team = TEAM_NONE;
	chess->piece[5][4].chess_type = CHESS_NONE;   chess->piece[5][4].team = TEAM_NONE;
	chess->piece[6][4].chess_type = CHESS_NONE;   chess->piece[6][4].team = TEAM_NONE;
	chess->piece[7][4].chess_type = CHESS_NONE;   chess->piece[7][4].team = TEAM_NONE;
										    
	chess->piece[0][5].chess_type = CHESS_NONE;   chess->piece[0][5].team = TEAM_NONE;
	chess->piece[1][5].chess_type = CHESS_NONE;   chess->piece[1][5].team = TEAM_NONE;
	chess->piece[2][5].chess_type = CHESS_NONE;   chess->piece[2][5].team = TEAM_NONE;
	chess->piece[3][5].chess_type = CHESS_NONE;   chess->piece[3][5].team = TEAM_NONE;
	chess->piece[4][5].chess_type = CHESS_NONE;   chess->piece[4][5].team = TEAM_NONE;
	chess->piece[5][5].chess_type = CHESS_NONE;   chess->piece[5][5].team = TEAM_NONE;
	chess->piece[6][5].chess_type = CHESS_NONE;   chess->piece[6][5].team = TEAM_NONE;
	chess->piece[7][5].chess_type = CHESS_NONE;   chess->piece[7][5].team = TEAM_NONE;
										    
	chess->piece[0][6].chess_type = CHESS_PAWN;  chess->piece[0][6].team = TEAM_WHITE;
	chess->piece[1][6].chess_type = CHESS_PAWN;  chess->piece[1][6].team = TEAM_WHITE;
	chess->piece[2][6].chess_type = CHESS_PAWN;  chess->piece[2][6].team = TEAM_WHITE;
	chess->piece[3][6].chess_type = CHESS_PAWN;  chess->piece[3][6].team = TEAM_WHITE;
	chess->piece[4][6].chess_type = CHESS_PAWN;  chess->piece[4][6].team = TEAM_WHITE;
	chess->piece[5][6].chess_type = CHESS_PAWN;  chess->piece[5][6].team = TEAM_WHITE;
	chess->piece[6][6].chess_type = CHESS_PAWN;  chess->piece[6][6].team = TEAM_WHITE;
	chess->piece[7][6].chess_type = CHESS_PAWN;  chess->piece[7][6].team = TEAM_WHITE;

	chess->piece[0][7].chess_type = CHESS_ROOK;		chess->piece[0][7].team = TEAM_WHITE;
	chess->piece[1][7].chess_type = CHESS_KNIGHT;	chess->piece[1][7].team = TEAM_WHITE;
	chess->piece[2][7].chess_type = CHESS_BISHOP;	chess->piece[2][7].team = TEAM_WHITE;
	chess->piece[3][7].chess_type = CHESS_QUEEN;		chess->piece[3][7].team = TEAM_WHITE;
	chess->piece[4][7].chess_type = CHESS_KING;		chess->piece[4][7].team = TEAM_WHITE;
	chess->piece[5][7].chess_type = CHESS_BISHOP;	chess->piece[5][7].team = TEAM_WHITE;
	chess->piece[6][7].chess_type = CHESS_KNIGHT;	chess->piece[6][7].team = TEAM_WHITE;
	chess->piece[7][7].chess_type = CHESS_ROOK;		chess->piece[7][7].team = TEAM_WHITE;

	Board_UpdateDangerZone(chess);
}

void Board_Move(Chess* chess, Move move) {

	chess->piece[move.dst_x][move.dst_y] = chess->piece[move.src_x][move.src_y];
	chess->piece[move.src_x][move.src_y].team = TEAM_NONE;
	chess->piece[move.src_x][move.src_y].chess_type = CHESS_NONE;

	if (chess->piece[move.dst_x][move.dst_y].chess_type == CHESS_PAWN) {
		if ( (chess->piece[move.dst_x][move.dst_y].team == TEAM_WHITE && move.dst_y == 0) || (chess->piece[move.dst_x][move.dst_y].team == TEAM_BLACK && move.dst_y == 7) ) {
			chess->pawn_at_end_x = move.dst_x;
			chess->pawn_at_end_y = move.dst_y;
		}
	}
	chess->last_move = move;
	Board_UpdateDangerZone(chess);
}

bool Board_CanMove(Chess* board, Move move) {

	if (move.src_x < 0 || move.src_x > 7 || move.src_y < 0 || move.src_y > 7)
		return false;
	if (move.dst_x < 0 || move.dst_x > 7 || move.dst_y < 0 || move.dst_y > 7)
		return false;

	if (move.src_x == move.dst_x && move.src_y == move.dst_y)
		return false;
	else if (board->piece[move.dst_x][move.dst_y].team == board->piece[move.src_x][move.src_y].team)
		return false;
		
	if (board->piece[move.src_x][move.src_y].chess_type == CHESS_KING) {
		if (board->danger_zone[board->turn][move.dst_x][move.dst_y] == true) {
			return false;
		}
		Chess test_board;
		Board_Copy(board, &test_board);

		if (test_board.piece[move.dst_x][move.dst_y].team > TEAM_NONE)
			Board_Pattern(&test_board, move, MOVE_CAPTURE);
		else
			Board_Pattern(&test_board, move, MOVE_MOVE);

		Board_Move(&test_board, move);
		if (test_board.danger_zone[board->turn][move.dst_x][move.dst_y] == true) {
			return false;
		}
	}
	else {
		int king_pos_x;
		int king_pos_y;
		Board_FindKing(board,board->turn,&king_pos_x, &king_pos_y);
		if (king_pos_x == -1 || king_pos_y == -1) {}
			
		else if (board->danger_zone[board->turn][king_pos_x][king_pos_y] == true) {
			
			Chess test_board;
			Board_Copy(board, &test_board);

			if (test_board.piece[move.dst_x][move.dst_y].team > TEAM_NONE)
				Board_Pattern(&test_board, move, MOVE_CAPTURE);
			else
				Board_Pattern(&test_board, move, MOVE_MOVE);

			Board_Move(&test_board, move);
			if (test_board.danger_zone[board->turn][king_pos_x][king_pos_y]) {
				return false;
			}
		}

	}

	if (board->piece[move.dst_x][move.dst_y].team > TEAM_NONE)
		return Board_Pattern(board,move,MOVE_CAPTURE);
	else 
		return Board_Pattern(board,move, MOVE_MOVE);
}

void Board_Copy(Chess* src, Chess* dst) {

	for (int x = 0; x < 8; x++) {
		for (int y = 0; y < 8; y++) {
			dst->piece[x][y].team = src->piece[x][y].team;
			dst->piece[x][y].chess_type = src->piece[x][y].chess_type;
		}
	}
	
	for (int team = 0; team < TEAMS_COUNT; team++) {
		for (int x = 0; x < 8; x++) {
			for (int y = 0; y < 8; y++) {
				dst->danger_zone[team][x][y] = src->danger_zone[team][x][y];
			}
		}
	}

	dst->turn = src->turn;
	dst->winner = src->winner;
	dst->gameover = src->gameover;
}

bool Board_Pattern(Chess* board, Move move, MoveType move_type) {

	switch (move_type) {
	case MOVE_MOVE: {
		switch (board->piece[move.src_x][move.src_y].chess_type) {
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
			if( queen_pattern[7 - (move.src_y - move.dst_y)][7 - (move.src_x - move.dst_x)] )
				return !Board_IsMoveBlocked(board, move);
			return false;
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
		switch (board->piece[move.src_x][move.src_y].chess_type) {
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
			if (queen_pattern[7 - (move.src_y - move.dst_y)][7 - (move.src_x - move.dst_x)])
				return !Board_IsMoveBlocked(board, move);
			return false;
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

	return false;
	
}

void Board_TestGameOver(Chess* board_data) {

	board_data->piece[0][0].chess_type = CHESS_KING;	board_data->piece[0][0].team = TEAM_BLACK;
	board_data->piece[1][0].chess_type = CHESS_NONE;	board_data->piece[1][0].team = TEAM_NONE;
	board_data->piece[2][0].chess_type = CHESS_NONE;	board_data->piece[2][0].team = TEAM_NONE;
	board_data->piece[3][0].chess_type = CHESS_NONE;	board_data->piece[3][0].team = TEAM_NONE;
	board_data->piece[4][0].chess_type = CHESS_NONE;	board_data->piece[4][0].team = TEAM_NONE;
	board_data->piece[5][0].chess_type = CHESS_NONE;	board_data->piece[5][0].team = TEAM_NONE;
	board_data->piece[6][0].chess_type = CHESS_NONE;	board_data->piece[6][0].team = TEAM_NONE;
	board_data->piece[7][0].chess_type = CHESS_NONE;	board_data->piece[7][0].team = TEAM_NONE;

	board_data->piece[0][1].chess_type = CHESS_NONE;   board_data->piece[0][1].team = TEAM_NONE;
	board_data->piece[1][1].chess_type = CHESS_NONE;   board_data->piece[1][1].team = TEAM_NONE;
	board_data->piece[2][1].chess_type = CHESS_NONE;   board_data->piece[2][1].team = TEAM_NONE;
	board_data->piece[3][1].chess_type = CHESS_NONE;   board_data->piece[3][1].team = TEAM_NONE;
	board_data->piece[4][1].chess_type = CHESS_NONE;   board_data->piece[4][1].team = TEAM_NONE;
	board_data->piece[5][1].chess_type = CHESS_NONE;   board_data->piece[5][1].team = TEAM_NONE;
	board_data->piece[6][1].chess_type = CHESS_NONE;   board_data->piece[6][1].team = TEAM_NONE;
	board_data->piece[7][1].chess_type = CHESS_NONE;   board_data->piece[7][1].team = TEAM_NONE;

	board_data->piece[0][2].chess_type = CHESS_NONE;   board_data->piece[0][2].team = TEAM_NONE;
	board_data->piece[1][2].chess_type = CHESS_NONE;   board_data->piece[1][2].team = TEAM_NONE;
	board_data->piece[2][2].chess_type = CHESS_NONE;   board_data->piece[2][2].team = TEAM_NONE;
	board_data->piece[3][2].chess_type = CHESS_NONE;   board_data->piece[3][2].team = TEAM_NONE;
	board_data->piece[4][2].chess_type = CHESS_NONE;   board_data->piece[4][2].team = TEAM_NONE;
	board_data->piece[5][2].chess_type = CHESS_NONE;   board_data->piece[5][2].team = TEAM_NONE;
	board_data->piece[6][2].chess_type = CHESS_NONE;   board_data->piece[6][2].team = TEAM_NONE;
	board_data->piece[7][2].chess_type = CHESS_NONE;   board_data->piece[7][2].team = TEAM_NONE;

	board_data->piece[0][3].chess_type = CHESS_NONE;   board_data->piece[0][3].team = TEAM_NONE;
	board_data->piece[1][3].chess_type = CHESS_NONE;   board_data->piece[1][3].team = TEAM_NONE;
	board_data->piece[2][3].chess_type = CHESS_NONE;   board_data->piece[2][3].team = TEAM_NONE;
	board_data->piece[3][3].chess_type = CHESS_NONE;   board_data->piece[3][3].team = TEAM_NONE;
	board_data->piece[4][3].chess_type = CHESS_NONE;   board_data->piece[4][3].team = TEAM_NONE;
	board_data->piece[5][3].chess_type = CHESS_NONE;   board_data->piece[5][3].team = TEAM_NONE;
	board_data->piece[6][3].chess_type = CHESS_NONE;   board_data->piece[6][3].team = TEAM_NONE;
	board_data->piece[7][3].chess_type = CHESS_NONE;   board_data->piece[7][3].team = TEAM_NONE;

	board_data->piece[0][4].chess_type = CHESS_NONE;   board_data->piece[0][4].team = TEAM_NONE;
	board_data->piece[1][4].chess_type = CHESS_NONE;   board_data->piece[1][4].team = TEAM_NONE;
	board_data->piece[2][4].chess_type = CHESS_NONE;   board_data->piece[2][4].team = TEAM_NONE;
	board_data->piece[3][4].chess_type = CHESS_NONE;   board_data->piece[3][4].team = TEAM_NONE;
	board_data->piece[4][4].chess_type = CHESS_NONE;   board_data->piece[4][4].team = TEAM_NONE;
	board_data->piece[5][4].chess_type = CHESS_NONE;   board_data->piece[5][4].team = TEAM_NONE;
	board_data->piece[6][4].chess_type = CHESS_NONE;   board_data->piece[6][4].team = TEAM_NONE;
	board_data->piece[7][4].chess_type = CHESS_NONE;   board_data->piece[7][4].team = TEAM_NONE;

	board_data->piece[0][5].chess_type = CHESS_NONE;   board_data->piece[0][5].team = TEAM_NONE;
	board_data->piece[1][5].chess_type = CHESS_NONE;   board_data->piece[1][5].team = TEAM_NONE;
	board_data->piece[2][5].chess_type = CHESS_NONE;   board_data->piece[2][5].team = TEAM_NONE;
	board_data->piece[3][5].chess_type = CHESS_NONE;   board_data->piece[3][5].team = TEAM_NONE;
	board_data->piece[4][5].chess_type = CHESS_NONE;   board_data->piece[4][5].team = TEAM_NONE;
	board_data->piece[5][5].chess_type = CHESS_NONE;   board_data->piece[5][5].team = TEAM_NONE;
	board_data->piece[6][5].chess_type = CHESS_NONE;   board_data->piece[6][5].team = TEAM_NONE;
	board_data->piece[7][5].chess_type = CHESS_NONE;   board_data->piece[7][5].team = TEAM_NONE;

	board_data->piece[0][6].chess_type = CHESS_QUEEN;  board_data->piece[0][6].team = TEAM_BLACK;
	board_data->piece[1][6].chess_type = CHESS_NONE;  board_data->piece[1][6].team = TEAM_NONE;
	board_data->piece[2][6].chess_type = CHESS_NONE;  board_data->piece[2][6].team = TEAM_NONE;
	board_data->piece[3][6].chess_type = CHESS_NONE;  board_data->piece[3][6].team = TEAM_NONE;
	board_data->piece[4][6].chess_type = CHESS_NONE;  board_data->piece[4][6].team = TEAM_NONE;
	board_data->piece[5][6].chess_type = CHESS_NONE;  board_data->piece[5][6].team = TEAM_NONE;
	board_data->piece[6][6].chess_type = CHESS_NONE;  board_data->piece[6][6].team = TEAM_NONE;
	board_data->piece[7][6].chess_type = CHESS_NONE;  board_data->piece[7][6].team = TEAM_NONE;

	board_data->piece[0][7].chess_type = CHESS_KING;	board_data->piece[0][7].team = TEAM_WHITE;
	board_data->piece[1][7].chess_type = CHESS_QUEEN;	board_data->piece[1][7].team = TEAM_BLACK;
	board_data->piece[2][7].chess_type = CHESS_NONE;	board_data->piece[2][7].team = TEAM_NONE;
	board_data->piece[3][7].chess_type = CHESS_NONE;	board_data->piece[3][7].team = TEAM_NONE;
	board_data->piece[4][7].chess_type = CHESS_NONE;	board_data->piece[4][7].team = TEAM_NONE;
	board_data->piece[5][7].chess_type = CHESS_NONE;	board_data->piece[5][7].team = TEAM_NONE;
	board_data->piece[6][7].chess_type = CHESS_NONE;	board_data->piece[6][7].team = TEAM_NONE;
	board_data->piece[7][7].chess_type = CHESS_NONE;	board_data->piece[7][7].team = TEAM_NONE;
	Board_UpdateDangerZone(board_data);
}

bool Board_IsMoveBlocked(Chess* board, Move move) {
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

bool Board_GameOver(Chess* board, ChessTeam team) {

	for (int srcx = 0; srcx < 8; srcx++) {
		for (int srcy = 0; srcy < 8; srcy++) {
			for (int dstx = 0; dstx < 8; dstx++) {
				for (int dsty = 0; dsty < 8; dsty++) {
					if (board->piece[srcx][srcy].team != team) {
						continue;
					}
					if (board->piece[srcx][srcy].chess_type == CHESS_NONE) {
						continue;
					}
					if (Board_CanMove(board,(Move){srcx,srcy,dstx,dsty}) == true) {
						return false;
					}
				}
			}
		}
	}

	int king_pos_x;
	int king_pos_y;
	Board_FindKing(board, board->turn, &king_pos_x, &king_pos_y);
	if (king_pos_x == -1 || king_pos_y == -1) {}
	else {
		if (board->danger_zone[team][king_pos_x][king_pos_y] == true) {
			LOG_INFO("Szach mat");
		}
		else {
			LOG_INFO("Can't move");
		}
	}

	board->gameover = true;
	board->winner = (board->turn == TEAM_WHITE) ? TEAM_BLACK : TEAM_WHITE;

	return true;
}

void Board_UpdateDangerZone(Chess* board) {

	for (int team = 0; team < TEAMS_COUNT; team++) {
		for (int x = 0; x < 8; x++) {
			for (int y = 0; y < 8; y++) {
				board->danger_zone[team][x][y] = false;
			}
		}
	}

	for (int team = 0; team < TEAMS_COUNT; team++) {
		for (int x = 0; x < 8; x++) {
			for (int y = 0; y < 8; y++) {

				if (board->piece[x][y].team > TEAM_NONE && board->piece[x][y].team != team) {

					for (int px = 0; px < 8; px++) {
						for (int py = 0; py < 8; py++) {

							if (Board_Pattern(board, (Move) { x, y, px, py }, MOVE_CAPTURE) == true) {
								board->danger_zone[team][px][py] = true;
							}

						}
					}

				}

			}
		}
	}

}

void Board_FindKing(Chess* board, ChessTeam team, int* x, int* y) {
	
	*x = -1;
	*y = -1;

	for (int px = 0; px < 8; px++) {
		for (int py = 0; py < 8; py++) {
			if (board->piece[px][py].team == team) {
				if (board->piece[px][py].chess_type == CHESS_KING) {
					*x = px; *y = py;
					break;
				}
			}
		}
	}

}

void Board_ChangePawn(Chess* board, ChessType chess) {
	if (board->pawn_at_end_x < 0 || board->pawn_at_end_x > 7 || board->pawn_at_end_y < 0 || board->pawn_at_end_y > 7) {
		LOG_ERROR("Chess out of board");
		return;
	}
	board->piece[board->pawn_at_end_x][board->pawn_at_end_y].chess_type = (int)chess;
	board->pawn_at_end_x = -1;
	board->pawn_at_end_y = -1;
}
