#include "FallingState.h"

void FallingStateInit(struct GAMEDATA* gameData)
{
	gameData->Action = LoadSprite("falling.png", 1);
}
void FallingStateUpdate(struct GAMEDATA* gameData)
{
	sfEvent event;
	while (gameData->phase == Falling)
	{
		while (sfRenderWindow_pollEvent(gameData->window, &event))
		{
			if (event.type == sfEvtClosed) exit(0); //Fermeture en appuyant sur le bouton Fermer

			if (event.type == sfEvtMouseButtonPressed)
			{

				if (event.mouseButton.button == sfMouseLeft)
				{

				}
			}
		}

		if (gameData->x <= 700 && gameData->y > 499)
		{
			gameData->phase = Running;
		}

		if (gameData->y > 800)
		{
			gameData->phase = Running;
		}

		gameData->y = gameData->y + 0.1;

		if (sfKeyboard_isKeyPressed(sfKeyLeft))
		{
			gameData->x = gameData->x - 0.1;
		}

		if (sfKeyboard_isKeyPressed(sfKeyRight))
		{
			gameData->x = gameData->x + 0.1;
		}

		sfRenderWindow_clear(gameData->window, sfBlack);

		BlitSprite(gameData->Action, gameData->x, gameData->y, gameData->window);

		sfRenderWindow_display(gameData->window);
	}
}
void FallingStateExit(struct GAMEDATA* gameData)
{
	sfTexture_destroy(sfSprite_getTexture(gameData->Action));
	sfSprite_destroy(gameData->Action);
}
void FallingState(struct GAMEDATA* gameData)
{
	FallingStateInit(gameData); 
	FallingStateUpdate(gameData); 
	FallingStateExit(gameData); 
}
