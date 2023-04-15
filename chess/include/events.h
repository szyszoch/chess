#pragma once
#include <SDL.h>
#include <stdbool.h>

void update();
bool pressed_key(SDL_Scancode code);
bool pressed_quit();
bool hover_rect(const SDL_Rect* rect);
bool clicked_rect(const SDL_Rect* rect);
void center_to_cursor(SDL_Rect* rect);
void center_x_to_rect(int* x, const SDL_Rect* rect);
void center_y_to_rect(int* y, const SDL_Rect* rect);
void center_rect_to_rect_x(SDL_Rect* src, const SDL_Rect* dst);
void center_rect_to_rect_y(SDL_Rect* src, const SDL_Rect* dst);
void center_rect_to_rect(SDL_Rect* src, const SDL_Rect* dst);
void change_rect_dim(SDL_Rect* rect, int w, int h);
void change_rect_pos(SDL_Rect* rect, int x, int y);
void get_mouse_pos(int* x, int* y);
bool pressed_left_button();
bool released_left_button();