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
#include <string.h>


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


void BlitText(sfFont* font, char* str, float x, float y, sfRenderWindow* window) // Fonction qui permet d'afficher une variable nombre à une certaine position
{
	sfText* text = sfText_create();
	sfText_setColor(text, sfBlack);
	sfText_setString(text, str);
	sfText_setFont(text, font);
	sfVector2f posVec = { x, y };
	sfText_setCharacterSize(text, 50);
	sfText_setPosition(text, posVec);
	sfRenderWindow_drawText(window, text, NULL);
	sfText_destroy(text);
}

int _tmain(int argc, _TCHAR* argv[])
{

	sfTime temps;
	sfClock* horloge = 0;

	sfVideoMode mode = { 1280, 800, 32 };
	window = sfRenderWindow_create(mode, "SFML window", sfResize | sfClose, NULL);
	srand((unsigned int)time(NULL));

	sfFont* font = sfFont_createFromFile("myfont.ttf");

	sfSprite* fond = LoadSprite("fond.png", 0);
	sfSprite* pierre = LoadSprite("pierre.png", 1);
	sfSprite* destin = LoadSprite("destin.png", 1);
	sfSprite* roue = LoadSprite("roue.png", 1);
	sfSprite* bois = LoadSprite("bois.png", 1);

	float rotation = 0;
	float rotationD = 0;

	horloge = sfClock_create();

	float vitesse = 1;

	float alea = (rand() % 5 + 2)*0.02;

	int top = 0;

	float frame = 0;
	


	//printf("%f\n", alea);

	while (sfRenderWindow_isOpen(window))
	{
		while (sfRenderWindow_pollEvent(window, &event))
		{
			if (event.type == sfEvtClosed) exit(0); //Fermeture en appuyant sur le bouton Fermer

			if (event.type == sfEvtKeyPressed)
			{
				if (event.key.code == sfKeySpace)
				{
					top = 1;
				}
				if (event.key.code == sfKeyReturn)
				{
					top = 0;
					vitesse = 1;
				}
			}
		}

		frame = sfTime_asSeconds(sfClock_restart(horloge));

		rotation = rotation - 200*vitesse*frame;

		sfSprite_setRotation(roue, rotation - 2);

		rotationD = rotationD + 600*vitesse*frame;
		if (rotationD > 45)
			rotationD -= 45;

		if (vitesse > 0 && top == 1)
		{
			vitesse = vitesse - alea*frame;
		}
		if (vitesse <= 0 && top == 1)
			vitesse = 0;
		

		sfSprite_setRotation(destin, rotationD);

		sfRenderWindow_clear(window, sfBlack);

		BlitSprite(fond, 0, 0, window);
		BlitSprite(pierre, 200, 520, window);
		BlitSprite(bois, 325, 580, window);
		BlitSprite(roue, 640, 400, window);
		BlitSprite(destin, 325, 400, window);

		BlitText(font, "coucou", 100, 100, window);

		sfRenderWindow_display(window);
	}

	return 0;
}
