#include "../Ngck_moteur/Ngck.h"
#include "time.h"
#include "stdlib.h"
#include <windows.h>

#define RESET "\033[0m"
#define YELLOW "\033[33m"
#define RED "\033[91m"
#define GREEN "\033[32m"
#define CYAN "\033[36m"

//Machins importants
FILE _iob[] = { *stdin,*stdout,*stderr };
extern "C" FILE *__cdecl __iob_func(void) { return _iob; }



int paragraphe = 1;
int choix = 1;
int Money = 1000;

char inventaire;


// -----------------------------------------------------------
void InitialiseGame()
{
	inventaire = NULL;
	system("cls");
}
// -----------------------------------------------------------


void GameLoop()
{
	
	/* _____________________________________________________________20/20 svp ( pour que maman soit contente )____________________________________________________________________*/

	if (paragraphe == 1)
	{
		printf("\n");
		printf(RED "Vous etes dans la rue, en face d'une boutique. Que faites vous?\n" RESET);
		printf(GREEN "1: Vous regardez dans votre sac\n"); // (Allez au Paragraphe 2)
		printf("2: Vous entrez dans la boutique.\n" RESET); // (Allez au Paragraphe 3)
		scanf_s("%d", &choix);
		while (!(choix == 1 || choix == 2))
			scanf_s("%d", &choix);
		if (choix == 1)
			paragraphe = 2;
		if (choix == 2)
			paragraphe = 3;
		system("cls");
	}

	if (paragraphe == 2)
	{
		printf("\n");
		printf(RED "Le sac contient des objets: \n" RESET);
		printf(CYAN);
		if (inventaire & (1 << 0))
			printf("Epee a beurre\n");
		if (inventaire & (1 << 1))
			printf("Armure en carton\n");
		if (inventaire & (1 << 2))
			printf("Arc sans corde\n");
		if (inventaire & (1 << 3))
			printf("Jambiere sans alcool\n");
		if (inventaire & (1 << 4))
			printf("Bottes de sept vieux\n");
		if (inventaire & (1 << 5))
			printf("Cle des champs\n");
		if (inventaire & (1 << 6))
			printf("Potion d'ebriete\n");
		if (inventaire & (1 << 7))
			printf("Carte 50cc\n");
		printf(RESET);
		printf(GREEN "1: Fermer le sac \n" RESET); // (Allez au Paragraphe 1)
		scanf_s("%d", &choix);
		while (!(choix == 1))
			scanf_s("%d", &choix);
		if (choix == 1)
			paragraphe = 1;
		system("cls");
	}

	if (paragraphe == 3)
	{
		printf("\n");
		printf(RED "Vous entrez dans la boutique.Le marchand vous regarde d'un air mefiant.\n" RESET);
		printf(GREEN "1: Vous demandez a acheter quelque chose\n"); // (Allez au Paragraphe 4)
		printf("2: Vous demandez a vendre quelque chose\n"); // (Allez au Paragraphe 5)
		printf("3: Vous sortez\n" RESET); // (Allez au paragraphe 1)
		scanf_s("%d", &choix);
		while (!(choix == 1 || choix == 2 || choix == 3))
			scanf_s("%d", &choix);
		if (choix == 1)
			paragraphe = 4;
		if (choix == 2)
			paragraphe = 5;
		if (choix == 3)
			paragraphe = 1;
		system("cls");
	}

	if (paragraphe == 4)
	{
		printf("\n");
		printf(RED "Quel article voulez vous acheter ?\n" RESET);
		printf(YELLOW "\nMoneyyy: %d ducats\n\n" RESET, Money);
		printf(GREEN);
		if (!(inventaire & (1 << 0)))
			printf("1: Epee a beurre (200 ducats)\n");
		if (!(inventaire & (1 << 1)))
			printf("2: Armure en carton (400 ducats)\n");
		if (!(inventaire & (1 << 2)))
			printf("3: Arc sans corde(350 ducats)\n");
		if (!(inventaire & (1 << 3)))
			printf("4: Jambiere sans alcool(350 ducats)\n");
		if (!(inventaire & (1 << 4)))
			printf("5: Bottes de sept vieux(300 ducats)\n");
		if (!(inventaire & (1 << 5)))
			printf("6: Cle des champs(400 ducats)\n");
		if (!(inventaire & (1 << 6)))
			printf("7: Potion d'ebriete (250 ducats)\n");
		if (!(inventaire & (1 << 7)))
			printf("8: Carte 50cc(200 ducats)\n");
		printf("9: Fin des achats\n"); // (Allez au paragraphe 3)
		printf(RESET);
		scanf_s("%d", &choix);
		while (!(choix == 1 || choix == 2 || choix == 3 || choix == 4 || choix == 5 || choix == 6 || choix == 7 || choix == 8 || choix == 9))
			scanf_s("%d", &choix);
		if (choix == 1 && !(inventaire & (1 << 0)) && Money > 200)
		{
			inventaire = inventaire | (1 << 0);
			Money = Money - 200;
		}
		else if (choix == 2 && !(inventaire & (1 << 1)) && Money > 400)
		{
			inventaire = inventaire | (1 << 1);
			Money = Money - 400;
		}
		else if (choix == 3 && !(inventaire & (1 << 2)) && Money > 350)
		{
			inventaire = inventaire | (1 << 2);
			Money = Money - 350;
		}
		else if (choix == 4 && !(inventaire & (1 << 3)) && Money > 350)
		{
			inventaire = inventaire | (1 << 3);
			Money = Money - 350;
		}
		else if (choix == 5 && !(inventaire & (1 << 4)) && Money > 300)
		{
			inventaire = inventaire | (1 << 4);
			Money = Money - 300;
		}
		else if (choix == 6 && !(inventaire & (1 << 5)) && Money > 400)
		{
			inventaire = inventaire | (1 << 5);
			Money = Money - 400;
		}
		else if (choix == 7 && !(inventaire & (1 << 6)) && Money > 250)
		{
			inventaire = inventaire | (1 << 6);
			Money = Money - 250;
		}
		else if (choix == 8 && !(inventaire & (1 << 7)) && Money > 200)
		{
			inventaire = inventaire | (1 << 7);
			Money = Money - 200;
		}
		else if (choix == 9)
			paragraphe = 3;
		system("cls");
	}

	if (paragraphe ==  5)
	{
		printf("\n");
		printf(RED "Quel article voulez vous vendre?\n" RESET);
		printf(YELLOW "\nMoneyyy: %d ducats\n\n" RESET, Money);
		printf(GREEN);
		if (inventaire & (1 << 0))
			printf("1: Epee a beurre (200 ducats)\n");
		if (inventaire & (1 << 1))
			printf("2: Armure en carton (400 ducats)\n");
		if (inventaire & (1 << 2))
			printf("3: Arc sans corde(350 ducats)\n");
		if (inventaire & (1 << 3))
			printf("4: Jambiere sans alcool(350 ducats)\n");
		if (inventaire & (1 << 4))
			printf("5: Bottes de sept vieux(300 ducats)\n");
		if (inventaire & (1 << 5))
			printf("6: Cle des champs(400 ducats)\n");
		if (inventaire & (1 << 6))
			printf("7: Potion d'ebriete (250 ducats)\n");
		if (inventaire & (1 << 7))
			printf("8: Carte 50cc(200 ducats)\n");
		printf("9: Fin des achats\n"); // (Allez au paragraphe 3)
		printf(RESET);
		scanf_s("%d", &choix);
		while (!(choix == 1 || choix == 2 || choix == 3 || choix == 4 || choix == 5 || choix == 6 || choix == 7 || choix == 8 || choix == 9))
			scanf_s("%d", &choix);
		if (choix == 1 && (inventaire & (1 << 0)))
		{
			inventaire = inventaire & ~(1 << 0);
			Money = Money + 200;
		}
		else if (choix == 2 && (inventaire & (1 << 1)))
		{
			inventaire = inventaire & ~(1 << 1);
			Money = Money + 400;
		}
		else if (choix == 3 && (inventaire & (1 << 2)))
		{
			inventaire = inventaire & ~(1 << 2);
			Money = Money + 350;
		}
		else if (choix == 4 && (inventaire & (1 << 3)))
		{
			inventaire = inventaire & ~(1 << 3);
			Money = Money + 350;
		}
		else if (choix == 5 && (inventaire & (1 << 4)))
		{
			inventaire = inventaire & ~(1 << 4);
			Money = Money + 300;
		}
		else if (choix == 6 && (inventaire & (1 << 5)))
		{
			inventaire = inventaire & ~(1 << 5);
			Money = Money + 400;
		}
		else if (choix == 7 && (inventaire & (1 << 6)))
		{
			inventaire = inventaire & ~(1 << 6);
			Money = Money + 250;
		}
		else if (choix == 8 && (inventaire & (1 << 7)))
		{
			inventaire = inventaire & ~(1 << 7);
			Money = Money + 200;
		}
		else if (choix == 9)
			paragraphe = 3;
		system("cls");
	}


}
// -----------------------------------------------------------


