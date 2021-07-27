

int paragraphe = 1;
int choix = 1;
int Money = 1000;

int Epee = 0;
int Armure = 0;
int Arc = 0;
int Jambiere = 0;
int Bottes = 0;
int Cle = 0;
int Potion = 0;
int Carte = 0;



// -----------------------------------------------------------
void InitialiseGame()
{

}
// -----------------------------------------------------------

/*
- Epée à beurre (200 ducats)
- Armure en carton (400 ducats)
- Arc sans corde (350 ducats)
- Jambière sans alcool (350 ducats)
- Bottes de sept vieux (300 ducats)
- Clé des champs (400 ducats)
- Potion d'ébriété (250 ducats)
- Carte 50cc (200 ducats)
*/




void GameLoop()
{
	if (paragraphe == 1)
	{
		printf("Vous etes dans la rue, en face d'une boutique. Que faites vous?\n");
		printf("1: Vous regardez dans votre sac\n"); // (Allez au Paragraphe 2)
		printf("2: Vous entrez dans la boutique.\n"); // (Allez au Paragraphe 3)
		scanf_s("%d", &choix);
		while (!(choix == 1 || choix == 2))
			scanf_s("%d", &choix);
		if (choix == 1)
			paragraphe = 2;
		if (choix == 2)
			paragraphe = 3;
	}

	if (paragraphe == 2)
	{
		printf("Le sac contient des objets: \n");
		if (Epee == 1)
			printf("Epee a beurre\n");
		if (Armure == 1)
			printf("Armure en carton\n");
		if (Arc == 1)
			printf("Arc sans corde\n");
		if (Jambiere == 1)
			printf("Jambiere sans alcool\n");
		if (Bottes == 1)
			printf("Bottes de sept vieux\n");
		if (Cle == 1)
			printf("Cle des champs\n");
		if (Potion == 1)
			printf("Potion d'ebriete\n");
		if (Carte == 1)
			printf("Carte 50cc\n");
		printf("1: Fermer le sac \n"); // (Allez au Paragraphe 1)
		scanf_s("%d", &choix);
		while (!(choix == 1))
			scanf_s("%d", &choix);
		if (choix == 1)
			paragraphe = 1;
	}

	if (paragraphe == 3)
	{
		printf("Vous entrez dans la boutique.Le marchand vous regarde d'un air mefiant.\n");
		printf("1: Vous demandez a acheter quelque chose\n"); // (Allez au Paragraphe 4)
		printf("2: Vous demandez a vendre quelque chose\n"); // (Allez au Paragraphe 5)
		printf("3: Vous sortez\n"); // (Allez au paragraphe 1)
		scanf_s("%d", &choix);
		while (!(choix == 1 || choix == 2 || choix == 3))
			scanf_s("%d", &choix);
		if (choix == 1)
			paragraphe = 4;
		if (choix == 2)
			paragraphe = 5;
		if (choix == 3)
			paragraphe = 1;
	}

	if (paragraphe == 4)
	{
		printf("Quel article voulez vous acheter ?\n");
		printf("\nMoneyyy: %d\n", Money);
		if (Epee == 0)
			printf("1: Epee a beurre (200 ducats)\n");
		if (Armure == 0)
			printf("2: Armure en carton (400 ducats)\n");
		if (Arc == 0)
			printf("3: Arc sans corde(350 ducats)\n");
		if (Jambiere == 0)
			printf("4: Jambiere sans alcool(350 ducats)\n");
		if (Bottes == 0)
			printf("5: Bottes de sept vieux(300 ducats)\n");
		if (Cle == 0)
			printf("6: Cle des champs(400 ducats)\n");
		if (Potion == 0)
			printf("7: Potion d'ebriete (250 ducats)\n");
		if (Carte == 0)
			printf("8: Carte 50cc(200 ducats)\n");
		printf("9: Fin des achats\n"); // (Allez au paragraphe 3)
		scanf_s("%d", &choix);
		while (!(choix == 1 || choix == 2 || choix == 3 || choix == 4 || choix == 5 || choix == 6 || choix == 7 || choix == 8 || choix == 9))
			scanf_s("%d", &choix);
		if (choix == 1 && Epee == 0 && Money > 200)
		{
			Epee = 1;
			Money = Money - 200;
		}
		else if (choix == 2 && Armure == 0 && Money > 400)
		{
			Armure = 1;
			Money = Money - 400;
		}
		else if (choix == 3 && Arc == 0 && Money > 350)
		{
			Arc = 1;
			Money = Money - 350;
		}
		else if (choix == 4 && Jambiere == 0 && Money > 350)
		{
			Jambiere = 1;
			Money = Money - 350;
		}
		else if (choix == 5 && Bottes == 0 && Money > 300)
		{
			Bottes = 1;
			Money = Money - 300;
		}
		else if (choix == 6 && Cle == 0 && Money > 400)
		{
			Cle = 1;
			Money = Money - 400;
		}
		else if (choix == 7 && Potion == 0 && Money > 250)
		{
			Potion = 1;
			Money = Money - 250;
		}
		else if (choix == 8 && Carte == 0 && Money > 200)
		{
			Carte = 1;
			Money = Money - 200;
		}
		else if (choix == 9)
			paragraphe = 3;
	}

	if (paragraphe ==  5)
	{
		printf("Quel article voulez vous vendre?\n");
		printf("\nMoneyyy: %d\n", Money);
		if (Epee == 1)
			printf("1: Epee a beurre (200 ducats)\n");
		if (Armure == 1)
			printf("2: Armure en carton (400 ducats)\n");
		if (Arc == 1)
			printf("3: Arc sans corde(350 ducats)\n");
		if (Jambiere == 1)
			printf("4: Jambiere sans alcool(350 ducats)\n");
		if (Bottes == 1)
			printf("5: Bottes de sept vieux(300 ducats)\n");
		if (Cle == 1)
			printf("6: Cle des champs(400 ducats)\n");
		if (Potion == 1)
			printf("7: Potion d'ebriete (250 ducats)\n");
		if (Carte == 1)
			printf("8: Carte 50cc(200 ducats)\n");
		printf("9: Fin des achats\n"); // (Allez au paragraphe 3)
		scanf_s("%d", &choix);
		while (!(choix == 1 || choix == 2 || choix == 3 || choix == 4 || choix == 5 || choix == 6 || choix == 7 || choix == 8 || choix == 9))
			scanf_s("%d", &choix);
		if (choix == 1 && Epee == 1)
		{
			Epee = 0;
			Money = Money + 200;
		}
		else if (choix == 2 && Armure == 1)
		{
			Armure = 0;
			Money = Money + 400;
		}
		else if (choix == 3 && Arc == 1)
		{
			Arc = 0;
			Money = Money + 350;
		}
		else if (choix == 4 && Jambiere == 1)
		{
			Jambiere = 0;
			Money = Money + 350;
		}
		else if (choix == 5 && Bottes == 1)
		{
			Bottes = 0;
			Money = Money + 300;
		}
		else if (choix == 6 && Cle == 1)
		{
			Cle = 0;
			Money = Money + 400;
		}
		else if (choix == 7 && Potion == 1)
		{
			Potion = 0;
			Money = Money + 250;
		}
		else if (choix == 8 && Carte == 1)
		{
			Carte = 0;
			Money = Money + 200;
		}
		else if (choix == 9)
			paragraphe = 3;
		
	}


}
// -----------------------------------------------------------

