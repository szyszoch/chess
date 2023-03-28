#include "object.h"

typedef enum ObjectType {
	OBJECT_NONE,
	OBJECT_TEXTURE,
	OBJECT_BUTTON,
	OBJECT_MESSAGEBOX,
	OBJECT_CHESS
} ObjectType;

SDL_Renderer* renderer = NULL;
SDL_Window* window = NULL;
SDL_Event event_handler;

int error = 0;

typedef struct Texture {
	SDL_Texture* texture;
} Texture;

typedef struct Button {
	void_func_ptr func;
	SDL_Texture* texture[2];
	int button_state;
	int event_type;
} Button;

typedef struct MessageBox {
	unsigned int texture;
	unsigned int button;
} MessageBox;

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

typedef struct Chess {
	Board board;
	unsigned int texture[TEXTURE_COUNT];
} Chess;

typedef struct Object {
	int type;
	union object {
		Texture texture;
		Button button;
		MessageBox message_box;
		Chess chess;
	};
	SDL_Rect dst;
	bool hover;
	bool click;
	bool hide; 
	bool sub; // if object is member of another object
} Object;


Object* object = NULL;
unsigned int objectn = 0;

int InitRenderer() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		LOG_ERROR(SDL_GetError());
		error++;
		return -1;
	}

	if (IMG_Init(IMG_INIT_PNG) == 0) {
		LOG_ERROR(SDL_GetError());
		error++;
		return -2;
	}

	if (TTF_Init() == -1) {
		LOG_ERROR(SDL_GetError());
		error++;
		return -3;
	}

	window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

	if (window == NULL) {
		LOG_ERROR(SDL_GetError());
		error++;
		return -4;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (renderer == NULL) {
		LOG_ERROR(SDL_GetError());
		error++;
		return -5;
	}

	return 0;
}

void CleanRenderer() {
	for (unsigned int i = 0; i < objectn; i++) {
		DestroyObject(i);
	}
	free(object);
	object = NULL;
	objectn = 0;
}

