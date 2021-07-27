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


	sfVideoMode mode = { 960, 800, 32 };
	window = sfRenderWindow_create(mode, "SFML window", sfResize | sfClose, NULL);

	//Sprite

	sfSprite* tableau;
	sfSprite* cadre;

	tableau = LoadSprite("Random.png", 0);
	cadre = LoadSprite("cadre.png", 0);

	int lag = 40;
	int test = 0;
	int win = 0;
	float x = 0;
	float y = 0;

	sfRectangleShape* bloc = sfRectangleShape_create();
	sfVector2f vec = { 365, 40 };
	sfVector2f ori = { -120, -105 };
	sfRectangleShape_setSize(bloc, vec);
	sfRectangleShape_setOrigin(bloc, ori);
	sfColor mycolor = { 236,231,58,100 };
	sfRectangleShape_setFillColor(bloc, mycolor);

	printf("\n\n\n\n        PRESS SPACE");

	while (sfRenderWindow_isOpen(window))
	{

		while (sfRenderWindow_pollEvent(window, &event))
		{
			if (event.type == sfEvtClosed) exit(0); //Fermeture en appuyant sur le bouton Fermer

			if (event.type == sfEvtKeyPressed)
			{
				if (event.key.code == sfKeySpace)
				{
					test = 1;
				}
			}
		}

		if (ori.y > -600)
		{
			ori.y = ori.y - 47;
		}
		else
		{
			if (ori.x == -480)
			{
				ori.x = -120;
			}
			else if (ori.x == -120)
			{
				ori.x = -480;
			}
			ori.y = -105;
		}
		
		if (test == 1)
		{
			lag = lag + 10;
			if (lag > 250)
			{
				lag = lag + rand() % 30;
				if (lag > 600 && win == 0)
				{
					lag = 100000;
					win = 1;
				}
			}
		}
		if (lag < 5000)
		{
			sfRectangleShape_setOrigin(bloc, ori);
		}
		if (win == 0)
		{
			x = ori.x;
			y = ori.y;
		}
		sfRenderWindow_clear(window, sfBlack);


		BlitSprite(tableau, 0, 0, window);
		sfRenderWindow_drawRectangleShape(window, bloc, NULL);
		BlitSprite(cadre, -x - 12, -y - 9, window);
	
		sfRenderWindow_display(window);
		if (win == 0)
			Sleep(lag);
	}

	return 0;
}

	

