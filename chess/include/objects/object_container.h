#pragma once
#include <memory.h>
#include "math.h"
#include "renderer.h"

#include "objects/texture.h"
#include "objects/button.h"
#include "objects/messagebox.h"
#include "objects/board.h"

#define INVALID_OBJECT 999999

typedef enum ObjectType {
	OBJECT_NONE,
	OBJECT_TEXTURE,
	OBJECT_BUTTON,
	OBJECT_MESSAGEBOX,
	OBJECT_CHESS
} ObjectType;

typedef union Objects {
	Texture* texture;
	Button* button;
	MessageBox* message_box;
	Chess* chess;
} Objects;

static unsigned int create_object();
static void destroy_object(unsigned int id);
bool reserve_object_memory(unsigned int count);
static unsigned int check_for_empty_space_in_object_container();
inline static bool check_validation_of_object(unsigned int id);
static void render_object(unsigned int id);
static void handle_object(unsigned int id);

void destroy_objects();
void render_objects();
void handle_objects();
Objects* get_object(unsigned int id);

unsigned int create_texture(TextureID id);
unsigned int create_button(const char* title, SDL_Rect position, void_func_ptr function);
unsigned int create_messagebox(const char* title, SDL_Rect pos);
unsigned int create_chess(SDL_Rect pos);





