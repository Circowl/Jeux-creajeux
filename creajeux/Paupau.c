
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

sfSprite* Paupau;
sfSprite* Chaussette;
sfSprite* Reine;
sfSprite* Fond;
sfSprite* Fin;

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
	float Paupaux = 640;
	float Paupauy = 700;

	float Chaussettex = 0;
	float Chaussettey = 0;

	float Reinex = 0;
	float Reiney = -350;

	int end = 0;

	sfVideoMode mode = { 1280, 800, 32 };
	window = sfRenderWindow_create(mode, "SFML window", sfResize | sfClose, NULL);
	srand((unsigned int)time(NULL));


	Paupau = LoadSprite("Paupau.png", 1);
	Chaussette = LoadSprite("Chaussette.png", 1);
	Reine = LoadSprite("Reine.png", 1);
	Fond = LoadSprite("Appart.png", 0);
	Fin = LoadSprite("Fin.png", 0);

	Chaussettex = rand() % 1200 + 40;
	Reinex = rand() % 1200 + 40;

	while (sfRenderWindow_isOpen(window))
	{

		while (sfRenderWindow_pollEvent(window, &event))
		{
			if (event.type == sfEvtClosed) exit(0); //Fermeture en appuyant sur le bouton Fermer

		}
		if (sfKeyboard_isKeyPressed(sfKeyRight) && Paupaux < 1280)
			Paupaux = Paupaux + 0.8;
		if (sfKeyboard_isKeyPressed(sfKeyLeft) && Paupaux > 0)
			Paupaux = Paupaux - 0.8;

		Chaussettey = Chaussettey + 0.3;
		Reiney = Reiney + 0.3;

		if (Chaussettey < 725 && Chaussettey > 675)
		{
			if (Chaussettex <= Paupaux + 50 && Chaussettex >= Paupaux - 150)
			{
				Chaussettex = rand() % 1200 + 40;
				Chaussettey = 0;
			}
		}
		if (Reiney < 725 && Reiney > 675)
		{
			if (Reinex <= Paupaux + 50 && Reinex >= Paupaux - 150)
			{
				Reinex = rand() % 1200 + 40;
				Reiney = 0;
			}
		}
		if (Reiney >= 799 || Chaussettey >= 799)
		{
			end = 1;
		}


		sfRenderWindow_clear(window, sfBlack);


		BlitSprite(Fond, 0, 0, window);
		BlitSprite(Paupau, Paupaux, Paupauy, window);
		BlitSprite(Chaussette, Chaussettex, Chaussettey, window);
		BlitSprite(Reine, Reinex, Reiney, window);
		if (end == 1)
			BlitSprite(Fin, 0, 0, window);
		sfRenderWindow_display(window);
	}

	return 0;
}
