// ProjetType.cpp : définit le point d'entrée pour l'application console.
//


#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "windows.h"
#include <string.h>

#define MOT 5
#define RESET "\033[0m"
#define RED "\033[91m"





void main()
{
	srand((unsigned int)time(NULL));

	char dico[MOT][27] = { {"tulipe"} ,{"panda"} ,{"giletjaune"} ,{"coucou"} ,{"programmation"} };
	char str[27];
	char str2[27];
	int i = 0;
	char lettre;
	int end = 0;
	char temp[100] = { 0 };
	int vie = 10;
	int win = 0;

	strcpy(str, dico[rand() % MOT]);


	system("cls");
	printf(RED"\n\n\n\n\n                                                        Vie: %d\n"RESET, vie);
	printf("\n                                                     ");
	for (i = 0; str[i] != '\0'; i++)
	{
		str2[i] = '_';
		printf("%c", str2[i]);
		printf(" ");
	}
	str2[i] = '\0';
	printf("\n");
	//printf("%s\n", str2);




	while (end == 0 && vie > 0)
	{
		printf("\n                                           lettre: ");
		gets(temp);
		lettre = temp[0];
		system("cls");
		win = 0;
		for (int j = 0; str[j] != '\0'; j++)
		{
			if (lettre == str[j])
			{
				str2[j] = str[j];
				win = 1;
			}
		}
		if (win == 0)
		{
			vie--;
		}
		win = 0;
		end = 1;
		printf(RED"\n\n\n\n\n                                                        Vie: %d\n"RESET, vie);
		printf("\n                                                     ");
		for (int j = 0; str2[j] != '\0'; j++)
		{
			if (str2[j] == '_')
			{
				end = 0;
			}
			printf("%c", str2[j]);
			printf(" ");
		}
		//printf(RED"\nVie: %d\n"RESET, vie);
		printf("\n");
		//printf("%s\n", str2);
	}
	
	if (vie <= 0)
	{
		printf("\n\n\n\n\n                                                       PERDU !!\n\n\n\n\n\n");
	}
	if (end == 1)
	{
		printf("\n\n\n\n\n                                                       GAGNE !!\n\n\n\n\n\n");
	}

}