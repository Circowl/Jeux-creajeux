#include "JumpingState.h"

void JumpingStateInit(struct GAMEDATA* gameData)
{
	gameData->Action = LoadSprite("jumping.png", 1);
}
void JumpingStateUpdate(struct GAMEDATA* gameData)
{
	sfEvent event;
	float bond = 0;
	while (gameData->phase == Jumping)
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

		if (bond >= 200)
		{
			gameData->phase = Falling;
		}

		gameData->y = gameData->y - 0.1;
		bond = bond + 0.1;
		printf("%f\n", bond);

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
void JumpingStateExit(struct GAMEDATA* gameData)
{
	sfTexture_destroy(sfSprite_getTexture(gameData->Action));
	sfSprite_destroy(gameData->Action);
}
void JumpingState(struct GAMEDATA* gameData)
{
	JumpingStateInit(gameData); 
	JumpingStateUpdate(gameData); 
	JumpingStateExit(gameData); 
}
