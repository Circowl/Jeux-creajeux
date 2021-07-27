#include "../Ngck_moteur/Ngck.h"
#include "time.h"
#include "stdlib.h"

//Machins importants
FILE _iob[] = { *stdin,*stdout,*stderr };
extern "C" FILE *__cdecl __iob_func(void) { return _iob; }




int x1 = 0;
int y1 = 0;
int x2 = 0;
int y2 = 0;
int aleax = 0;
int aleay = 0;
int aleacolor = 0;
int couleur1 = 0;
int couleur2 = 0;
char score[1];
int carburant1 = 0;
int carburant2 = 0;
int begin = 1;
int joueur = 1;
int deplacement = 0;

// -----------------------------------------------------------
void InitialiseGame()
{
	srand(time(0));
	if (begin == 1)
	{
		x1 = 12;
		y1 = 9;
		x2 = 14;
		y2 = 9;
		carburant1 = 50;
		carburant2 = 50;
		joueur = 1;
		deplacement = 2;
	}
	begin = 0;
	aleacolor = (rand() % 4 + 1);
	aleax = (rand() % 28 + 1);
	aleay = (rand() % 18 + 1);
	while ((aleax == x1 && aleay == y1) || (aleax == x2 && aleay == y2))
	{
		aleax = (rand() % 28 + 1);
		aleay = (rand() % 18 + 1);
	}
}
// -----------------------------------------------------------



void GameLoop()
{
	KSetDisplayColor(11);
	sprintf(score, "%i", carburant1);
	KPrintString(score, 26, 16);
	KPrintSquare(24, 16);
	sprintf(score, "%i", carburant2);
	KPrintString(score, 26, 14);
	KPrintBall(24, 14);
	KSetDisplayColor(aleacolor);
	KPrintBar(aleax, aleay);
	if (x1 == aleax && y1 == aleay)
	{
		if (aleacolor == couleur1)
			carburant1 = carburant1 + 20;
		else
			carburant1 = carburant1 - 10;
		InitialiseGame();
	}
	if (x2 == aleax && y2 == aleay)
	{
		if (aleacolor == couleur2)
			carburant2 = carburant2 + 20;
		else
			carburant2 = carburant2 - 10;
		InitialiseGame();
	}
	KSetDisplayColor(couleur1);
	KPrintSquare(x1, y1);
	KSetDisplayColor(couleur2);
	KPrintBall(x2, y2);
	if (KGetDown() && joueur == 1 && y1 != 19 && !(x1 == x2 && (y1 + 1) == y2))
	{
		couleur1 = 1;
		y1++;
		carburant1--;
		deplacement--;
		if (deplacement == 0)
		{
			joueur = 2;
			deplacement = 2;
		}
	}
	else if (KGetRight() && joueur == 1 && x1 != 29 && !((x1 + 1) == x2 && y1 == y2))
	{
		couleur1 = 2;
		x1++;
		carburant1--;
		deplacement--;
		if (deplacement == 0)
		{
			joueur = 2;
			deplacement = 2;
		}
	}
	else if (KGetLeft() && joueur == 1 && x1 != 1 && !((x1 - 1) == x2 && y1 == y2))
	{
		couleur1 = 4;
		x1--;
		carburant1--;
		deplacement--;
		if (deplacement == 0)
		{
			joueur = 2;
			deplacement = 2;
		}
	}
	else if (KGetUp() && joueur == 1 && y1 != 1 && !(x1 == x2 && (y1 - 1) == y2))
	{
		couleur1 = 3;
		y1--;
		carburant1--;
		deplacement--;
		if (deplacement == 0)
		{
			joueur = 2;
			deplacement = 2;
		}
	}

	else if (KGetDown() && joueur == 2 && y2 != 19 && !(x2 == x1 && (y2 + 1) == y1))
	{
		couleur2 = 1;
		y2++;
		carburant2--;
		deplacement--;
		if (deplacement == 0)
		{
			joueur = 1;
			deplacement = 2;
		}
	}
	else if (KGetRight() && joueur == 2 && x2 != 29 && !((x2 + 1) == x1 && y2 == y1))
	{
		couleur2 = 2;
		x2++;
		carburant2--;
		deplacement--;
		if (deplacement == 0)
		{
			joueur = 1;
			deplacement = 2;
		}
	}
	else if (KGetLeft() && joueur == 2 && x2 != 1 && !((x2 - 1) == x1 && y2 == y1))
	{
		couleur2 = 4;
		x2--;
		carburant2--;
		deplacement--;
		if (deplacement == 0)
		{
			joueur = 1;
			deplacement = 2;
		}
	}
	else if (KGetUp() && joueur == 2 && y2 != 1 && !(x2 == x1 && (y2 - 1) == y1))
	{
		couleur2 = 3;
		y2--;
		carburant2--;
		deplacement--;
		if (deplacement == 0)
		{
			joueur = 1;
			deplacement = 2;
		}
	}

	if (carburant1 <= 0 || carburant2 <= 0)
	{
		begin = 1;
		InitialiseGame();
	}
}
// -----------------------------------------------------------


