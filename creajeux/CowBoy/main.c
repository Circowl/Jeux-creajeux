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
#include <SFML/Graphics/Rect.h>

sfRenderWindow* window = 0;
sfTime temps;
sfClock* horloge = 0;
sfClock* horloge1 = 0;
sfClock* horloge2 = 0;
sfClock* horloge3 = 0;

sfEvent event;

sfMusic* musique = 0;

sfSprite* MortDroite;
sfSprite* MortGauche;
sfSprite* cactus;
sfSprite* Boy;
sfSprite* Mort;
sfSprite* Un;
sfSprite* Deux;
sfSprite* Trois;
sfSprite* Bang;
sfSprite* gris;
sfSprite* tir;
sfSprite* Paille;

sfSound* STrois;
sfSound* SDeux;
sfSound* SUn;
sfSound* SBang;
sfSound* BangTir;


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

sfSound* LoadSon(char* nom)
{
	sfSound* son = 0;
	sfSoundBuffer* buffer = 0;

	buffer = sfSoundBuffer_createFromFile(nom); //Chargement des données du son
	son = sfSound_create(); //création du son
	sfSound_setBuffer(son, buffer); //Assignation des données du fichier au son
	return (son);
}


int _tmain(int argc, _TCHAR* argv[])
{

	sfVideoMode mode = { 1280, 800, 32 };
	window = sfRenderWindow_create(mode, "3 2 1 BANG", sfResize | sfClose, NULL);
	srand((unsigned int)time(NULL));

	sfFont* font = sfFont_createFromFile("CarnevaleeFreakshow.ttf");
	FILE * pFile;

	int end = 1;

	char str[100] = "";

	int perso1 = 1;
	int perso2 = 1;
	int perso3 = 1;

	int animation1 = 0;
	int animation2 = 0;
	int animation3 = 0;

	int vie1 = 5;
	int vie2 = 5;
	int vie3 = 5;

	int win1 = 0;
	int win2 = 0;
	int win3 = 0;
	float vitesse = 0;
	float record = 100;

	pFile = fopen("myfile.txt", "r");
	if (pFile != NULL)
	{
		fscanf(pFile, "%f", &record);
		printf("%f", record);
	}
	fclose(pFile);


	float go = 0;

	int son1 = 0;
	int son2 = 0;
	int son3 = 0;
	int son4 = 0;
	int stop1 = 0;
	int stop2 = 0;
	int stop3 = 0;
	int stop4 = 0;

	float time1x = 0;
	float time2x = 0;
	float time3x = 0;

	float paillex = -1500;
	float pailley = rand() % 510 + 270;
	float rotation = 0.1;

	horloge = sfClock_create();
	horloge1 = sfClock_create();
	horloge2 = sfClock_create();
	horloge3 = sfClock_create();

	MortGauche = LoadSprite("dieLeft.png", 0);
	MortDroite = LoadSprite("dieRight.png", 0);
	cactus = LoadSprite("cactus.png", 0);
	gris = LoadSprite("mapClement.jpg", 0);
	Boy = LoadSprite("Boy1.png", 1);
	tir = LoadSprite("Boy2.png", 1);
	Mort = LoadSprite("mort.png", 1);
	Un = LoadSprite("1.png", 1);
	Deux = LoadSprite("2.png", 1);
	Trois = LoadSprite("3.png", 1);
	Bang = LoadSprite("Bang.png", 1);
	Paille = LoadSprite("paille.png", 1);

	STrois = LoadSon("3.wav");
	SDeux = LoadSon("2.wav");
	SUn = LoadSon("1.wav");
	SBang = LoadSon("bang2.wav");
	BangTir = LoadSon("bang.wav");

	/*sfSound_setVolume(STrois, 50);
	sfSound_setVolume(SDeux, 50);
	sfSound_setVolume(SUn, 50);*/
	sfSound_setVolume(SBang, 50);

	musique = sfMusic_createFromFile("western.wav"); //Chargement à partir du fichier
	sfMusic_setVolume(musique, 100); //Volume réduit de moitié (sur 100)
	sfMusic_setLoop(musique, 1); //Lecture en boucle
	sfMusic_play(musique); //Lancement de la musique

	while (sfRenderWindow_isOpen(window))
	{

		while (sfRenderWindow_pollEvent(window, &event))
		{
			if (event.type == sfEvtClosed) exit(0); //Fermeture en appuyant sur le bouton Fermer

			if (event.type == sfEvtKeyPressed)
			{
				if (event.key.code == sfKeyR)
				{
					record = 100;
				}
				/*if (event.key.code == sfKeyW)
				{
				keybd_event('Delete', 0, 0, 0);
				}*/
				if (event.key.code == sfKeyReturn)
				{
					animation1 = 0;
					animation2 = 0;
					animation3 = 0;
					son1 = 0;
					son2 = 0;
					son3 = 0;
					son4 = 0;
					stop1 = 0;
					stop2 = 0;
					stop3 = 0;
					stop4 = 0;
					end = 0;
					sfClock_restart(horloge);
					win1 = 0;
					win2 = 0;
					win3 = 0;
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
					sfSound_play(BangTir);
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
						{
							record = vitesse;
							pFile = fopen("myfile.txt", "w");
							if (pFile != NULL)
							{
								snprintf(str, 100, "%f", record);
								printf("%s", str);
								fputs(str, pFile);
							}
							fclose(pFile);
						}
						win1 = 1;
					}
				}
				if (event.key.code == sfKeySpace && end == 0)
				{
					sfSound_play(BangTir);
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
						{
							record = vitesse;
							pFile = fopen("myfile.txt", "w");
							if (pFile != NULL)
							{
								snprintf(str, 100, "%f", record);
								printf("%s", str);
								fputs(str, pFile);
							}
							fclose(pFile);
						}
						win2 = 1;
					}
				}
				if (event.key.code == sfKeyNumpad0 && end == 0)
				{
					sfSound_play(BangTir);
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
						{
							record = vitesse;
							pFile = fopen("myfile.txt", "w");
							if (pFile != NULL)
							{
								snprintf(str, 100, "%f", record);
								printf("%s", str);
								fputs(str, pFile);
							}
							fclose(pFile);
						}
						win3 = 1;
					}
				}
			}
		}

		if (perso1 == 0 && perso2 == 0 && perso3 == 0)
			end = 1;

		sfRenderWindow_clear(window, sfWhite);

		BlitSprite(gris, 0, 0, window);

		if (son1 == 1 && stop1 == 0)
		{
			sfSound_play(STrois);
			stop1 = 1;
		}
		if (son2 == 1 && stop2 == 0)
		{
			sfSound_play(SDeux);
			stop2 = 1;
		}
		if (son3 == 1 && stop3 == 0)
		{
			sfSound_play(SUn);
			stop3 = 1;
		}
		if (son4 == 1 && stop4 == 0)
		{
			sfSound_play(SBang);
			stop4 = 1;
		}

		if (sfTime_asSeconds(sfClock_getElapsedTime(horloge)) >= 0 && sfTime_asSeconds(sfClock_getElapsedTime(horloge)) < 1 && end == 0)
		{
			BlitSprite(Trois, 640, 400, window);
			son1 = 1;
		}
		if (sfTime_asSeconds(sfClock_getElapsedTime(horloge)) >= 1 && sfTime_asSeconds(sfClock_getElapsedTime(horloge)) < 2 && end == 0)
		{
			BlitSprite(Deux, 640, 400, window);
			son2 = 1;
		}
		if (sfTime_asSeconds(sfClock_getElapsedTime(horloge)) >= 2 && sfTime_asSeconds(sfClock_getElapsedTime(horloge)) < 3 && end == 0)
		{
			BlitSprite(Un, 640, 400, window);
			son3 = 1;
		}
		if (sfTime_asSeconds(sfClock_getElapsedTime(horloge)) >= go && sfTime_asSeconds(sfClock_getElapsedTime(horloge)) < 11 && end == 0)
		{
			BlitSprite(Bang, 640, 400, window);
			son4 = 1;
		}
		if (sfTime_asSeconds(sfClock_getElapsedTime(horloge)) > 13)
			end = 1;


		if (perso1 == 1 && win1 == 0)
			BlitSprite(Boy, 200, 250, window);
		else if (perso1 == 1 && win1 == 1)
			BlitSprite(tir, 200, 250, window);
		else
		{
			if (animation1 == 0)
			{
				sfClock_restart(horloge1);
				animation1 = 1;
			}
			if (sfTime_asSeconds(sfClock_getElapsedTime(horloge1)) <= 0.05 && sfTime_asSeconds(sfClock_getElapsedTime(horloge1)) > 0)
			{
				time1x = 600;
			}
			if (sfTime_asSeconds(sfClock_getElapsedTime(horloge1)) <= 0.1 && sfTime_asSeconds(sfClock_getElapsedTime(horloge1)) > 0.05)
			{
				time1x = 450;
			}
			if (sfTime_asSeconds(sfClock_getElapsedTime(horloge1)) <= 0.15 && sfTime_asSeconds(sfClock_getElapsedTime(horloge1)) > 0.1)
			{
				time1x = 300;
			}
			if (sfTime_asSeconds(sfClock_getElapsedTime(horloge1)) <= 0.2 && sfTime_asSeconds(sfClock_getElapsedTime(horloge1)) > 0.15)
			{
				time1x = 150;
			}
			if (sfTime_asSeconds(sfClock_getElapsedTime(horloge1)) > 0.2)
			{
				time1x = 0;
			}
			sfIntRect rectSprite = { time1x,0,150,150 };
			sfSprite_setTextureRect(MortGauche, rectSprite);
			BlitSprite(MortGauche, 125, 175, window);
		}


		if (perso3 == 1 && win3 == 0)
			BlitSprite(Boy, 1080, 200, window);
		else if (perso3 == 1 && win3 == 1)
			BlitSprite(tir, 1080, 200, window);
		else
		{
			if (animation3 == 0)
			{
				sfClock_restart(horloge3);
				animation3 = 1;
			}
			if (sfTime_asSeconds(sfClock_getElapsedTime(horloge3)) <= 0.05 && sfTime_asSeconds(sfClock_getElapsedTime(horloge3)) > 0)
			{
				time3x = 0;
			}
			if (sfTime_asSeconds(sfClock_getElapsedTime(horloge3)) <= 0.1 && sfTime_asSeconds(sfClock_getElapsedTime(horloge3)) > 0.05)
			{
				time3x = 150;
			}
			if (sfTime_asSeconds(sfClock_getElapsedTime(horloge3)) <= 0.15 && sfTime_asSeconds(sfClock_getElapsedTime(horloge3)) > 0.1)
			{
				time3x = 300;
			}
			if (sfTime_asSeconds(sfClock_getElapsedTime(horloge3)) <= 0.2 && sfTime_asSeconds(sfClock_getElapsedTime(horloge3)) > 0.15)
			{
				time3x = 450;
			}
			if (sfTime_asSeconds(sfClock_getElapsedTime(horloge3)) > 0.2)
			{
				time3x = 600;
			}
			sfIntRect rectSprite = { time3x,0,150,150 };
			sfSprite_setTextureRect(MortDroite, rectSprite);
			BlitSprite(MortDroite, 1015, 125, window);
		}


		if (pailley < 600 && pailley >= 250)
			BlitSprite(Paille, paillex, pailley, window);

		BlitSprite(cactus, 0, 0, window);

		if (perso2 == 1 & win2 == 0)
			BlitSprite(Boy, 640, 600, window);
		else if (perso2 == 1 && win2 == 1)
			BlitSprite(tir, 640, 600, window);
		else
		{
			if (animation2 == 0)
			{
				sfClock_restart(horloge2);
				animation2 = 1;
			}
			if (sfTime_asSeconds(sfClock_getElapsedTime(horloge2)) <= 0.05 && sfTime_asSeconds(sfClock_getElapsedTime(horloge2)) > 0)
			{
				if (win1 == 1)
					time2x = 0;
				else
					time2x = 600;
			}
			if (sfTime_asSeconds(sfClock_getElapsedTime(horloge2)) <= 0.1 && sfTime_asSeconds(sfClock_getElapsedTime(horloge2)) > 0.05)
			{
				if (win1 == 1)
					time2x = 150;
				else
					time2x = 450;
			}
			if (sfTime_asSeconds(sfClock_getElapsedTime(horloge2)) <= 0.15 && sfTime_asSeconds(sfClock_getElapsedTime(horloge2)) > 0.1)
			{
				time2x = 300;
			}
			if (sfTime_asSeconds(sfClock_getElapsedTime(horloge2)) <= 0.2 && sfTime_asSeconds(sfClock_getElapsedTime(horloge2)) > 0.15)
			{
				if (win1 == 1)
					time2x = 450;
				else
					time2x = 150;
			}
			if (sfTime_asSeconds(sfClock_getElapsedTime(horloge2)) > 0.2)
			{
				if (win1 == 1)
					time2x = 600;
				else
					time2x = 0;
			}
			sfIntRect rectSprite = { time2x,0,150,150 };
			if (win1 == 1)
			{
				sfSprite_setTextureRect(MortDroite, rectSprite);
				BlitSprite(MortDroite, 565, 525, window);
			}
			else
			{
				sfSprite_setTextureRect(MortGauche, rectSprite);
				BlitSprite(MortGauche, 565, 525, window);
			}

		}

		if (pailley >= 600)
			BlitSprite(Paille, paillex, pailley, window);

		if (end == 1)
		{
			BlitInt(font, vie1, 190, 320, window);
			BlitInt(font, vie2, 630, 670, window);
			BlitInt(font, vie3, 1070, 270, window);
			BlitFloat(font, vitesse, 1100, 700, window);
			if (record < 100)
				BlitRecord(font, record, 100, 700, window);
		}

		if (paillex >= 1500)
		{
			paillex = -1500;
			pailley = rand() % 510 + 270;
		}
		sfSprite_setRotation(Paille, rotation);
		rotation = rotation + 0.1;
		paillex = paillex + 0.1;


		sfRenderWindow_display(window);
	}

	return 0;
}
