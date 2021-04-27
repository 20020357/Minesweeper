#include "Map.h"

void Map (Minesweeper& test)
{
    SDL_Window* window = SDL_CreateWindow("Minesweeper", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width*50, height*50, 0);
    SDL_Renderer* render =  SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Surface* load = IMG_Load("Minesweeper.bmp");
    SDL_Texture* texture = SDL_CreateTextureFromSurface(render, load);
    SDL_Rect picture; SDL_Rect screen;
    picture.x = 320; picture.y = 0; picture.w = 32; picture.h = 32;
    for (int i = 0; i < width; i++)
        for (int j = 0; j < height; j++)
        {
            screen.x = i*50; screen.y = j*50; screen.h = 50; screen.w = 50;
            test.print(render, texture, picture, screen);
        }

    SDL_Event e;
    SDL_Rect mouse;
    mouse.x = 400; mouse.y = 300;
    mouse.w = 16; mouse.h = 12;
    int count = mines, count_square = width*height;
    bool win = false;
    while (win == false)
    {
        SDL_Delay(10);
        if (SDL_WaitEvent(&e) == 0) continue;
        if (e.type == SDL_QUIT) break;
        if ((count == 1 && count_square <= 1) || (count == 0 && count_square <= 0))
        {
            SDL_DestroyWindow(window);
            count = 10;
            win = true;
        }
        if (e.type == SDL_MOUSEBUTTONDOWN)
        {
            mouse.x = e.button.x;
            mouse.y = e.button.y;
            if (e.button.button == SDL_BUTTON_LEFT)
            {
                refreshScreen(window, render, texture, mouse, test, count_square);
            }
            else if (e.button.button ==  SDL_BUTTON_RIGHT)
                {
                    picture.x = 352; picture.y = 0; picture.h = 32; picture.w = 32;
                    screen.x = (mouse.x/50)*50; screen.y = (mouse.y/50)*50; screen.h = 50; screen.w = 50;
                    SDL_RenderCopy(render, texture, &picture, &screen);
                    SDL_RenderPresent(render);

                    if (test.data[mouse.x/50][mouse.y/50] == BOMB)
                    {
                        count--;
                        if (test.button[mouse.x/50][mouse.y/50] == 1) test.countSquares(count_square);
                        test.button[mouse.x/50][mouse.y/50] = 0;
                    }
                }
        }
        cout << count_square << endl;
    }
    if (win == true)
    {
        SDL_Delay(1000);
        youWin(picture, screen, test);
    }
}
void refreshScreen (SDL_Window* window, SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect& mouse, Minesweeper& test, int& squares)
{
    bool aLive = true;
    SDL_Rect picture, screen;
    test.open(mouse.x/50, mouse.y/50, squares, aLive, renderer, texture, picture, screen);
    if (aLive == false)
        {
            showBomb(picture, screen, renderer, texture, test);
            SDL_DestroyWindow(window);
            youLose(picture, screen, test);
        }
}
void youWin (SDL_Rect picture, SDL_Rect screen, Minesweeper test)
{
    // show picture: You Win to screen
    SDL_Window* window_win = SDL_CreateWindow("Minesweeper", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 626, 417, 0);
    SDL_Renderer* renderer_win = SDL_CreateRenderer(window_win, -1, SDL_RENDERER_ACCELERATED);
    SDL_Surface* surface_win = IMG_Load("You Win.bmp");
    SDL_Texture* texture_win = SDL_CreateTextureFromSurface(renderer_win, surface_win);
    picture.x = 0; picture.y = 0; picture.h = 417; picture.w = 626;
    screen.x = 0; screen.y = 0; screen.h = 417; screen.w = 626;
    test.print(renderer_win, texture_win, picture, screen);
    SDL_Delay(1000);
    SDL_DestroyWindow(window_win);

    // show full map
    SDL_Window* newWindow = SDL_CreateWindow("Minesweeper", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width*50, height*50, 0);
    SDL_Renderer* newRenderer = SDL_CreateRenderer(newWindow, -1, SDL_RENDERER_ACCELERATED);
    SDL_Surface* newSurface = IMG_Load("Minesweeper.bmp");
    SDL_Texture* newTexture = SDL_CreateTextureFromSurface(newRenderer, newSurface);
    for (int i = 0; i < width; i++)
        for (int j = 0; j < height; j++)
        {
            picture.x = (test.data[i][j])*32; picture.y = 0; picture.h = 32; picture.w = 32;
            screen.x = i*50; screen.y = j*50; screen.h = 50; screen.w = 50;
            test.print(newRenderer, newTexture, picture, screen);
        }
    SDL_Event e;
    while (true)
    {
        SDL_Delay(10);
        if (SDL_WaitEvent(&e) == 0) continue;
        if (e.type == SDL_QUIT) break;
    }
}
void youLose (SDL_Rect picture, SDL_Rect screen, Minesweeper test)
{
    // show picture: You Lose to screen
    SDL_Window* window_lose = SDL_CreateWindow("Minesweeper", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 626, 391, 0);
    SDL_Renderer* renderer_lose = SDL_CreateRenderer(window_lose, -1, SDL_RENDERER_ACCELERATED);
    SDL_Surface* surface_lose = IMG_Load("You Lose.bmp");
    SDL_Texture* texture_lose = SDL_CreateTextureFromSurface(renderer_lose, surface_lose);
    picture.x = 0; picture.y = 0; picture.h = 391; picture.w = 626;
    screen.x = 0; screen.y = 0; screen.h = 391; screen.w = 626;
    test.print(renderer_lose, texture_lose, picture, screen);
    SDL_Delay(1000);
    SDL_DestroyWindow(window_lose);
}
void showBomb (SDL_Rect picture, SDL_Rect screen, SDL_Renderer* renderer, SDL_Texture* texture, Minesweeper test)
{
    for (int i = 0; i < width; i++)
        for (int j = 0; j < height; j++)
            if (test.data[i][j] == BOMB)
            {
                picture.x = 288; picture.y = 0; picture.h = 32; picture.w = 32;
                screen.x = i*50; screen.y = j*50; screen.h = 50; screen.w = 50;
                test.print(renderer, texture, picture, screen);
            }
    SDL_Delay(1000);
}

