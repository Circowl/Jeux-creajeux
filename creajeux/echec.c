#include <stdio.h>
#include <tchar.h>
#include <SFML/Window.h>
#include <SFML/Graphics.h>
#include <SFML/System.h>
#include <SFML/OpenGL.h>
#include <SFML/Network.h>
#include <SFML/Audio.h>
#include "time.h"
#include "windows.h"


sfRenderWindow* window = 0;

sfEvent event;


sfSprite* LoadSprite(char* nom, int isCentered)
{
	sfSprite* Sprite = 0;
	sfTexture* TextureSprite = 0;

	TextureSprite = sfTexture_createFromFile(nom, NULL);

	sfVector2f origin = { sfTexture_getSize(TextureSprite).x / 2, sfTexture_getSize(TextureSprite).y / 2 };

	Sprite = sfSprite_create();
	sfSprite_setTexture(Sprite, TextureSprite, sfTrue);
	if (isCentered == 1)
	{
		sfSprite_setOrigin(Sprite, origin);
	}
	return(Sprite);
}


void BlitSprite(sfSprite* Sprite, float x, float y, sfRenderWindow* window)
{
	sfVector2f tempPosition = { x, y };
	sfSprite_setPosition(Sprite, tempPosition);
	sfRenderWindow_drawSprite(window, Sprite, NULL);
}




int _tmain(int argc, _TCHAR* argv[])
{


	sfVideoMode mode = { 800, 800, 32 };
	window = sfRenderWindow_create(mode, "SFML window", sfResize | sfClose, NULL);

	sfSprite* map;

	map = LoadSprite("map.png", 0);

	int tab[8][8];

	FILE * pFile;
	pFile = fopen("plateau.txt", "r");
	if (pFile != NULL)
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				fscanf(pFile, "%d", &tab[i][j]);
			}
		}
	}
	fclose(pFile);

	sfSprite* blanc[6];
	blanc[0] = LoadSprite("pion2.png", 0);
	blanc[1] = LoadSprite("tour2.png", 0);
	blanc[2] = LoadSprite("cheval2.png", 0);
	blanc[3] = LoadSprite("fou2.png", 0);
	blanc[4] = LoadSprite("reine2.png", 0);
	blanc[5] = LoadSprite("roi2.png", 0);

	sfSprite* noir[6];
	noir[0] = LoadSprite("pion.png", 0);
	noir[1] = LoadSprite("tour.png", 0);
	noir[2] = LoadSprite("cheval.png", 0);
	noir[3] = LoadSprite("fou.png", 0);
	noir[4] = LoadSprite("reine.png", 0);
	noir[5] = LoadSprite("roi.png", 0);

	sfSprite* selec;

	selec = LoadSprite("case.png", 0);

	while (sfRenderWindow_isOpen(window))
	{
		while (sfRenderWindow_pollEvent(window, &event))
		{
			if (event.type == sfEvtClosed) exit(0); //Fermeture en appuyant sur le bouton Fermer

			if (event.type == sfEvtMouseButtonPressed)
			{

				if (event.mouseButton.button == sfMouseLeft)
				{
					
				}
			}
		}


		sfRenderWindow_clear(window, sfBlack);

		BlitSprite(map, 0, 0, window);
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (tab[i][j] < 6 && tab[i][j] >= 0)
				{
					BlitSprite(noir[tab[i][j]], (j * 100), (i * 100), window);
				}
				else if (tab[i][j] < 12 && tab[i][j] >= 6)
				{
					BlitSprite(blanc[(tab[i][j]) % 6], (j * 100), (i * 100), window);
				}
			}
		}
		BlitSprite(selec, ((sfMouse_getPositionRenderWindow(window).x) / 100) * 100, ((sfMouse_getPositionRenderWindow(window).y) / 100) * 100, window);

		sfRenderWindow_display(window);
	}

	return 0;
}
