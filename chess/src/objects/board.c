#include "objects/board.h"

void board_restart(Board* board)
{
	const int type[8][8] = {
		{ 5, 2, 0, 4, 1, 0, 2, 5},
		{ 3, 3, 3, 3, 3, 3, 3, 3},
		{-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1},
		{ 3, 3, 3, 3, 3, 3, 3, 3},
		{ 5, 2, 0, 4, 1, 0, 2, 5}
	};

	const int team[8][8] = {
		{ 1, 1, 1, 1, 1, 1, 1, 1},
		{ 1, 1, 1, 1, 1, 1, 1, 1},
		{-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1},
		{ 0, 0, 0, 0, 0, 0, 0, 0},
		{ 0, 0, 0, 0, 0, 0, 0, 0}
	};

	memcpy(board->type, type, sizeof(int[8][8]));
	memcpy(board->team, team, sizeof(int[8][8]));
}

void board_test_gameover(Board* board) 
{
	const int type[8][8] = {
		{-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1},
		{ 4,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1},
		{ 1,-1, 4,-1,-1,-1,-1,-1}
	};

	const int team[8][8] = {
		{-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1},
		{ 1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1},
		{ 0,-1, 1,-1,-1,-1,-1,-1}
	};

	memcpy(board->type, type, sizeof(int[8][8]));
	memcpy(board->team, team, sizeof(int[8][8]));
}

void board_move(Board* board, Move m)
{
	board->team[m.dst_y][m.dst_x] = board->team[m.src_y][m.src_x];
	board->type[m.dst_y][m.dst_x] = board->type[m.src_y][m.src_x];
	board->team[m.src_y][m.src_x] = TEAM_NONE;
	board->type[m.src_y][m.src_x] = CHESS_NONE;

	if (board->type[m.dst_y][m.dst_x] == CHESS_PAWN) {
		if (board->team[m.dst_y][m.dst_x] == TEAM_WHITE && m.dst_y == 0) {
			board->type[m.dst_y][m.dst_x] = CHESS_QUEEN;
		}
		else if (board->team[m.dst_y][m.dst_x] == TEAM_BLACK && m.dst_y == 7) {
			board->type[m.dst_y][m.dst_x] = CHESS_QUEEN;
		}
	}
	
}

bool board_can_move(const Board* board, Move m) {

	if (!board_check_move_validation(m))
		return false;

	if (board->team[m.dst_y][m.dst_x] == board->team[m.src_y][m.src_x])
		return false;

	if (!board_can_protect_king(board, m))
		return false;

	if (board->team[m.dst_y][m.dst_x] > TEAM_NONE)
		return board_pattern(board, MOVE_CAPTURE, m);
	else
		return board_pattern(board, MOVE_MOVE, m);
}

bool board_check_move_validation(Move m)
{
	if (m.src_x < 0 || m.src_x > 7 || m.src_y < 0 || m.src_y > 7)
		return false;
	if (m.dst_x < 0 || m.dst_x > 7 || m.dst_y < 0 || m.dst_y > 7)
		return false;
	if (m.src_x == m.dst_x && m.src_y == m.dst_y)
		return false;
	return true;
}

bool board_can_protect_king(const Board* board, Move m)
{
	Board test_board;
	memcpy(&test_board, board, sizeof(Board));

	if (test_board.team[m.dst_y][m.dst_x] > TEAM_NONE) {
		if (!board_pattern(&test_board, MOVE_CAPTURE, m))
			return false;
	}
	else {
		if (!board_pattern(&test_board, MOVE_MOVE, m))
			return false;
	}

	board_move(&test_board, m);
	
	bool danger_zone[8][8];
	int king_pos_x, king_pos_y;

	board_get_dangerzone(board, board->team[m.src_y][m.src_x], danger_zone);
	board_find_king(board, board->team[m.src_y][m.src_x], &king_pos_x, &king_pos_y);

	return (!danger_zone[king_pos_y][king_pos_x]);
}

bool board_is_move_blocked(const Board* board, Move m) 
{
	int xk = (m.src_x - m.dst_x < 0) ? -1 : (m.src_x - m.dst_x > 0) ? 1 : 0;
	int yk = (m.src_y - m.dst_y < 0) ? -1 : (m.src_y - m.dst_y > 0) ? 1 : 0;

	int x = m.src_x - xk;
	int y = m.src_y - yk;

	while (x != m.dst_x && y != m.dst_y) {
		if (board->team[y][x] > TEAM_NONE)
			return true;
		x -= xk;
		y -= yk;
	}

	return false;
}

void board_get_dangerzone(const Board* board, ChessTeam team, bool danger_zone[8][8])
{
	memset(danger_zone, 0, sizeof(bool[8][8]));
	
	for (int x = 0; x < 8; x++) {
		for (int y = 0; y < 8; y++) {

			if (board->team[y][x] > TEAM_NONE && board->team[y][x] != team) {

				for (int px = 0; px < 8; px++) {
					for (int py = 0; py < 8; py++) {

						if (board_pattern(board, MOVE_CAPTURE, (Move) { x, y, px, py }) == true) {
							danger_zone[py][px] = true;
						}

					}
				}

			}

		}
	}
}

void board_find_king(const Board* board, ChessTeam team, int* x, int* y) {

	*x = -1;
	*y = -1;

	for (int px = 0; px < 8; px++) {
		for (int py = 0; py < 8; py++) {
			if (board->team[py][px] == team) {
				if (board->type[py][px] == CHESS_KING) {
					*x = px; *y = py;
					break;
				}
			}
		}
	}

}

