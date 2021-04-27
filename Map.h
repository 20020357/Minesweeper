#pragma once
#include "Minesweeper.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

void Map (Minesweeper& test);
void refreshScreen (SDL_Window* window, SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect& mouse, Minesweeper& test, int& squares);
void youWin (SDL_Rect picture, SDL_Rect screen, Minesweeper test);
void youLose (SDL_Rect picture, SDL_Rect screen, Minesweeper test);
void showBomb (SDL_Rect picture, SDL_Rect screen, SDL_Renderer* renderer, SDL_Texture* texture, Minesweeper test);
