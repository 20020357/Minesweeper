#include <iostream>
#include "Map.h"
#include "Minesweeper.h"


int main(int argc, char *argv[])
{
/*
    cout << "Nhap vao che do ban chon: (Width x Height x Bomb)"
         << "1. Easy: 9 x 9 x 10"
         << "2. Normal: 16 x 16 x 40"
         << "3. Hard: 30 x 16 x 99";
    int n;      cin >> n;
    int width = 0, height = 0, bomb = 0;
    switch(n)
    {
        case 1: width = height = 9, bomb = 10;
        case 2: width = height = 16, bomb = 40;
        case 3: width = 30, height = 16, bomb = 99;
    }
*/
    bool aLive = true;
	Minesweeper test;
	test.creating_map();
	test.processing_bomb();
	Map(test);
	return 0;
}
