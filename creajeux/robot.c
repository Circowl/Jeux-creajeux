
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

float x = 270;
float y = 260;


int _tmain(int argc, _TCHAR* argv[])
{


	printf("Chargement et affichage d'un sprite dans la fenetre\n\n");


	sfVideoMode mode = { 1228, 614, 32 };
	window = sfRenderWindow_create(mode, "SFML window", sfResize | sfClose, NULL);

	//Sprite
	sfTexture* TextureRobotUp = 0;
	sfTexture* TextureRobotDown = 0;
	sfTexture* TextureRobotRight = 0;
	sfTexture* TextureRobotLeft = 0;
	TextureRobotUp = sfTexture_createFromFile("robot3.png", NULL);
	TextureRobotDown = sfTexture_createFromFile("robot2.png", NULL);
	TextureRobotRight = sfTexture_createFromFile("robot4.png", NULL);
	TextureRobotLeft = sfTexture_createFromFile("robot.png", NULL);

	sfImage* Collisions = 0;
	Collisions = sfImage_createFromFile("mapMask.png");

	sfSprite* exemple;
	sfSprite* map;
	sfVector2f recadre = { 0.15, 0.15 };
	map = LoadSprite("mapIso.png", 0);
	exemple = LoadSprite("robot.png", 1);
	sfSprite_setScale(exemple, recadre);
	while (sfRenderWindow_isOpen(window))
	{

		while (sfRenderWindow_pollEvent(window, &event))
		{
			if (event.type == sfEvtClosed) exit(0); //Fermeture en appuyant sur le bouton Fermer

			if (event.type == sfEvtMouseButtonPressed)
			{
				if (event.key.code == sfMouseLeft && sfImage_getPixel(Collisions, sfMouse_getPosition(window).x, sfMouse_getPosition(window).y).g <= 8)
				{
					if (sfImage_getPixel(Collisions, sfMouse_getPosition(window).x, sfMouse_getPosition(window).y).g < sfImage_getPixel(Collisions, x, y).g && abs(sfImage_getPixel(Collisions, sfMouse_getPosition(window).x, sfMouse_getPosition(window).y).r - sfImage_getPixel(Collisions, x, y).r) < abs(sfImage_getPixel(Collisions, sfMouse_getPosition(window).x, sfMouse_getPosition(window).y).g - sfImage_getPixel(Collisions, x, y).g))
					{
						x = x - 69;
						y = y - 34.5;
						sfSprite_setTexture(exemple, TextureRobotUp, sfTrue);
					}
					else if (sfImage_getPixel(Collisions, sfMouse_getPosition(window).x, sfMouse_getPosition(window).y).g > sfImage_getPixel(Collisions, x, y).g && abs(sfImage_getPixel(Collisions, sfMouse_getPosition(window).x, sfMouse_getPosition(window).y).r - sfImage_getPixel(Collisions, x, y).r) < abs(sfImage_getPixel(Collisions, sfMouse_getPosition(window).x, sfMouse_getPosition(window).y).g - sfImage_getPixel(Collisions, x, y).g))
					{
						x = x + 69;
						y = y + 34.5;
						sfSprite_setTexture(exemple, TextureRobotDown, sfTrue);
					}

					else if (sfImage_getPixel(Collisions, sfMouse_getPosition(window).x, sfMouse_getPosition(window).y).r > sfImage_getPixel(Collisions, x, y).r && abs(sfImage_getPixel(Collisions, sfMouse_getPosition(window).x, sfMouse_getPosition(window).y).r - sfImage_getPixel(Collisions, x, y).r) >= abs(sfImage_getPixel(Collisions, sfMouse_getPosition(window).x, sfMouse_getPosition(window).y).g - sfImage_getPixel(Collisions, x, y).g))
					{
						if ((sfImage_getPixel(Collisions, x, y).r == 6 && sfImage_getPixel(Collisions, x, y).g == 0) || (sfImage_getPixel(Collisions, x, y).r == 7 && sfImage_getPixel(Collisions, x, y).g == 1))
						{
							y = y + 34.5;
							sfSprite_setTexture(exemple, TextureRobotDown, sfTrue);
						}
						else
						{
							y = y - 34.5;
							sfSprite_setTexture(exemple, TextureRobotRight, sfTrue);
						}
						if ((sfImage_getPixel(Collisions, x, y).r == 7 && sfImage_getPixel(Collisions, x, y).g == 7) || (sfImage_getPixel(Collisions, x, y).r == 6 && sfImage_getPixel(Collisions, x, y).g == 8))
						{ 
							x = x - 69;
							sfSprite_setTexture(exemple, TextureRobotUp, sfTrue);
						}
						else
						{
							x = x + 69;
						}
					}

					else if (sfImage_getPixel(Collisions, sfMouse_getPosition(window).x, sfMouse_getPosition(window).y).r < sfImage_getPixel(Collisions, x, y).r && abs(sfImage_getPixel(Collisions, sfMouse_getPosition(window).x, sfMouse_getPosition(window).y).r - sfImage_getPixel(Collisions, x, y).r) >= abs(sfImage_getPixel(Collisions, sfMouse_getPosition(window).x, sfMouse_getPosition(window).y).g - sfImage_getPixel(Collisions, x, y).g))
					{
						if ((sfImage_getPixel(Collisions, x, y).r == 2 && sfImage_getPixel(Collisions, x, y).g == 8) || (sfImage_getPixel(Collisions, x, y).r == 1 && sfImage_getPixel(Collisions, x, y).g == 7))
						{
							y = y - 34.5;
							sfSprite_setTexture(exemple, TextureRobotUp, sfTrue);
						}
						else
						{
							y = y + 34.5;
							sfSprite_setTexture(exemple, TextureRobotLeft, sfTrue);
						}
						if ((sfImage_getPixel(Collisions, x, y).r == 2 && sfImage_getPixel(Collisions, x, y).g == 0) || (sfImage_getPixel(Collisions, x, y).r == 1 && sfImage_getPixel(Collisions, x, y).g == 1))
						{
							x = x + 69;
							sfSprite_setTexture(exemple, TextureRobotDown, sfTrue);
						}
						else
						{
							x = x - 69;
						}
					}
				}
			}

		}

		sfRenderWindow_clear(window, sfBlack);


		//printf("Pixel: %u", sfImage_getPixel(Collisions, sfMouse_getPosition(window).x, sfMouse_getPosition(window).y).r);

		BlitSprite(map, 0, 0, window);
		BlitSprite(exemple, x, y, window);
		//printf("x: %d  y: %d\n", sfImage_getPixel(Collisions, sfMouse_getPosition(window).x, sfMouse_getPosition(window).y).r, sfImage_getPixel(Collisions, sfMouse_getPosition(window).x, sfMouse_getPosition(window).y).g);
		sfRenderWindow_display(window);
	}

	return 0;
}
