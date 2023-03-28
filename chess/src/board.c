#include "board.h"

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



void Board_ChangeTurn(Board* board) {
	board->turn = (board->turn == TEAM_WHITE) ? TEAM_BLACK : TEAM_WHITE;
}

bool Board_KingCannotMove(Board* board, ChessTeam team) {

	int king_pos_x = 0;
	int king_pos_y = 0;

	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			if (board->piece[x][y].chess_type == CHESS_KING && board->piece[x][y].team == team) {
				king_pos_x = x;
				king_pos_y = y;
				break;
			}
		}
	}

	bool88 king_danger_zone;
	Board_GetKingDangerZone(board, team, king_danger_zone);


	if (king_pos_x > 0 && king_pos_y > 0)
		if (Board_CanMove(board, (Move) { king_pos_x, king_pos_y, king_pos_x - 1, king_pos_y - 1 }) && king_danger_zone[king_pos_x - 1][king_pos_y - 1] == false)
			return false;
	if (king_pos_x > 0)
		if (Board_CanMove(board, (Move) {king_pos_x, king_pos_y, king_pos_x - 1, king_pos_y    }) && king_danger_zone[king_pos_x - 1][king_pos_y    ] == false)
			return false;
	if (king_pos_x > 0 && king_pos_y < 7)
		if (Board_CanMove(board, (Move) {king_pos_x, king_pos_y, king_pos_x - 1, king_pos_y + 1}) && king_danger_zone[king_pos_x - 1][king_pos_y + 1] == false)
			return false;
	if (king_pos_x < 7 && king_pos_y > 0)
		if (Board_CanMove(board, (Move) {king_pos_x, king_pos_y, king_pos_x + 1, king_pos_y - 1}) && king_danger_zone[king_pos_x + 1][king_pos_y - 1] == false)
			return false;
	if (king_pos_x < 7)
		if (Board_CanMove(board, (Move) {king_pos_x, king_pos_y, king_pos_x + 1, king_pos_y    }) && king_danger_zone[king_pos_x + 1][king_pos_y    ] == false)
			return false;
	if (king_pos_x < 7 && king_pos_y < 7)
		if (Board_CanMove(board, (Move) {king_pos_x, king_pos_y, king_pos_x + 1, king_pos_y + 1}) && king_danger_zone[king_pos_x + 1][king_pos_y + 1] == false)
			return false;
	if (king_pos_y < 7)
		if (Board_CanMove(board, (Move) {king_pos_x, king_pos_y, king_pos_x    , king_pos_y + 1}) && king_danger_zone[king_pos_x    ][king_pos_y + 1] == false)
			return false;
	if (king_pos_y > 0)
		if (Board_CanMove(board, (Move) {king_pos_x, king_pos_y, king_pos_x    , king_pos_y - 1}) && king_danger_zone[king_pos_x    ][king_pos_y - 1] == false)
			return false;

	return true;

}

