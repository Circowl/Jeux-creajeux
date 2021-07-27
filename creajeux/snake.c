#include "../Ngck_moteur/Ngck.h"

//Machins importants
FILE _iob[] = { *stdin,*stdout,*stderr };
extern "C" FILE *__cdecl __iob_func(void) { return _iob; }



int i = 0;
int j = 0;
int directionx = 0;
int directiony = 1;
int x = 14;
int y = 9;
int tab[20][30];
int a = 0;
int b = 0;
int Taille = 3;
int begin = 1;
int aleax = 0;
int aleay = 0;
int finish = 0;
char score[1];
int num = 0;
int mode = 1;

// -----------------------------------------------------------
void InitialiseGame()
{
	if (begin == 1)
	{
		tab[8][14] = 2;
		tab[7][14] = 1;
		begin = 0;
	}
	aleax = (rand() % 28 + 1);
	aleay = (rand() % 18 + 1);
	finish = 0;

}
// -----------------------------------------------------------



void GameLoop()
{
	KSetDisplayColor(11);
	sprintf(score, "%i", num);
	KPrintString(score, 26, 16);
	if (mode == 1)
		KSetDisplayColor(9);
	if (mode == -1)
		KSetDisplayColor(12);
	for (i = 0; i < 30; i++)
		for (j = 0; j < 20; j++)
			if (i == 0 || i == 29 || j == 0 || j == 19)
				KPrintSquare(i, j);

	KSetDisplayColor(10);
	while (tab[aleay][aleax] != 0)
	{
		aleax = (rand() % 28 + 1);
		aleay = (rand() % 18 + 1);
	}
	KPrintBall(aleax, aleay);
	if (x == aleax && y == aleay)
	{
		Taille++;
		num++;
		InitialiseGame();
	}
	tab[y][x] = Taille;
	for (a = 0; a < 30; a++)
		for (b = 0; b < 20; b++)
		{
			if (tab[b][a] != 0)
			{
				KSetDisplayColor(8);
				KPrintBall(a, b);
				tab[b][a]--;
			}
		}
	if (KGetDown() && (directiony != -1 && directionx != 0)) // si j'appuie vers le bas et que le serpent ne va pas vers le haut alors je vais vers le bas
	{
		directiony = 1;
		directionx = 0;
	}
	else if (KGetUp() && (directiony != 1 && directionx != 0))  // 
	{
		directiony = -1;
		directionx = 0;
	}
	else if (KGetRight() && (directiony != 0 && directionx != -1))
	{
		directiony = 0;
		directionx = 1;
	}
	else if (KGetLeft() && (directiony != 0 && directionx != 1))
	{
		directiony = 0;
		directionx = -1;
	}

	if (directionx == 1)
	{
		if (tab[y][x + 1] != 0)
			finish++;
		x++;
	}
	if (directionx == -1)
	{
		if (tab[y][x - 1] != 0)
			finish++;
		x--;
	}
	if (directiony == 1)
	{
		if (tab[y + 1][x] != 0)
			finish++;
		y++;
	}
	if (directiony == -1)
	{
		if (tab[y - 1][x] != 0)
			finish++;
		y--;
	}


	if (KGetSpace())
		mode = mode * (-1);

	if ((mode == (-1) && (x == 0 || x == 29 || y == 0 || y == 19)) || finish == 1)
	{
		for (a = 0; a < 30; a++)
			for (b = 0; b < 20; b++)
				tab[b][a] = 0;
		Taille = 3;
		begin = 1;
		directiony = 1;
		directionx = 0;
		num = 0;
		InitialiseGame();
		x = 14;
		y = 9;
	}
	if (mode == 1)
	{
		if (x == 0)
			x = 28;
		if (x == 29)
			x = 1;
		if (y == 0)
			y = 18;
		if (y == 19)
			y = 1;
	}
}
// -----------------------------------------------------------

