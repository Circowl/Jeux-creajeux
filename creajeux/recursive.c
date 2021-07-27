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

sfSprite* affichage[8];
sfSprite* win;
sfSprite* bombe;
sfSprite* feu;
sfSprite* feuBas;
sfSprite* feuHaut;
sfSprite* feuGauche;
sfSprite* feuDroite;

int test = 1;

/*sfSprite* fond;
sfSprite* bas;
sfSprite* haut;
sfSprite* gauche;
sfSprite* droite;
sfSprite* mur;
sfSprite* caisse;
sfSprite* fin;*/

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

void printTab(int tab[10][10])
{
	for (int i = 0; i <= 9; i++)
	{
		for (int j = 0; j <= 9; j++)
		{
			printf("%d \t ", tab[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");
}


void remplir(unsigned int chemin[10][10], int tab[10][10], int persox, int persoy, int nombre)
{
	if (persoy >= 0 && persoy <= 9 && persox >= 0 && persox <= 9)
	{
		if (tab[persox][persoy] != 1 && chemin[persox][persoy] > nombre)
		{
			chemin[persox][persoy] = nombre;
			remplir(chemin, tab, persox, persoy - 1, nombre + 1);
			remplir(chemin, tab, persox, persoy + 1, nombre + 1);
			remplir(chemin, tab, persox - 1, persoy, nombre + 1);
			remplir(chemin, tab, persox + 1, persoy, nombre + 1);
		}
	}
}

void ligne(unsigned int chemin[10][10], int tab[10][10], int lignex, int ligney)
{
	if (ligney >= 0 && ligney <= 9 && lignex >= 0 && lignex <= 9)
	{
		tab[lignex][ligney] = 3;
		if (chemin[lignex][ligney - 1] == chemin[lignex][ligney] - 1)
		{
			ligne(chemin, tab, lignex, ligney - 1);
		}
		else if (chemin[lignex][ligney + 1] == chemin[lignex][ligney] - 1)
		{
			ligne(chemin, tab, lignex, ligney + 1);
		}
		else if (chemin[lignex - 1][ligney] == chemin[lignex][ligney] - 1)
		{
			ligne(chemin, tab, lignex - 1, ligney);
		}
		else if (chemin[lignex + 1][ligney] == chemin[lignex][ligney] - 1)
		{
			ligne(chemin, tab, lignex + 1, ligney);
		}
	}
}

int _tmain(int argc, _TCHAR* argv[])
{

	if (test == 1)
	{
		sfVideoMode mode = { 320, 320, 32 };
		window = sfRenderWindow_create(mode, "3 2 1 BANG", sfResize | sfClose, NULL);
		test = 0;
	}
	srand((unsigned int)time(NULL));
	horloge = sfClock_create();

	affichage[0] = LoadSprite("Perso/pelouse.bmp", 0);
	affichage[1] = LoadSprite("Perso/wall.bmp", 0);
	affichage[2] = LoadSprite("Perso/front.bmp", 0);
	affichage[3] = LoadSprite("Perso/arrival.bmp", 0);
	affichage[4] = LoadSprite("Perso/crate.bmp", 0);
	affichage[5] = LoadSprite("Perso/back.bmp", 0);
	affichage[6] = LoadSprite("Perso/right.bmp", 0);
	affichage[7] = LoadSprite("Perso/left.bmp", 0);
	win = LoadSprite("Perso/win.png", 0);
	bombe = LoadSprite("Perso/bombe.png", 0);
	feu = LoadSprite("Perso/feu.png", 0);
	feuDroite = LoadSprite("Perso/feuDroite.png", 0);
	feuHaut = LoadSprite("Perso/feuHaut.png", 0);
	feuBas = LoadSprite("Perso/feuBas.png", 0);
	feuGauche = LoadSprite("Perso/feuGauche.png", 0);

	int persox = 0;
	int persoy = 0;
	int bombex = 0;
	int bombey = 0;
	int end = 0;
	int tictac = 0;
	int nombre = 0;
	int lignex = 9;
	int ligney = 9;

	int tab[10][10] = { 2,0,0,1,0,1,1,0,0,0,
						0,1,4,0,4,0,1,0,1,0,
						0,4,0,1,0,1,1,0,4,0,
						1,1,0,1,0,1,0,0,0,0,
						1,1,0,1,0,1,0,1,1,4,
						0,0,0,0,0,0,0,0,0,0,
						0,1,1,1,1,1,0,1,1,0,
						0,0,0,0,0,1,0,1,1,0,
						1,1,0,4,1,1,0,1,1,0,
						0,0,0,0,0,0,0,1,1,3 };

	unsigned int chemin[10][10] = { -2,-2,-2,-2,-2,-2,-2,-2,-2,-2,
									-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,
									-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,
									-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,
									-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,
									-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,
									-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,
									-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,
									-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,
									-2,-2,-2,-2,-2,-2,-2,-2,-2,-2 };


	while (sfRenderWindow_isOpen(window))
	{
		
		//remplir(tab, persox, persoy);

		while (sfRenderWindow_pollEvent(window, &event))
		{
			if (event.type == sfEvtClosed) exit(0); //Fermeture en appuyant sur le bouton Fermer

			if (event.type == sfEvtKeyPressed)
			{
				
				if (event.key.code == sfKeyLeft && persoy > 0)
				{
					if (tab[persox][persoy - 1] != 1)
					{
						tab[persox][persoy - 1] = 2;
						tab[persox][persoy] = 0;
						persoy--;
					}
				}
				if (event.key.code == sfKeyRight && persoy < 9)
				{
					if (tab[persox][persoy + 1] != 1)
					{
						tab[persox][persoy + 1] = 2;
						tab[persox][persoy] = 0;
						persoy++;
					}
				}
				if (event.key.code == sfKeyUp && persox > 0)
				{
					if (tab[persox - 1][persoy] != 1)
					{
						tab[persox - 1][persoy] = 2;
						tab[persox][persoy] = 0;
						persox--;
					}
				}
				if (event.key.code == sfKeyDown && persox < 9)
				{
					if (tab[persox + 1][persoy] != 1)
					{
						tab[persox + 1][persoy] = 2;
						tab[persox][persoy] = 0;
						persox++;
					}
				}
			}
		}

		remplir(chemin, tab, persox, persoy, nombre);
		for (int i = 0; i <= 9; i++)
		{
			for (int j = 0; j <= 9; j++)
			{
				if (tab[i][j] == 3)
				{
					tab[i][j] = 0;
				}
			}
		}
		ligne(chemin, tab, lignex, ligney);


		sfRenderWindow_clear(window, sfWhite);

		

		BlitSprite(affichage[0], 0, 0, window);
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				if (tab[i][j] != 0)
				{
					BlitSprite(affichage[tab[i][j]], j * 32, i * 32, window);
				}
			}
		}



		sfRenderWindow_display(window);
	}

	return 0;
}