bool Board_CanProtectKing(Board* board, Move move, ChessTeam team) {

	if (board->piece[move.src_x][move.src_y].team != team) {
		return false;
	}

	Board test_board;
	Board_Copy(board, &test_board);
	
	if (!Board_CanMove(&test_board, move)) {
		return false;
	}

	Board_Move(&test_board, move);
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
	board_data->last_move = (Move){ -1,-1,-1,-1 };

	board_data->piece[0][0].chess_type = CHESS_ROOK;		board_data->piece[0][0].team = TEAM_BLACK;
	board_data->piece[1][0].chess_type = CHESS_KNIGHT;	board_data->piece[1][0].team = TEAM_BLACK;
	board_data->piece[2][0].chess_type = CHESS_BISHOP;	board_data->piece[2][0].team = TEAM_BLACK;
	board_data->piece[3][0].chess_type = CHESS_QUEEN;		board_data->piece[3][0].team = TEAM_BLACK;
	board_data->piece[4][0].chess_type = CHESS_KING;		board_data->piece[4][0].team = TEAM_BLACK;
	board_data->piece[5][0].chess_type = CHESS_BISHOP;	board_data->piece[5][0].team = TEAM_BLACK;
	board_data->piece[6][0].chess_type = CHESS_KNIGHT;	board_data->piece[6][0].team = TEAM_BLACK;
	board_data->piece[7][0].chess_type = CHESS_ROOK;		board_data->piece[7][0].team = TEAM_BLACK;

	board_data->piece[0][1].chess_type = CHESS_PAWN;   board_data->piece[0][1].team = TEAM_BLACK;
	board_data->piece[1][1].chess_type = CHESS_PAWN;   board_data->piece[1][1].team = TEAM_BLACK;
	board_data->piece[2][1].chess_type = CHESS_PAWN;   board_data->piece[2][1].team = TEAM_BLACK;
	board_data->piece[3][1].chess_type = CHESS_PAWN;   board_data->piece[3][1].team = TEAM_BLACK;
	board_data->piece[4][1].chess_type = CHESS_PAWN;   board_data->piece[4][1].team = TEAM_BLACK;
	board_data->piece[5][1].chess_type = CHESS_PAWN;   board_data->piece[5][1].team = TEAM_BLACK;
	board_data->piece[6][1].chess_type = CHESS_PAWN;   board_data->piece[6][1].team = TEAM_BLACK;
	board_data->piece[7][1].chess_type = CHESS_PAWN;   board_data->piece[7][1].team = TEAM_BLACK;
										    
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
										    
	board_data->piece[0][6].chess_type = CHESS_PAWN;  board_data->piece[0][6].team = TEAM_WHITE;
	board_data->piece[1][6].chess_type = CHESS_PAWN;  board_data->piece[1][6].team = TEAM_WHITE;
	board_data->piece[2][6].chess_type = CHESS_PAWN;  board_data->piece[2][6].team = TEAM_WHITE;
	board_data->piece[3][6].chess_type = CHESS_PAWN;  board_data->piece[3][6].team = TEAM_WHITE;
	board_data->piece[4][6].chess_type = CHESS_PAWN;  board_data->piece[4][6].team = TEAM_WHITE;
	board_data->piece[5][6].chess_type = CHESS_PAWN;  board_data->piece[5][6].team = TEAM_WHITE;
	board_data->piece[6][6].chess_type = CHESS_PAWN;  board_data->piece[6][6].team = TEAM_WHITE;
	board_data->piece[7][6].chess_type = CHESS_PAWN;  board_data->piece[7][6].team = TEAM_WHITE;

	board_data->piece[0][7].chess_type = CHESS_ROOK;		board_data->piece[0][7].team = TEAM_WHITE;
	board_data->piece[1][7].chess_type = CHESS_KNIGHT;	board_data->piece[1][7].team = TEAM_WHITE;
	board_data->piece[2][7].chess_type = CHESS_BISHOP;	board_data->piece[2][7].team = TEAM_WHITE;
	board_data->piece[3][7].chess_type = CHESS_QUEEN;		board_data->piece[3][7].team = TEAM_WHITE;
	board_data->piece[4][7].chess_type = CHESS_KING;		board_data->piece[4][7].team = TEAM_WHITE;
	board_data->piece[5][7].chess_type = CHESS_BISHOP;	board_data->piece[5][7].team = TEAM_WHITE;
	board_data->piece[6][7].chess_type = CHESS_KNIGHT;	board_data->piece[6][7].team = TEAM_WHITE;
	board_data->piece[7][7].chess_type = CHESS_ROOK;		board_data->piece[7][7].team = TEAM_WHITE;

}

void Board_Move(Board* board, Move move) {

	board->piece[move.dst_x][move.dst_y] = board->piece[move.src_x][move.src_y];
	board->piece[move.src_x][move.src_y].team = TEAM_NONE;
	board->piece[move.src_x][move.src_y].chess_type = CHESS_NONE;

	if (board->piece[move.dst_x][move.dst_y].chess_type == CHESS_PAWN) {
		if (board->piece[move.dst_x][move.dst_y].team == TEAM_WHITE && move.dst_y == 0) {
			board->piece[move.dst_x][move.dst_y].chess_type = CHESS_QUEEN;
		}
		else if (board->piece[move.dst_x][move.dst_y].team == TEAM_BLACK && move.dst_y == 7) {
			board->piece[move.dst_x][move.dst_y].chess_type = CHESS_QUEEN;
		}
	}

	board->last_move = (Move){ 0,0,0,0 };

}

bool Board_CanMove(Board* board, Move move) {

	if (move.src_x < 0 || move.src_x > 7 || move.src_y < 0 || move.src_y > 7)
		return false;
	if (move.dst_x < 0 || move.dst_x > 7 || move.dst_y < 0 || move.dst_y > 7)
		return false;

	if (move.src_x == move.dst_x && move.src_y == move.dst_y)
		return false;
	else if (board->piece[move.dst_x][move.dst_y].team == board->piece[move.src_x][move.src_y].team)
		return false;
		
	if (board->piece[move.dst_x][move.dst_y].team > TEAM_NONE)
		return Board_Pattern(board,move,MOVE_CAPTURE);
	else 
		return Board_Pattern(board,move, MOVE_MOVE);
}

bool Board_IsKingInDanger(Board* board, ChessTeam team) {

	int king_pos_x=-1, king_pos_y=-1;

	for (int x = 0; x < 8; x++) {
		for (int y = 0; y < 8; y++) {
			if (board->piece[x][y].team == team) {
				if (board->piece[x][y].chess_type == CHESS_KING) {
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
			dst->piece[x][y].chess_type = src->piece[x][y].chess_type;
		}
	}

}

bool Board_Pattern(Board* board, Move move, MoveType move_type) {

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

bool Board_GameOver(Board* board, ChessTeam team) {

	if (Board_IsKingInDanger(board, team) == false)
		return false;

	if (Board_KingCannotMove(board, team) == false)
		return false;

	for (int srcx = 0; srcx < 8; srcx++) {
		for (int srcy = 0; srcy < 8; srcy++) {
			for (int dstx = 0; dstx < 8; dstx++) {
				for (int dsty = 0; dsty < 8; dsty++) {
					if (Board_CanProtectKing(board, (Move) { srcx, srcy, dstx, dsty }, team) == true) {
						return false;
					}
				}
			}
		}
	}

	return true;
}

