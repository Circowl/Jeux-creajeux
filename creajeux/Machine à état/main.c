#include "All.h"






int _tmain(int argc, _TCHAR* argv[])
{


	sfVideoMode mode = { 1280, 900, 32 };
	

	struct GAMEDATA gameData = {0 , 0, 0, 500, Running};

	gameData.window = sfRenderWindow_create(mode, "SFML window", sfResize | sfClose, NULL);

	while (sfRenderWindow_isOpen(gameData.window))
	{
		if (gameData.phase == Running)
		{
			RunningState(&gameData);
		}
		if (gameData.phase == Jumping)
		{
			JumpingState(&gameData);
		}
		if (gameData.phase == Falling)
		{
			FallingState(&gameData);
		}
	}

	return 0;
}
