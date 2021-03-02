#define OLC_PGE_APPLICATION
#include "snake.h"

int main()
{
	srand(time(NULL));
	Game snake_game;
	if (snake_game.Construct(256, 128, 4, 4, false, true))
		snake_game.Start();

	return EXIT_SUCCESS;
}