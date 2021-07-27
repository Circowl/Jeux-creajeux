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

	sfVector2f origin = { sfTexture_getSize(TextureSprite).x /2, sfTexture_getSize(TextureSprite).y /2 };

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


	printf("Chargement et affichage d'un sprite dans la fenetre\n\n");


	sfVideoMode mode = { 640, 480, 32 };
	window = sfRenderWindow_create(mode, "SFML window", sfResize | sfClose, NULL);

	//Sprite

	sfSprite* exemple;



	while (sfRenderWindow_isOpen(window))
	{

		while (sfRenderWindow_pollEvent(window, &event))
		{
			if (event.type == sfEvtClosed) exit(0); //Fermeture en appuyant sur le bouton Fermer

		}

		sfRenderWindow_clear(window, sfBlack);

		exemple = LoadSprite("robot.png", 0);
		BlitSprite(exemple, 0, 0, window);

		sfRenderWindow_display(window);
	}

	return 0;
}

