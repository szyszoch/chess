#pragma once
#include "objects/object.h"
#include "objects/button.h"
#include "objects/texture.h"

typedef struct MessageBox MessageBox;

MessageBox* mb_create(const char* title, SDL_Rect pos);
void mb_destroy(MessageBox* mb);
void mb_render(MessageBox* mb);
void mb_handle(MessageBox* mb);