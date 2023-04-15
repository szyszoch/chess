#include "objects/chess.h"

typedef struct Chess {
	SDL_Rect pos;
	ChessTeam turn;
	SDL_Point select;
	Board board;
	bool gameover;
	GameMode game_mode;
} Chess;



Chess* chess_create(const SDL_Rect* pos, GameMode gm)
{
	if (gm == GAMEMODE_NETWORK && !is_connected())
		return NULL;

	Chess* chess= malloc(sizeof(Chess));

	if (chess == NULL) {
		LOG_ERROR(SDL_LOG_CATEGORY_SYSTEM,"Can't allocate memory");
		return NULL;
	}

	board_restart(&chess->board);
	chess->turn = TEAM_WHITE;
	chess->gameover = false;
	memset(&chess->select, -1, sizeof(SDL_Point));
	chess->pos = *pos;
	chess->game_mode = gm;
	
	return chess;
}

void chess_destroy(Chess* chess)
{
	if (chess == NULL)
		return;
	free(chess);
}

void chess_render(Chess* chess)
{
	render(get_texture(TEXTURE_BOARD), NULL, &chess->pos);

	int chess_width = (chess->pos.w / 8);
	int chess_height = (chess->pos.h / 8);

	for (int x = 0; x < 8; x++) {
		for (int y = 0; y < 8; y++) {
			if (x == chess->select.x && y == chess->select.y)
				continue;
			if (chess->board.team[y][x] == TEAM_NONE || chess->board.type[y][x] == CHESS_NONE)
				continue;

			int tex_id = chess_get_texture_id(chess->board.type[y][x], chess->board.team[y][x]);
			SDL_Rect chess_pos = { x * chess_width, y * chess_height, chess_width, chess_height };
			render(get_texture(tex_id), NULL, &chess_pos);
		}
	}

	if (chess->select.x != -1 && chess->select.y != -1) {
		int mx, my;
		SDL_GetMouseState(&mx, &my);

		int x = chess->select.x;
		int y = chess->select.y;

		int tex_id = chess_get_texture_id(chess->board.type[y][x], chess->board.team[y][x]);

		SDL_Rect chess_pos = {mx - chess_width / 2, my - chess_height / 2, chess_width, chess_height };
		render(get_texture(tex_id), NULL, &chess_pos);
	}

}

void chess_handle(Chess* chess)
{
	Move move = chess_move_piece(chess);

	if (board_check_move_validation(move)) {
		if (board_can_move(&chess->board, move)) {
			board_move(&chess->board, move);
		
			if (chess->game_mode == GAMEMODE_NETWORK)
				chess_send_move_throught_network(move);
		
			chess->turn = (chess->turn == TEAM_WHITE) ? TEAM_BLACK : TEAM_WHITE;
			chess->gameover = board_is_gameover(&chess->board, chess->turn);
		}
	}

	else if (chess->game_mode == GAMEMODE_NETWORK) {
		move = chess_receive_move_from_network();
		if (board_check_move_validation(move)) {
			board_move(&chess->board, move);
			chess->turn = (chess->turn == TEAM_WHITE) ? TEAM_BLACK : TEAM_WHITE;
			chess->gameover = board_is_gameover(&chess->board, chess->turn);
		}
	}

}

ChessTeam chess_get_turn(Chess* chess)
{
	return chess->turn;
}

TextureID chess_get_texture_id(ChessType type, ChessTeam team)
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

	LOG_WARN(SDL_LOG_CATEGORY_APPLICATION,"Undefined chess type or team");
	return 0;
}

bool chess_is_gameover(Chess* chess)
{
	return chess->gameover;
}

static Move chess_move_piece(Chess* chess)
{
	Move move = { -1,-1,-1,-1 };

	if (!hover_rect(&chess->pos)) {
		memset(&chess->select, -1, sizeof(SDL_Point));
	}

	else if (released_left_button()) {

		if (chess->select.x != -1 && chess->select.y != -1) {
			int x = 0;
			int y = 0;
			SDL_GetMouseState(&x, &y);

			x = (x - chess->pos.x) / (chess->pos.w / 8);
			y = (y - chess->pos.y) / (chess->pos.h / 8);

			if (x < 0 || x > 7 || y < 0 || y > 7) {
				chess->select.x = -1;
				chess->select.y = -1;
				return move;
			}

			else if (chess->game_mode == GAMEMODE_LOCAL || chess_team_of_player_on_network_mode(chess) == chess->turn) {
				move.src_x = chess->select.x;
				move.src_y = chess->select.y;
				move.dst_x = x;
				move.dst_y = y;
			}
			
			memset(&chess->select, -1, sizeof(SDL_Point));
		}

	}

	else if (pressed_left_button()) {
		int x = 0;
		int y = 0;
		SDL_GetMouseState(&x, &y);

		x = (x - chess->pos.x) / (chess->pos.w / 8);
		y = (y - chess->pos.y) / (chess->pos.h / 8);

		if (!(x < 0 || x > 7 || y < 0 || y > 7)) {
			if (chess->game_mode == GAMEMODE_LOCAL) {
				if (chess->board.team[y][x] == chess->turn) {
					chess->select.x = x;
					chess->select.y = y;
				}
			}

			else {
				if (chess->board.team[y][x] == chess_team_of_player_on_network_mode(chess)) {
					chess->select.x = x;
					chess->select.y = y;
				}
			}
		}
	}

	return move;
}

static ChessTeam chess_team_of_player_on_network_mode(Chess* chess)
{
	return (get_host_type() == HOST_CLIENT ? TEAM_BLACK : TEAM_WHITE);
}

static void chess_send_move_throught_network(Move move)
{
	char msg[] = { move.src_x,move.src_y,move.dst_x,move.dst_y,'\0' };
	send_message(msg, 5);
}

static Move chess_receive_move_from_network()
{
	Move move = { -1,-1,-1,-1 };
	char buff[DEFAULT_BUFLEN];
	if (receive_message(buff, DEFAULT_BUFLEN)) {
		move.src_x = buff[0];
		move.src_y = buff[1];
		move.dst_x = buff[2];
		move.dst_y = buff[3];
	}
	return move;
}