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

int tab[1000][1000];

sfSprite* affichage[4];
sfSprite* personnage;



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

	sfVideoMode mode = { 1280, 960, 32 };
	window = sfRenderWindow_create(mode, "3 2 1 BANG", sfResize | sfClose, NULL);
	srand((unsigned int)time(NULL));
	horloge = sfClock_create();

	affichage[0] = LoadSprite("Perso/herbe.png", 0);
	affichage[1] = LoadSprite("Perso/wall.png", 0);
	affichage[2] = LoadSprite("Perso/crate.png", 0);
	affichage[3] = LoadSprite("Perso/sable.png", 0);
	personnage = LoadSprite("Perso/front.bmp", 1);

	for (int a = 0; a < 1000; a++)
	{
		for (int b = 0; b < 1000; b++)
		{
			tab[a][b] = rand() % 4;
		}
	}

	float camerax = 500;
	float cameray = 500;



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
					tab[(int)(((cameray*32) + sfMouse_getPositionRenderWindow(window).y) / 32)][(int)(((camerax*32) + sfMouse_getPositionRenderWindow(window).x) / 32)] = 3;
				}
			}
		}

		if (sfKeyboard_isKeyPressed(sfKeyLeft) && (int)camerax > 0)
		{
			if (tab[((int)cameray*32 + 480)/32][((int)camerax*32 + 640 - 16)/32] != 1 && tab[((int)cameray*32 + 480)/32][((int)camerax*32 + 640 - 16)/32] != 2)
				camerax = camerax - 0.005;
		}
		if (sfKeyboard_isKeyPressed(sfKeyRight) && (int)camerax <= 999)
		{
			if (tab[((int)cameray*32 + 480)/32][((int)camerax*32 + 640 + 16)/32] != 1 && tab[((int)cameray*32 + 480)/32][((int)camerax*32 + 640 + 16)/32] != 2)
				camerax = camerax + 0.005;
		}
		if (sfKeyboard_isKeyPressed(sfKeyUp) && (int)cameray > 0)
		{
			if (tab[((int)cameray*32 + 480 - 16)/32][((int)camerax*32 + 640)/32] != 1 && tab[((int)cameray*32 + 480 - 16)/32][((int)camerax*32 + 640)/32] != 2)
				cameray = cameray - 0.005;
		}
		if (sfKeyboard_isKeyPressed(sfKeyDown) && (int)cameray <= 999)
		{
			if (tab[((int)cameray*32 + 480 + 16)/32][((int)camerax*32 + 640)/32] != 1 && tab[((int)cameray*32 + 480 + 16)/32][((int)camerax*32 + 640)/32] != 2)
				cameray = cameray + 0.005;
		}
		sfRenderWindow_clear(window, sfWhite);


		BlitSprite(affichage[0], 0, 0, window);
		for (int i = (int)cameray ; i < 36 + (int)cameray ; i++)
		{
			for (int j = (int)camerax ; j < 48 + (int)camerax ; j++)
			{
					BlitSprite(affichage[tab[i][j]], j * 32 - camerax * 32, i * 32 - cameray * 32, window);
			}
		}
		BlitSprite(personnage, 640, 480, window);
	
		sfRenderWindow_display(window);
	}

	return 0;
}