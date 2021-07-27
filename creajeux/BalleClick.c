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
sfTime temps;
sfClock* horloge = 0;

sfEvent event;

sfSprite* Boy;
sfSprite* Mort;
sfSprite* Un;
sfSprite* Deux;
sfSprite* Trois;
sfSprite* Bang;
sfSprite* gris;



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

void BlitFloat(sfFont* font, float Nombre, float x, float y, sfRenderWindow* window) // Fonction qui permet d'afficher une variable nombre à une certaine position
{
	char str[100] = "";
	sfText* text = sfText_create();
	sfText_setColor(text, sfBlack);
	snprintf(str, 100, "%f", Nombre);
	sfText_setString(text, str);
	sfText_setFont(text, font);
	sfVector2f posVec = { x, y };
	sfText_setCharacterSize(text, 30);
	sfText_setPosition(text, posVec);
	sfRenderWindow_drawText(window, text, NULL);
	sfText_destroy(text);
}
void BlitRecord(sfFont* font, float Nombre, float x, float y, sfRenderWindow* window) // Fonction qui permet d'afficher une variable nombre à une certaine position
{
	char str[100] = "";
	sfText* text = sfText_create();
	sfText_setColor(text, sfBlack);
	snprintf(str, 100, "record: %f", Nombre);
	sfText_setString(text, str);
	sfText_setFont(text, font);
	sfVector2f posVec = { x, y };
	sfText_setCharacterSize(text, 25);
	sfText_setPosition(text, posVec);
	sfRenderWindow_drawText(window, text, NULL);
	sfText_destroy(text);
}


int _tmain(int argc, _TCHAR* argv[])
{

	sfVideoMode mode = { 1280, 800, 32 };
	window = sfRenderWindow_create(mode, "3 2 1 BANG", sfResize | sfClose, NULL);
	srand((unsigned int)time(NULL));

	sfFont* font = sfFont_createFromFile("CarnevaleeFreakshow.ttf");

	int end = 1;
	

	int perso1 = 1;
	int perso2 = 1;
	int perso3 = 1;

	int vie1 = 5;
	int vie2 = 5;
	int vie3 = 5;

	float vitesse = 0;
	float record = 100;
	float go = 0;

	horloge = sfClock_create();
	
	gris = LoadSprite("gris2.png", 0);
	Boy = LoadSprite("Boy.png", 1);
	Mort = LoadSprite("mort.png", 1);
	Un = LoadSprite("1.png", 1);
	Deux = LoadSprite("2.png", 1);
	Trois = LoadSprite("3.png", 1);
	Bang = LoadSprite("Bang.png", 1);



	while (sfRenderWindow_isOpen(window))
	{

		while (sfRenderWindow_pollEvent(window, &event))
		{
			if (event.type == sfEvtClosed) exit(0); //Fermeture en appuyant sur le bouton Fermer

			if (event.type == sfEvtKeyPressed)
			{
				if (event.key.code == sfKeyReturn)
				{
					end = 0;
					sfClock_restart(horloge);
					if (vie1 != 0)
						perso1 = 1;
					if (vie2 != 0)
						perso2 = 1;
					if (vie3 != 0)
						perso3 = 1;
					go = rand() % 6 + 3;
				}
				if (event.key.code == sfKeyA && end == 0)
				{
					if (sfTime_asSeconds(sfClock_getElapsedTime(horloge)) < go && perso1 == 1)
					{
						perso1 = 0;
						vie1--;
					}
					if (perso1 == 1)
					{
						if (perso2 == 1)
						{
							perso2 = 0;
							vie2--;
						}
						if (perso3 == 1)
						{
							perso3 = 0;
							vie3--;
						}
						end = 1;
						vitesse = sfTime_asSeconds(sfClock_getElapsedTime(horloge)) - go;
						if (record > vitesse)
							record = vitesse;
					}
				}
				if (event.key.code == sfKeySpace && end == 0)
				{
					if (sfTime_asSeconds(sfClock_getElapsedTime(horloge)) < go && perso2 == 1)
					{
						perso2 = 0;
						vie2--;
					}
					if (perso2 == 1)
					{
						if (perso1 == 1)
						{
							perso1 = 0;
							vie1--;
						}
						if (perso3 == 1)
						{
							perso3 = 0;
							vie3--;
						}
						end = 1;
						vitesse = sfTime_asSeconds(sfClock_getElapsedTime(horloge)) - go;
						if (record > vitesse)
							record = vitesse;
					}
				}
				if (event.key.code == sfKeyNumpad0 && end == 0)
				{
					if (sfTime_asSeconds(sfClock_getElapsedTime(horloge)) < go && perso3 == 1)
					{
						perso3 = 0;
						vie3--;
					}
					if (perso3 == 1)
					{
						if (perso1 == 1)
						{
							perso1 = 0;
							vie1--;
						}
						if (perso2 == 1)
						{
							perso2 = 0;
							vie2--;
						}
						end = 1;
						vitesse = sfTime_asSeconds(sfClock_getElapsedTime(horloge)) - go;
						if (record > vitesse)
							record = vitesse;
					}
				}
			}
		}


		sfRenderWindow_clear(window, sfWhite);

		BlitSprite(gris, 0, 0, window);

		if (sfTime_asSeconds(sfClock_getElapsedTime(horloge)) >= 0 && sfTime_asSeconds(sfClock_getElapsedTime(horloge)) < 1 && end == 0)
			BlitSprite(Trois, 640, 400, window);
		if (sfTime_asSeconds(sfClock_getElapsedTime(horloge)) >= 1 && sfTime_asSeconds(sfClock_getElapsedTime(horloge)) < 2 && end == 0)
			BlitSprite(Deux, 640, 400, window);
		if (sfTime_asSeconds(sfClock_getElapsedTime(horloge)) >= 2 && sfTime_asSeconds(sfClock_getElapsedTime(horloge)) < 3 && end == 0)
			BlitSprite(Un, 640, 400, window);
		if (sfTime_asSeconds(sfClock_getElapsedTime(horloge)) >= go && sfTime_asSeconds(sfClock_getElapsedTime(horloge)) < 11 && end == 0)
			BlitSprite(Bang, 640, 400, window);

		if (perso1 == 1)
			BlitSprite(Boy, 200, 200, window);
		else
			BlitSprite(Mort, 200, 200, window);
		if (perso2 == 1)
			BlitSprite(Boy, 640, 600, window);
		else
			BlitSprite(Mort, 640, 600, window);
		if (perso3 == 1)
			BlitSprite(Boy, 1080, 200, window);
		else
			BlitSprite(Mort, 1080, 200, window);

		if (end == 1)
		{
			BlitInt(font, vie1, 190, 270, window);
			BlitInt(font, vie2, 630, 670, window);
			BlitInt(font, vie3, 1070, 270, window);
			BlitFloat(font, vitesse, 1100, 700, window);
			if (record < 99)
				BlitRecord(font, record, 100, 700, window);
		}
		

		sfRenderWindow_display(window);
	}

	return 0;
}
