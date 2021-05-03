#include <iostream>
#include "Map.h"

void game (bool &replay)
{
    Minesweeper test;
    test.options();
	test.creating_map();
	test.processing_bomb();
	Map(test, replay);
}

int main(int argc, char *argv[])
{
	bool replay = true;
    while (replay == true)
    {
        game(replay);
    }
	return 0;
}
