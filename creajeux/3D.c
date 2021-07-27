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
#include <stdio.h>

sfRenderWindow* window = 0;
sfEvent event;

sfTime temps;
sfClock* horloge = 0;

sfSprite* Fond = 0;
sfSprite* Montagne = 0;
sfSprite* Sol = 0;
sfSprite* Perso = 0;
sfImage* Collisions = 0;
sfImage* Collisions2 = 0;


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

void BlitInt(sfFont* font, int Nombre, float x, float y, sfRenderWindow* window) // Fonction qui permet d'afficher une variable nombre à une certaine position
{
	char str[100] = "";
	sfText* text = sfText_create();
	sfText_setColor(text, sfBlack);
	snprintf(str, 100, "%d", Nombre);
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

	sfVideoMode mode = { 500, 889, 32 };
	window = sfRenderWindow_create(mode, "3 2 1 BANG", sfResize | sfClose, NULL);
	srand((unsigned int)time(NULL));
	horloge = sfClock_create();

	Fond = LoadSprite("mobile/fond.png", 0);
	Montagne = LoadSprite("mobile/Montagne.png", 0);
	Sol = LoadSprite("mobile/Sol.png", 0);
	Perso = LoadSprite("mobile/perso.png", 1);

	float camera = 1;
	float persoy = 0;
	int change = 1;

	Collisions = sfImage_createFromFile("mobile/Sol.png");
	Collisions2 = sfImage_createFromFile("mobile/Montagne.png");

	while (sfRenderWindow_isOpen(window))
	{

		

		while (sfRenderWindow_pollEvent(window, &event))
		{
			if (event.type == sfEvtClosed) exit(0); //Fermeture en appuyant sur le bouton Fermer

			if (event.type == sfEvtKeyPressed)
			{

			}
			if (event.type == sfEvtMouseButtonPressed)
			{

				if (event.mouseButton.button == sfMouseLeft)
				{
					change = (-change);
				}
			}
		}

		if (camera >= 0 && camera <= 2500)
		{
			if (sfKeyboard_isKeyPressed(sfKeyLeft))
			{
				camera = camera - 0.2;
				if (camera < 0)
					camera = 0;
			}
			if (sfKeyboard_isKeyPressed(sfKeyRight))
			{
				camera = camera + 0.2;
				if (camera > 2500)
					camera = 2500;
			}
		}

		persoy = 0;
		if (change == 1)
		{
			while (sfImage_getPixel(Collisions, (int)camera + 250, (int)persoy).a == 0)
			{
				persoy++;
			}
		}
		if (change == -1)
		{
			while (sfImage_getPixel(Collisions2, (int)camera / 3 + 250, (int)persoy).a == 0)
			{
				persoy++;
			}
		}

		sfRenderWindow_clear(window, sfBlack);

		BlitSprite(Fond, 0, 0, window);
		BlitSprite(Montagne, -camera / 3, 0, window);
		BlitSprite(Sol, -camera, 0, window);
		BlitSprite(Perso, 250, persoy, window);

		sfRenderWindow_display(window);
	}

	return 0;
}