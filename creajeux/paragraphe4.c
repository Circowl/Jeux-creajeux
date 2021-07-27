#include "../Ngck_moteur/Ngck.h"
#include "time.h"
#include "stdlib.h"
#include <windows.h>

#define RESET "\033[0m"
#define YELLOW "\033[33m"
#define RED "\033[91m"
#define GREEN "\033[32m"
#define CYAN "\033[36m"
#define MAGENTA "\033[95m"

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
	system("cls");
	printf(MAGENTA "\n\n\nSa majeste Pierre 1er du nom, terreur des bugs informatiques, s'apprete a partir pour une grande quete.\n Cependant, afin de braver les etudiants de premiere annee, il doit d'abord faire son sac, \n et possede la somme de mille boulas.\n Apres une longue marche sous la pluie, il arrive en face du snack de Creajeux,\n premiere etape de son long periple...\n\n" RESET);
	inventaire = NULL;
	printf(GREEN "\n\n1: ok\n" RESET);
	scanf_s("%d", &choix);
	while (!(choix == 1))
		scanf_s("%d", &choix);
	system("cls");
}
// -----------------------------------------------------------


void GameLoop()
{
	
	/* _____________________________________________________________20/20 svp ( pour que maman soit contente )____________________________________________________________________*/

	if (paragraphe == 1)
	{
		printf("\n");
		printf(RED "Vous recroisez quelques eleves en face du snack. Que faites vous?\n" RESET);
		printf(GREEN "1: Vous regardez dans votre sac\n"); // (Allez au Paragraphe 2)
		printf("2: Vous passez devant tout le monde parce que vous etes un etre malefique.\n"); // (Allez au Paragraphe 3)
		printf("3: Vous les frappez pour le plaisir.\n" RESET);
		scanf_s("%d", &choix);
		while (!(choix == 1 || choix == 2 || choix == 3))
			scanf_s("%d", &choix);
		if (choix == 1)
			paragraphe = 2;
		if (choix == 2)
			paragraphe = 3;
		if (choix == 3)
			paragraphe = 6;
		system("cls");
	}

	if (paragraphe == 2)
	{
		printf("\n");
		printf(RED "Le sac contient des choses: \n" RESET);
		printf(CYAN);
		if (inventaire & (1 << 0))
			printf("Ice tea citron\n");
		if (inventaire & (1 << 1))
			printf("Maxi burger bacon\n");
		if (inventaire & (1 << 2))
			printf("Batte de Baseball\n");
		if (inventaire & (1 << 3))
			printf("La lumiere du jour\n");
		if (inventaire & (1 << 4))
			printf("Mamie Gertrude\n");
		if (inventaire & (1 << 5))
			printf("42\n");
		if (inventaire & (1 << 6))
			printf("Codes nucleaires\n");
		if (inventaire & (1 << 7))
			printf("Jeu pc: Goat simulator\n");
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
		printf(RED "Vous arrivez au guichet du snack.Le marchand vous tape un check.\n" RESET);
		printf(GREEN "1: Vous demandez a acheter quelque chose\n"); // (Allez au Paragraphe 4)
		printf("2: Vous demandez a vendre quelque chose\n"); // (Allez au Paragraphe 5)
		printf("3: Vous partez\n" RESET); // (Allez au paragraphe 1)
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
		printf(YELLOW "\nMoneyyy: %d boulas\n\n" RESET, Money);
		printf(GREEN);
		if (!(inventaire & (1 << 0)))
			printf("1: Ice tea citron (200 boulas)\n");
		if (!(inventaire & (1 << 1)))
			printf("2: Maxi burger bacon (400 boulas)\n");
		if (!(inventaire & (1 << 2)))
			printf("3: Batte de Baseball (350 boulas)\n");
		if (!(inventaire & (1 << 3)))
			printf("4: La lumiere du jour (350 boulas)\n");
		if (!(inventaire & (1 << 4)))
			printf("5: Mamie Gertrude (300 boulas)\n");
		if (!(inventaire & (1 << 5)))
			printf("6: 42 (400 boulas)\n");
		if (!(inventaire & (1 << 6)))
			printf("7: Codes nucleaires (250 boulas)\n");
		if (!(inventaire & (1 << 7)))
			printf("8: Jeu pc: Goat simulator (200 boulas)\n");
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
		printf(YELLOW "\nMoneyyy: %d boulas\n\n" RESET, Money);
		printf(GREEN);
		if (inventaire & (1 << 0))
			printf("1: Ice tea citron (200 ducats)\n");
		if (inventaire & (1 << 1))
			printf("2: Maxi burger bacon (400 ducats)\n");
		if (inventaire & (1 << 2))
			printf("3: Batte de Baseball (350 ducats)\n");
		if (inventaire & (1 << 3))
			printf("4: La lumiere du jour (350 ducats)\n");
		if (inventaire & (1 << 4))
			printf("5: Mamie Gertrude (300 ducats)\n");
		if (inventaire & (1 << 5))
			printf("6: 42 (400 ducats)\n");
		if (inventaire & (1 << 6))
			printf("7: Codes nucleaires (250 ducats)\n");
		if (inventaire & (1 << 7))
			printf("8: Jeu pc: Goat simulator (200 ducats)\n");
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
	
	if (paragraphe == 6)
	{
		printf("\n");
		printf(RED "\n Pfffiou ca fait du bien\n" RESET);
		printf(GREEN "1: Vous continuez de les massacrer jusqu'a la mort\n");
		printf("2: Vous leur donnez un bescherelle d'anglais et vous retournez devant le snack\n" RESET);
		scanf_s("%d", &choix);
		while (!(choix == 1 || choix == 2))
			scanf_s("%d", &choix);
		if (choix == 1)
			paragraphe = 7;
		if (choix == 2)
			paragraphe = 1;
		system("cls");
	}

	if (paragraphe == 7)
	{
		printf("\n");
		printf(RED "\n Vous urinez sur leurs cadavres\n" RESET);
		printf(GREEN "1: Vous retournez devant le snack\n" RESET);
		scanf_s("%d", &choix);
		while (!(choix == 1))
			scanf_s("%d", &choix);
		if (choix == 1)
			paragraphe = 1;
		system("cls");
	}

}
// -----------------------------------------------------------