void DestroyRenderer() {

	CleanRenderer();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void DestroyObject(unsigned int id) {

	if (id >= objectn)
		return;
	if (object[id].type != OBJECT_NONE) {
		
		switch (object[id].type) {
		case OBJECT_TEXTURE: {
			if (object[id].texture.texture != NULL)
				SDL_DestroyTexture(object[id].texture.texture);
			break;
		}
		case OBJECT_BUTTON: {
			if (object[id].button.texture[BUTTONSTATE_NORMAL] != NULL)
				SDL_DestroyTexture(object[id].button.texture[BUTTONSTATE_NORMAL]);
			if (object[id].button.texture[BUTTONSTATE_HOVER] != NULL)
				SDL_DestroyTexture(object[id].button.texture[BUTTONSTATE_HOVER]);
			object[id].button.func = NULL;
			object[id].button.event_type = 0;
			object[id].button.button_state = 0;
			break;
		}
		}

	}
	object[id].click = false;
	object[id].dst = (SDL_Rect){ 0,0,0,0 };
	object[id].type = OBJECT_NONE;
}

void ReserveObjectMemory(unsigned int num) {
	
	if (object == NULL) {
		object = calloc(num, sizeof(Object));
	}
	else {
		Object* new_object = realloc(object, objectn * sizeof(Object));
		if (new_object == NULL) {
			free(new_object);
			LOG_ERROR("Can't allocate memory");
			return;
		}
		object = new_object;

	}
	objectn = num;
}

void RenderObjects() {

	for (unsigned int i = 0; i < objectn; i++) {

		if (object[i].sub == true)
			continue;
		
		if (object[i].hide == true)
			continue;

		RenderObject(i);

	}

}

void RenderObject(unsigned int id) {

	if (id >= objectn)
		return;
	if (object[id].hide == true)
		return;

	switch (object[id].type) {
	case OBJECT_NONE: {
		break;
	}
	case OBJECT_TEXTURE: {
		SDL_RenderCopy(renderer, object[id].texture.texture, NULL, &object[id].dst);
		break;
	}
	case OBJECT_BUTTON: {
		SDL_RenderCopy(renderer, object[id].button.texture[object[id].button.button_state], NULL, &object[id].dst);
		break;
	}
	case OBJECT_MESSAGEBOX: {
		RenderObject(object[id].message_box.texture);
		RenderObject(object[id].message_box.button);
		break;
	}
	case OBJECT_CHESS: {
		SetObjectPositionAndDimensions(object[id].chess.texture[TEXTURE_BOARD], object[id].dst.x, object[id].dst.y, object[id].dst.w, object[id].dst.h);
		RenderObject(object[id].chess.texture[TEXTURE_BOARD]);

		int chess_width = (object[id].dst.w / 8);
		int chess_height = (object[id].dst.h / 8);

		for (int x = 0; x < 8; x++) {
			for (int y = 0; y < 8; y++) {

				if (object[id].chess.board.piece[x][y].team == TEAM_NONE || object[id].chess.board.piece[x][y].chess_type == CHESS_NONE)
					continue;

				int tex_id = 0;

				switch (object[id].chess.board.piece[x][y].team) {
				case TEAM_WHITE: {
					switch (object[id].chess.board.piece[x][y].chess_type) {
					case CHESS_BISHOP: {tex_id = TEXTURE_WHITE_BISHOP; break; }
					case CHESS_KING: {tex_id = TEXTURE_WHITE_KING; break; }
					case CHESS_KNIGHT: {tex_id = TEXTURE_WHITE_KNIGHT; break; }
					case CHESS_PAWN: {tex_id = TEXTURE_WHITE_PAWN; break; }
					case CHESS_QUEEN: {tex_id = TEXTURE_WHITE_QUEEN; break; }
					case CHESS_ROOK: {tex_id = TEXTURE_WHITE_ROOK; break; }
					}
					break;
				}
				case TEAM_BLACK: {
					switch (object[id].chess.board.piece[x][y].chess_type) {
					case CHESS_BISHOP: {tex_id = TEXTURE_BLACK_BISHOP; break; }
					case CHESS_KING: {tex_id = TEXTURE_BLACK_KING; break; }
					case CHESS_KNIGHT: {tex_id = TEXTURE_BLACK_KNIGHT; break; }
					case CHESS_PAWN: {tex_id = TEXTURE_BLACK_PAWN; break; }
					case CHESS_QUEEN: {tex_id = TEXTURE_BLACK_QUEEN; break; }
					case CHESS_ROOK: {tex_id = TEXTURE_BLACK_ROOK; break; }
					}
					break;
				}
				}

				if (x != object[id].chess.board.select_x || y != object[id].chess.board.select_y) {
					SetObjectPositionAndDimensions(object[id].chess.texture[tex_id], x * chess_width, y * chess_height, chess_width, chess_height);
					RenderObject(object[id].chess.texture[tex_id]);
				}

			}
		}

		if (object[id].chess.board.select_x != -1 && object[id].chess.board.select_y != -1) {
			int mx, my;
			SDL_GetMouseState(&mx, &my);

			int tex_id = 0;
			int x = object[id].chess.board.select_x;
			int y = object[id].chess.board.select_y;

			switch (object[id].chess.board.piece[x][y].team) {
			case TEAM_WHITE: {
				switch (object[id].chess.board.piece[x][y].chess_type) {
				case CHESS_BISHOP: {tex_id = TEXTURE_WHITE_BISHOP; break; }
				case CHESS_KING: {tex_id = TEXTURE_WHITE_KING; break; }
				case CHESS_KNIGHT: {tex_id = TEXTURE_WHITE_KNIGHT; break; }
				case CHESS_PAWN: {tex_id = TEXTURE_WHITE_PAWN; break; }
				case CHESS_QUEEN: {tex_id = TEXTURE_WHITE_QUEEN; break; }
				case CHESS_ROOK: {tex_id = TEXTURE_WHITE_ROOK; break; }
				}
				break;
			}
			case TEAM_BLACK: {
				switch (object[id].chess.board.piece[x][y].chess_type) {
				case CHESS_BISHOP: {tex_id = TEXTURE_BLACK_BISHOP; break; }
				case CHESS_KING: {tex_id = TEXTURE_BLACK_KING; break; }
				case CHESS_KNIGHT: {tex_id = TEXTURE_BLACK_KNIGHT; break; }
				case CHESS_PAWN: {tex_id = TEXTURE_BLACK_PAWN; break; }
				case CHESS_QUEEN: {tex_id = TEXTURE_BLACK_QUEEN; break; }
				case CHESS_ROOK: {tex_id = TEXTURE_BLACK_ROOK; break; }
				}
				break;
			}
			}

			SetObjectPositionAndDimensions(object[id].chess.texture[tex_id], mx - chess_width / 2, my - chess_height / 2, chess_width, chess_height);
			RenderObject(object[id].chess.texture[tex_id]);
		}
		break;
	}
	}
}

void RenderObjectAt(unsigned int id, int x, int y, int w, int h) {
	if (id >= objectn)
		return;
	if (object[id].hide == true)
		return;

	SDL_Rect pos = { x,y,w,h };

	switch (object[id].type) {
	case OBJECT_NONE: {
		break;
	}
	case OBJECT_TEXTURE: {
		SDL_RenderCopy(renderer, object[id].texture.texture, NULL, &pos);
		break;
	}
	case OBJECT_BUTTON: {
		SDL_RenderCopy(renderer, object[id].button.texture[object[id].button.button_state], NULL, &pos);
		break;
	}
	}
}

unsigned int CreateObject() {

	unsigned int o_id = INVALID_OBJECT;

	for(unsigned int i=0; i < objectn; i++)
		if (object[i].type == OBJECT_NONE) {
			o_id = i;
			break;
		}
	if (o_id == INVALID_OBJECT) {
		o_id = objectn;
		objectn++;
		ReserveObjectMemory(objectn);
	}
	return o_id;
}

void SetObjectPosition(unsigned int id, int x, int y) {
	if (id >= objectn)
		return;

	if (object[id].type == OBJECT_MESSAGEBOX) {
		object[id].dst.x = x;
		object[id].dst.y = y;
		object[object[id].message_box.texture].dst.x = x;
		object[object[id].message_box.texture].dst.y = y;
		object[object[id].message_box.button].dst.x = x + object[id].dst.w / 2 - object[id].dst.w / 4;
		object[object[id].message_box.button].dst.y = y + object[id].dst.h / 2;
	}

	else {
		object[id].dst.x = x;
		object[id].dst.y = y;
	}

	
}

void SetObjectPositionAndDimensions(unsigned int id, int x, int y, int w, int h) {
	if (id >= objectn)
		return;

	if (object[id].type == OBJECT_MESSAGEBOX) {
		object[id].dst.x = x;
		object[id].dst.y = y;
		object[id].dst.h = h;
		object[id].dst.w = w;
		object[object[id].message_box.texture].dst.x = x;
		object[object[id].message_box.texture].dst.y = y;
		object[object[id].message_box.texture].dst.w = w;
		object[object[id].message_box.texture].dst.h = h;
		object[object[id].message_box.button].dst.x = x + w/2 - w / 4;
		object[object[id].message_box.button].dst.y = y + h / 2;
		object[object[id].message_box.button].dst.w = w / 2;
		object[object[id].message_box.button].dst.h = h / 3;
	}

	else {
		object[id].dst.x = x;
		object[id].dst.y = y;
		object[id].dst.h = h;
		object[id].dst.w = w;
	}
	
}

unsigned int LoadTexture(const char* path) {
	
	SDL_Surface* surface = IMG_Load(path);

	if (surface == NULL) {
		LOG_ERROR(SDL_GetError());
		error++;
		return INVALID_OBJECT;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	if (texture == NULL) {
		LOG_ERROR(SDL_GetError());
		error++;
		return INVALID_OBJECT;
	}

	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
	SDL_SetTextureScaleMode(texture, SDL_ScaleModeLinear);

	unsigned int tex_id = CreateObject();

	object[tex_id].texture.texture = texture;
	object[tex_id].type = OBJECT_TEXTURE;
	SDL_QueryTexture(texture, NULL, NULL, &object[tex_id].dst.w, &object[tex_id].dst.h);

	return tex_id;

}

unsigned int CreateButton(const char* title, SDL_Rect position, Button_F* button_form, int event_type) {

	TTF_Font* font = TTF_OpenFont(button_form->font_path, button_form->font_size);

	if (font == NULL) {
		LOG_ERROR(SDL_GetError());
		error++;
		return INVALID_OBJECT;
	}

	SDL_Surface* text = TTF_RenderText_Solid(font, title, button_form->text_color);
	TTF_CloseFont(font);

	if (text == NULL) {
		LOG_ERROR(SDL_GetError());
		error++;
		return INVALID_OBJECT;
	}

	SDL_Surface* normal_sprite = SDL_CreateRGBSurface(0, position.w, position.h, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);

	if (normal_sprite == NULL) {
		LOG_ERROR(SDL_GetError());
		SDL_FreeSurface(text);
		error++;
		return INVALID_OBJECT;
	}

	SDL_Surface* hover_sprite = SDL_CreateRGBSurface(0, position.w, position.h, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);

	if (hover_sprite == NULL) {
		LOG_ERROR(SDL_GetError());
		SDL_FreeSurface(text);
		SDL_FreeSurface(normal_sprite);
		error++;
		return INVALID_OBJECT;
	}

	Uint32 normal_sprite_color = (button_form->background_color.r << 24) | (button_form->background_color.g << 16) | (button_form->background_color.b << 8) | (button_form->background_color.a);
	Uint32 hover_sprite_color = (button_form->background_color_hover.r << 24) | (button_form->background_color_hover.g << 16) | (button_form->background_color_hover.b << 8) | (button_form->background_color_hover.a);

	SDL_FillRect(normal_sprite, NULL, normal_sprite_color);
	SDL_FillRect(hover_sprite, NULL, hover_sprite_color);

	SDL_Rect center_text = { position.w / 2 - text->w / 2, position.h / 2 - text->h / 2,text->w,text->h };

	SDL_BlitSurface(text, NULL, normal_sprite, &center_text);
	SDL_BlitSurface(text, NULL, hover_sprite, &center_text);

	unsigned int b_id = CreateObject();

	object[b_id].button.texture[BUTTONSTATE_NORMAL] = SDL_CreateTextureFromSurface(renderer, normal_sprite);
	object[b_id].button.texture[BUTTONSTATE_HOVER] = SDL_CreateTextureFromSurface(renderer, hover_sprite);

	SDL_FreeSurface(normal_sprite);
	SDL_FreeSurface(hover_sprite);
	SDL_FreeSurface(text);

	if (object[b_id].button.texture[BUTTONSTATE_NORMAL] == NULL || object[b_id].button.texture[BUTTONSTATE_HOVER] == NULL) {
		LOG_ERROR(SDL_GetError());
		DestroyObject(b_id);
		error++;
		return INVALID_OBJECT;
	}

	object[b_id].type = OBJECT_BUTTON;
	object[b_id].dst = position;
	object[b_id].button.button_state = BUTTONSTATE_NORMAL;
	object[b_id].button.event_type = event_type;

	return b_id;
}

unsigned int CreateText(const char* title, Text_F* text_form) {
	
	TTF_Font* font = TTF_OpenFont(text_form->font_path, text_form->size);

	if (font == NULL) {
		LOG_ERROR(SDL_GetError());
		return INVALID_OBJECT;
	}

	SDL_Surface* surface = TTF_RenderText_Solid(font, title, text_form->color);
	TTF_CloseFont(font);

	if (surface == NULL) {
		LOG_ERROR(SDL_GetError());
		return INVALID_OBJECT;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	if (texture == NULL) {
		LOG_ERROR(SDL_GetError());
		return INVALID_OBJECT;
	}

	unsigned int tex_id = CreateObject();

	object[tex_id].texture.texture = texture;
	SDL_QueryTexture(object[tex_id].texture.texture, NULL, NULL, &object[tex_id].dst.w, &object[tex_id].dst.h);
	object[tex_id].type = OBJECT_TEXTURE;

	return tex_id;

}

unsigned int CreateRect(Uint32 color, int width, int height) {

	SDL_Surface* surface = SDL_CreateRGBSurface(0, width, height, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);

	if (surface == NULL) {
		LOG_ERROR(SDL_GetError());
		return INVALID_OBJECT;
	}

	SDL_FillRect(surface, NULL, color);

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	if (texture == NULL) {
		LOG_ERROR(SDL_GetError());
		return INVALID_OBJECT;
	}

	unsigned int tex_id = CreateObject();
	
	object[tex_id].texture.texture = texture;
	object[tex_id].dst.w = width;
	object[tex_id].dst.h = height;
	object[tex_id].type = OBJECT_TEXTURE;

	return tex_id;
}

void MergeTextures(unsigned int src, SDL_Rect pos, unsigned int dst) {
	if (src >= objectn || dst >= objectn)
		return;

	SDL_SetRenderTarget(renderer, object[dst].texture.texture);
	SDL_RenderCopy(renderer, object[src].texture.texture, NULL, &pos);
	SDL_SetRenderTarget(renderer, NULL);

}

void SetButtonEvent(unsigned int id, void_func_ptr function) {
	if (id >= objectn)
		return;
	if (object[id].type != OBJECT_BUTTON)
		return;
	object[id].button.event_type = BUTTONEVENT_FUNC;
	object[id].button.func = function;
}

void HandleObjectEvent(unsigned int id) {
	
	if (id >= objectn)
		return;

	int x = 0;
	int y = 0;
	SDL_GetMouseState(&x, &y);
	SDL_Rect point = { x,y,1,1 };

	object[id].hover = SDL_HasIntersection(&object[id].dst, &point);
	object[id].click = object[id].hover && event_handler.button.button == SDL_BUTTON_LEFT && event_handler.type == SDL_MOUSEBUTTONDOWN;

	switch (object[id].type) {
	case OBJECT_NONE: {
		break;
	}
	case OBJECT_TEXTURE: {
		break;
	}
	case OBJECT_BUTTON: {
		object[id].button.button_state = (object[id].hover) ? BUTTONSTATE_HOVER : BUTTONSTATE_NORMAL;
		if (object[id].button.event_type == BUTTONEVENT_FUNC && object[id].click)
			object[id].button.func();
		break;
	}
	case OBJECT_MESSAGEBOX: {
		if (object[id].hover && event_handler.button.button == SDL_BUTTON_LEFT && event_handler.type == SDL_MOUSEMOTION) {
			SetObjectPosition(id,x-object[id].dst.w/2,y - object[id].dst.h / 4);
		}

		HandleObjectEvent(object[id].message_box.texture);
		HandleObjectEvent(object[id].message_box.button);
		if (object[object[id].message_box.button].click == true) {
			DestroyObject(id);
		}
		break;
	}
	case OBJECT_CHESS: {
		if (object[id].chess.board.gameover == true) {
			return;
		}

		if (event_handler.button.button == SDL_BUTTON_LEFT) {

			if (object[id].hover == false) {
				object[id].chess.board.select_x = -1;
				object[id].chess.board.select_y = -1;
				return;
			}

			if (event_handler.type == SDL_MOUSEBUTTONUP) {

				if (object[id].chess.board.select_x != -1 && object[id].chess.board.select_y != -1) {
					int x = 0;
					int y = 0;
					SDL_GetMouseState(&x, &y);

					x = (x - object[id].dst.x) / (object[id].dst.w / 8);
					y = (y - object[id].dst.y) / (object[id].dst.h / 8);

					if (x < 0 || x > 7 || y < 0 || y > 7) {
						object[id].chess.board.select_x = -1;
						object[id].chess.board.select_y = -1;
						return;
					}
					object[id].chess.board.last_move.src_x = object[id].chess.board.select_x;
					object[id].chess.board.last_move.src_y = object[id].chess.board.select_y;
					object[id].chess.board.last_move.dst_x = x;
					object[id].chess.board.last_move.dst_y = y;

					object[id].chess.board.select_x = -1;
					object[id].chess.board.select_y = -1;
				}

			}

			if (event_handler.type == SDL_MOUSEBUTTONDOWN) {
				int x = 0;
				int y = 0;
				SDL_GetMouseState(&x, &y);

				x = (x - object[id].dst.x) / (object[id].dst.w / 8);
				y = (y - object[id].dst.y) / (object[id].dst.h / 8);

				if (x < 0 || x > 7 || y < 0 || y > 7) {
					return;
				}

				if (object[id].chess.board.piece[x][y].team == object[id].chess.board.turn) {
					object[id].chess.board.select_x = x;
					object[id].chess.board.select_y = y;
					return;
				}
			}
		}

		break;
	}

	}
}

void HandleObjectsEvent() {

	for (unsigned int i = 0; i < objectn; i++) {

		HandleObjectEvent(i);

	}

}

unsigned int CreateMessageBox(const char* title, SDL_Rect pos, Button_F* button_form, Text_F* text_form) {

	unsigned int texture_id = 0;
	unsigned int button_id = 0;

	{ // texture
		Uint32 white = 0xFFFFFFFF;
		Uint32 black = 0x222222AA;

		SDL_Surface* background = SDL_CreateRGBSurface(0, pos.w-6, pos.h-6, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);

		if (background == NULL) {
			LOG_ERROR(SDL_GetError());
			error++;
			return INVALID_OBJECT;
		}

		SDL_Surface* border = SDL_CreateRGBSurface(0, pos.w, pos.h, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);

		if (border == NULL) {
			LOG_ERROR(SDL_GetError());
			SDL_FreeSurface(background);
			error++;
			return INVALID_OBJECT;
		}

		SDL_FillRect(background, NULL, white);
		SDL_FillRect(border, NULL, black);

		SDL_Rect background_pos = {3, 3, pos.w, pos.h};
		SDL_BlitSurface(background, NULL, border, &background_pos);
		SDL_FreeSurface(background);
		background = border;

		TTF_Font* font = TTF_OpenFont(text_form->font_path, text_form->size);

		if (font == NULL) {
			LOG_ERROR(SDL_GetError());
			error++;
			return INVALID_OBJECT;
		}

		SDL_Surface* text = TTF_RenderText_Solid(font, title, text_form->color);
		TTF_CloseFont(font);

		if (text == NULL) {
			LOG_ERROR(SDL_GetError());
			SDL_FreeSurface(background);
			error++;
			return INVALID_OBJECT;
		}

		SDL_Rect text_pos = {pos.w/2 - text->w/2, 10, text->w, text->h};
		
		SDL_BlitSurface(text, NULL, background, &text_pos);
		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, background);
		SDL_FreeSurface(background);
		SDL_FreeSurface(text);

		if (texture == NULL) {
			LOG_ERROR(SDL_GetError());
			SDL_DestroyTexture(texture);
			error++;
			return INVALID_OBJECT;
		}

		texture_id = CreateObject();
		object[texture_id].texture.texture = texture;
		object[texture_id].type = OBJECT_TEXTURE;
	}

	{ // button
		SDL_Rect button_pos = { pos.x + pos.w / 2 - pos.w / 4,pos.h / 2 - (pos.h / 3),pos.w / 2,pos.h / 3 };

		button_id = CreateButton("Ok", button_pos, button_form, BUTTONEVENT_BOOL);

		if (button_id == INVALID_OBJECT) {
			DestroyObject(texture_id);
			error++;
			return INVALID_OBJECT;
		}
	}

	unsigned int m_id = CreateObject();
	object[m_id].message_box.texture = texture_id;
	object[m_id].message_box.button = button_id;
	object[m_id].type = OBJECT_MESSAGEBOX;
	SetObjectPositionAndDimensions(m_id, pos.x, pos.y, pos.w, pos.h);

	object[texture_id].sub = true;
	object[button_id].sub = true;

	return m_id;

}

int ErrorCount() {
	return error;
}

void HideObject(unsigned int id) {
	object[id].hide = true;
}

unsigned int CreateChess(SDL_Rect pos) {

	unsigned int tex_id[TEXTURE_COUNT] = { 0 };

	tex_id[TEXTURE_BOARD] = LoadTexture("img/board.png");
	tex_id[TEXTURE_BLACK_BISHOP] = LoadTexture("img/black_bishop.png");
	tex_id[TEXTURE_BLACK_KING] = LoadTexture("img/black_king.png");
	tex_id[TEXTURE_BLACK_KNIGHT] = LoadTexture("img/black_knight.png");
	tex_id[TEXTURE_BLACK_PAWN] = LoadTexture("img/black_pawn.png");
	tex_id[TEXTURE_BLACK_QUEEN] = LoadTexture("img/black_queen.png");
	tex_id[TEXTURE_BLACK_ROOK] = LoadTexture("img/black_rook.png");
	tex_id[TEXTURE_WHITE_BISHOP] = LoadTexture("img/white_bishop.png");
	tex_id[TEXTURE_WHITE_KING] = LoadTexture("img/white_king.png");
	tex_id[TEXTURE_WHITE_KNIGHT] = LoadTexture("img/white_knight.png");
	tex_id[TEXTURE_WHITE_PAWN] = LoadTexture("img/white_pawn.png");
	tex_id[TEXTURE_WHITE_QUEEN] = LoadTexture("img/white_queen.png");
	tex_id[TEXTURE_WHITE_ROOK] = LoadTexture("img/white_rook.png");
		
	unsigned int o_id = CreateObject();
	object[o_id].type = OBJECT_CHESS;
	Board_Restart(&object[o_id].chess.board);
	SetObjectPositionAndDimensions(o_id,pos.x,pos.y,pos.w,pos.h);
	
	for (int i = 0; i < TEXTURE_COUNT; i++) {
		object[o_id].chess.texture[i] = tex_id[i];
		object[object[o_id].chess.texture[i]].sub = true;

	}
		
	return o_id;
}

Board* GetChessBoard(unsigned int id) {
	if (id >= objectn)
		return NULL;
	if (object[id].type != OBJECT_CHESS)
		return NULL;
	return &object[id].chess.board;
}