#pragma once
#include <bits/stdc++.h>
#include <SDL.h>
#define BOMB 9
#define width 9     // Cac truong hop khac: 16 | 30
#define height 9    // Cac truong hop khac: 16 | 16
#define mines 10    // Cac truong hop khac: 40 | 99
using namespace std;

struct Minesweeper
{
	vector <vector<char>> display;
	vector <vector<int>> data;
	vector<vector<int>> button;
	void creating_map ();
	void processing_bomb ();
	void open (int x, int y, int& squares, bool& aLive, SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect& picture, SDL_Rect& screen);
	void extend (int x, int y, int& squares, SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect& picture, SDL_Rect& screen);
	void print (SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect& picture, SDL_Rect& screen);
	int countSquares (int& squares);
	void output ();
};
