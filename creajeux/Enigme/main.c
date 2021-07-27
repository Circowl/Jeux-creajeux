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


int porte(float x, float y)
{
	if (x >= 187 && x <= 350 && y >= 129 && y <= 502)
		return (1);
	else if (x >= 562 && x <= 724 && y >= 133 && y <= 505)
		return (2);
	else if (x >= 938 && x <= 1101 && y >= 132 && y <= 505)
		return (3);
	else
		return (0);
}


int _tmain(int argc, _TCHAR* argv[])
{


	sfVideoMode mode = { 1280, 900, 32 };
	window = sfRenderWindow_create(mode, "SFML window", sfResize | sfClose, NULL);

	//Sprite
	sfSprite* enigme1;
	sfSprite* enigme2;
	sfSprite* enigme3;
	sfSprite* enigme4;
	sfSprite* enigme5;
	sfSprite* enigme6;
	sfSprite* enigme7;
	sfSprite* enigme8;
	sfSprite* enigme9;
	sfSprite* enigme10;
	sfSprite* enigme11;
	sfSprite* enigme12;
	sfSprite* s_perdu;
	sfSprite* s_gagne;

	enigme1 = LoadSprite("enigme/1.jpg", 0);
	enigme2 = LoadSprite("enigme/2.jpg", 0);
	enigme3 = LoadSprite("enigme/3.jpg", 0);
	enigme4 = LoadSprite("enigme/4.jpg", 0);
	enigme5 = LoadSprite("enigme/5.jpg", 0);
	enigme6 = LoadSprite("enigme/6.jpg", 0);
	enigme7 = LoadSprite("enigme/7.jpg", 0);
	enigme8 = LoadSprite("enigme/8.jpg", 0);
	enigme9 = LoadSprite("enigme/9.jpg", 0);
	enigme10 = LoadSprite("enigme/10.jpg", 0);
	enigme11 = LoadSprite("enigme/11.jpg", 0);
	enigme12 = LoadSprite("enigme/12.jpg", 0);
	s_perdu = LoadSprite("enigme/perdu.jpg", 0);
	s_gagne = LoadSprite("enigme/gagne.jpg", 0);

	int phase = 1;
	int rep = 0;
	int gagne = 0;
	int perdu = 0;

	while (sfRenderWindow_isOpen(window))
	{
		while (sfRenderWindow_pollEvent(window, &event))
		{
			if (event.type == sfEvtClosed) exit(0); //Fermeture en appuyant sur le bouton Fermer

			if (event.type == sfEvtMouseButtonPressed)
			{

				if (event.mouseButton.button == sfMouseLeft)
				{
					rep = porte(sfMouse_getPositionRenderWindow(window).x, sfMouse_getPositionRenderWindow(window).y);
				}
			}
		}

		if (phase == 1)
		{
			if (rep == 3)
			{
				rep = 0;
				phase = 2;
			}
			else if (rep == 1 || rep == 2)
			{
				perdu = 1;
			}
		}
		if (phase == 2)
		{
			if (rep == 2)
			{
				rep = 0;
				phase = 3;
			}
			else if (rep == 1 || rep == 3)
			{
				perdu = 1;
			}
		}
		if (phase == 3)
		{
			if (rep == 3)
			{
				rep = 0;
				phase = 4;
			}
			else if (rep == 1 || rep == 2)
			{
				perdu = 1;
			}
		}
		if (phase == 4)
		{
			if (rep == 1)
			{
				rep = 0;
				phase = 5;
			}
			else if (rep == 2 || rep == 3)
			{
				perdu = 1;
			}
		}
		if (phase == 5)
		{
			if (rep == 2)
			{
				rep = 0;
				phase = 6;
			}
			else if (rep == 1 || rep == 3)
			{
				perdu = 1;
			}
		}
		if (phase == 6)
		{
			if (rep == 1)
			{
				rep = 0;
				phase = 7;
			}
			else if (rep == 2 || rep == 3)
			{
				perdu = 1;
			}
		}
		if (phase == 7)
		{
			if (rep == 3)
			{
				rep = 0;
				phase = 8;
			}
			else if (rep == 1 || rep == 2)
			{
				perdu = 1;
			}
		}
		if (phase == 8)
		{
			if (rep == 3)
			{
				rep = 0;
				phase = 9;
			}
			else if (rep == 1 || rep == 2)
			{
				perdu = 1;
			}
		}
		if (phase == 9)
		{
			if (rep == 2)
			{
				rep = 0;
				phase = 10;
			}
			else if (rep == 1 || rep == 3)
			{
				perdu = 1;
			}
		}
		if (phase == 10)
		{
			if (rep == 3)
			{
				rep = 0;
				phase = 11;
			}
			else if (rep == 1 || rep == 2)
			{
				perdu = 1;
			}
		}
		if (phase == 11)
		{
			if (rep == 1)
			{
				rep = 0;
				phase = 12;
			}
			else if (rep == 2 || rep == 3)
			{
				perdu = 1;
			}
		}
		if (phase == 12)
		{
			if (rep == 2)
			{
				rep = 0;
				gagne = 1;
			}
			else if (rep == 1 || rep == 3)
			{
				perdu = 1;
			}
		}

		sfRenderWindow_clear(window, sfBlack);

		if (phase == 1)
			BlitSprite(enigme1, 0, 0, window);
		if (phase == 2)
			BlitSprite(enigme2, 0, 0, window);
		if (phase == 3)
			BlitSprite(enigme3, 0, 0, window);
		if (phase == 4)
			BlitSprite(enigme4, 0, 0, window);
		if (phase == 5)
			BlitSprite(enigme5, 0, 0, window);
		if (phase == 6)
			BlitSprite(enigme7, 0, 0, window);
		if (phase == 7)
			BlitSprite(enigme7, 0, 0, window);
		if (phase == 8)
			BlitSprite(enigme8, 0, 0, window);
		if (phase == 9)
			BlitSprite(enigme9, 0, 0, window);
		if (phase == 10)
			BlitSprite(enigme10, 0, 0, window);
		if (phase == 11)
			BlitSprite(enigme11, 0, 0, window);
		if (phase == 12)
			BlitSprite(enigme12, 0, 0, window);
		if (perdu == 1)
			BlitSprite(s_perdu, 0, 0, window);
		if (gagne == 1)
			BlitSprite(s_gagne, 0, 0, window);

		sfRenderWindow_display(window);
	}

	return 0;
}
