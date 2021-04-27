#include "Minesweeper.h"

void Minesweeper:: creating_map ()
{
	display.resize(width);
	data.resize(width);
	button.resize(width);
	for (int i = 0; i < width; i++)
	{
		display[i].resize(height);
		data[i].resize(height);
		button[i].resize(height);
		for (int j = 0; j < height; j++)
		{
			display[i][j] = '*';
			data[i][j] = 0;
			button[i][j] = 1;
		}
	}
}
void Minesweeper:: processing_bomb ()
{
	// Creating Bomb !
	srand(07032002);

	int x = 0, y = 0;
	for (int i = 0; i < mines; i++)
	{
		do
		{
			x = rand() % width;
			y = rand() % height;
		}
		while (data[x][y] == BOMB);
		data[x][y] = BOMB;
	}

	// Counting bomb around area have coordinate (i, j) !
	for (int i = 0; i < width; i++)
		for (int j = 0; j < height; j++)
			if (data[i][j] != BOMB)
				for (int a = i-1; a <= i+1; a++)
					if (0 <= a && a < width)
						for (int b = j-1; b <= j+1; b++)
							if (0 <= b && b < height && data[a][b] == BOMB) data[i][j]++;
}
void Minesweeper:: open (int x, int y, int& squares, bool& aLive, SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect& picture, SDL_Rect& screen)
{
	if (data[x][y] == BOMB)
	{
		display[x][y] = 'X';

		picture.x = data[x][y]*32; picture.y = 0; picture.h = 32; picture.w = 32;
		screen.x = x*50; screen.y = y*50; screen.h = 50; screen.w = 50;
		print(renderer, texture, picture, screen);

		aLive = false;
	}
	else extend (x, y, squares, renderer, texture, picture, screen);
}
void Minesweeper:: extend (int x, int y, int& squares, SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect& picture, SDL_Rect& screen)
{
	if (data[x][y] != 0)
	{
		display[x][y] = data[x][y] + 48;
		if (button[x][y] == 1) countSquares(squares);
		button[x][y] = 0;

		picture.x = data[x][y]*32; picture.y = 0; picture.h = 32; picture.w = 32;
		screen.x = x*50; screen.y = y*50; screen.h = 50; screen.w = 50;
		print(renderer, texture, picture, screen);

		return;
	}
	else
	{
		display[x][y] = ' ';
		if (button[x][y] == 1) countSquares(squares);
		button[x][y] = 0;

		picture.x = data[x][y]*32; picture.y = 0; picture.h = 32; picture.w = 32;
		screen.x = x*50; screen.y = y*50; screen.h = 50; screen.w = 50;
		print(renderer, texture, picture, screen);

		for (int i = -1; i < 2; i++)
			if (0 <= x+i && x+i < width)
				for (int j = -1; j < 2; j++)
					if (0 <= j+y && j+y < height)
						if (display[x+i][y+j] == '*') extend(x+i, y+j, squares, renderer, texture, picture, screen);

	}
}
void Minesweeper:: print (SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect& picture, SDL_Rect& screen)
{
	SDL_RenderCopy(renderer, texture, &picture, &screen);
    SDL_RenderPresent(renderer);
}
int Minesweeper:: countSquares (int& squares)
{
    squares--;
    return squares;
}
void Minesweeper:: output ()
{
    for (int i = 0; i < width; i++)
    {
        for (int j = 0;j < height; j++)
            cout << display[i][j] << " ";
        cout << endl;
    }
}

