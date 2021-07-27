
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
#include <math.h>


sfRenderWindow* window = 0;

sfEvent event;


// ---------------- Sprite --------------- // 


sfSprite* tab[1000];




// ---------------------------------------------------------- Fonction d'affichage -------------------------------------------------------------------//

sfSprite* LoadSprite(char* nom, int isCentered) // Fonction qui permet de charger une texture dans un sprite
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

void BlitSprite(sfSprite* Sprite, float x, float y, sfRenderWindow* window) // Fonction qui permet d'afficher un sprite
{
	sfVector2f tempPosition = { x, y };
	sfSprite_setPosition(Sprite, tempPosition);
	sfRenderWindow_drawSprite(window, Sprite, NULL);
}


int _tmain(int argc, _TCHAR* argv[])
{

	// --------------------- Creation de la fenetre ----------------- //

	printf("Lancement du jeu: \n\n");
	sfVideoMode mode = { 1280, 800, 32 };
	window = sfRenderWindow_create(mode, "Creartillerie", sfResize | sfClose, NULL);
	int j = 0;
	sfSprite* test;

	srand((unsigned int)time(NULL));

	// ________________________________________________________________ //
	char str[100];

	for (int i = 0; i < 1000; i++)
	{
		sprintf(str, "DiamantRouge/(%d).png", i);
		tab[i] = LoadSprite(str, 0);
	}

	test = LoadSprite("boulet.png", 0);

	printf("%s", str);

	while (sfRenderWindow_isOpen(window))
	{


		while (sfRenderWindow_pollEvent(window, &event))
		{
			if (event.type == sfEvtClosed) exit(0);


		}


		sfRenderWindow_clear(window, sfBlack);


		BlitSprite(test, 200, 200, window);

		if (j < 1000)
		{
			BlitSprite(tab[j], 200, 200, 0, window);
			j++;
		}
		else
		{
			j = 0;
		}


		sfRenderWindow_display(window);

	}

	return 0;
}