bool board_is_gameover(const Board* board, ChessTeam team)
{
	for (int srcx = 0; srcx < 8; srcx++) {
		for (int srcy = 0; srcy < 8; srcy++) {
			for (int dstx = 0; dstx < 8; dstx++) {
				for (int dsty = 0; dsty < 8; dsty++) {
					if (board->team[srcy][srcx] != team) {
						continue;
					}
					if (board->type[srcy][srcx] == CHESS_NONE) {
						continue;
					}
					if (board_can_move(board, (Move) { srcx, srcy, dstx, dsty }) == true) {
						return false;
					}
				}
			}
		}
	}

	int king_pos_x;
	int king_pos_y;
	board_find_king(board, team, &king_pos_x, &king_pos_y);
	if (king_pos_x == -1 || king_pos_y == -1) {}
	else {
		bool danger_zone[8][8];
		board_get_dangerzone(board, team, danger_zone);
		if (danger_zone[king_pos_x][king_pos_y] == true) {
			LOG_DEBUG(SDL_LOG_CATEGORY_APPLICATION, "Szach mat");
		}
		else {
			LOG_DEBUG(SDL_LOG_CATEGORY_APPLICATION, "Can't move");
		}
	}

	return true;
}



bool board_pattern(const Board* board, MoveType move_type, Move m)
{
	switch (board->type[m.src_y][m.src_x]) {
	case CHESS_BISHOP: {
		return board_pattern_bishop(board, move_type, m);
		break;
	}
	case CHESS_KING: {
		return board_pattern_king(board, move_type, m);
		break;
	}
	case CHESS_KNIGHT: {
		return board_pattern_knight(board, move_type, m);
		break;
	}
	case CHESS_PAWN: {
		return board_pattern_pawn(board, move_type, m);
		break;
	}
	case CHESS_QUEEN: {
		return board_pattern_queen(board, move_type, m);
		break;
	}
	case CHESS_ROOK: {
		return board_pattern_rook(board, move_type, m);
		break;
	}
	default: {LOG_ERROR(SDL_LOG_CATEGORY_SYSTEM, "Uknown Chess Pattern"); return false; }
	}
}

bool board_pattern_bishop(const Board* board, MoveType move_type, Move m)
{
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

	if (bishop_pattern[7 - (m.src_y - m.dst_y)][7 - (m.src_x - m.dst_x)])
		return !board_is_move_blocked(board, m);
	return false;
}

bool board_pattern_king(const Board* board, MoveType move_type, Move m)
{
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

	return king_pattern[7 - (m.src_y - m.dst_y)][7 - (m.src_x - m.dst_x)];
}

bool board_pattern_knight(const Board* board, MoveType move_type, Move m)
{
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

	return knight_pattern[7 - (m.src_y - m.dst_y)][7 - (m.src_x - m.dst_x)];
}

bool board_pattern_pawn(const Board* board, MoveType move_type, Move m)
{
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
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
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
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};

	if (move_type == MOVE_MOVE) {
		if (board->team[m.src_y][m.src_x] == TEAM_WHITE)
			if (m.src_y > 5)
				return pawn_first_move_pattern[7 - (m.src_y - m.dst_y)][7 - (m.src_x - m.dst_x)] && up_mask_pattern[7 - (m.src_y - m.dst_y)][7 - (m.src_x - m.dst_x)];
			else
				return pawn_move_pattern[7 - (m.src_y - m.dst_y)][7 - (m.src_x - m.dst_x)] && up_mask_pattern[7 - (m.src_y - m.dst_y)][7 - (m.src_x - m.dst_x)];

		else if (board->team[m.src_y][m.src_x] == TEAM_BLACK) {
			if (m.src_y < 2)
				return pawn_first_move_pattern[7 - (m.src_y - m.dst_y)][7 - (m.src_x - m.dst_x)] && down_mask_pattern[7 - (m.src_y - m.dst_y)][7 - (m.src_x - m.dst_x)];
			else
				return pawn_move_pattern[7 - (m.src_y - m.dst_y)][7 - (m.src_x - m.dst_x)] && down_mask_pattern[7 - (m.src_y - m.dst_y)][7 - (m.src_x - m.dst_x)];
		}
	}

	else {
		if (board->team[m.src_y][m.src_x] == TEAM_WHITE)
			return pawn_capture_pattern[7 - (m.src_y - m.dst_y)][7 - (m.src_x - m.dst_x)] && up_mask_pattern[7 - (m.src_y - m.dst_y)][7 - (m.src_x - m.dst_x)];

		if (board->team[m.src_y][m.src_x] == TEAM_BLACK)
			return pawn_capture_pattern[7 - (m.src_y - m.dst_y)][7 - (m.src_x - m.dst_x)] && down_mask_pattern[7 - (m.src_y - m.dst_y)][7 - (m.src_x - m.dst_x)];
	}

	
	return false;
}

bool board_pattern_queen(const Board* board, MoveType move_type, Move m)
{
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

	if (queen_pattern[7 - (m.src_y - m.dst_y)][7 - (m.src_x - m.dst_x)])
		return !board_is_move_blocked(board, m);
	return false;
}

bool board_pattern_rook(const Board* board, MoveType move_type, Move m)
{
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

	if (rook_pattern[7 - (m.src_y - m.dst_y)][7 - (m.src_x - m.dst_x)])
		return !board_is_move_blocked(board, m);
	return false;
}
