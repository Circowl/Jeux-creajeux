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
#include <math.h>

sfRenderWindow* window = 0;
sfTime temps;
sfClock* horloge = 0;


sfMusic* musique = 0;




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


void BlitSprite(sfSprite* Sprite, float x, float y, float rotation, sfRenderWindow* window)
{
	sfVector2f tempPosition = { x, y };
	sfSprite_setPosition(Sprite, tempPosition);
	sfRenderWindow_drawSprite(window, Sprite, NULL);
	sfSprite_setRotation(Sprite, rotation);
}

void BlitSpriteRect(sfSprite* Sprite, float x, float y, float rotation, int pourcentage, sfRenderWindow* window)
{
	sfVector2f tempPosition = { x, y };
	sfSprite_setPosition(Sprite, tempPosition);

	sfSprite_setTextureRect(Sprite, (sfIntRect) {0, 0, pourcentage, 30});

	sfRenderWindow_drawSprite(window, Sprite, NULL);
	sfSprite_setRotation(Sprite, rotation);
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


sfSound* LoadSon(char* nom)
{
	sfSound* son = 0;
	sfSoundBuffer* buffer = 0;

	buffer = sfSoundBuffer_createFromFile(nom);
	son = sfSound_create();
	sfSound_setBuffer(son, buffer);
	return (son);
}





int _tmain(int argc, _TCHAR* argv[])
{

	sfVideoMode mode = { 1280, 800, 32 };
	window = sfRenderWindow_create(mode, "Test", sfResize | sfClose, NULL);
	srand((unsigned int)time(NULL));
	
	sfSprite* sperm;
	sfSprite* fond;
	sfSprite* ovule;
	sfSprite* mst;
	sfSprite* splash;
	sfSprite* txt;
	sfSprite* victoire;
	sfSprite* life;
	sfSprite* energy;
	sfSprite* defaite;


	int phase = 0;
	int win1 = 0;
	int win2 = 0;

	float barreLife = 200;
	float barreEnergy = 200;


	sperm = LoadSprite("mesper/sperm.png", 1);
	fond = LoadSprite("mesper/fond.png", 0);
	ovule = LoadSprite("mesper/ovule.png", 1);
	mst = LoadSprite("mesper/mst.png", 1);
	splash = LoadSprite("mesper/splash2.png", 1);
	txt = LoadSprite("mesper/txt.png", 1);
	victoire = LoadSprite("mesper/victoire.png", 0);
	life = LoadSprite("mesper/Life.png", 0);
	energy = LoadSprite("mesper/energy.png", 0);
	defaite = LoadSprite("mesper/defaite.png", 0);
	
	float SplashY = rand() % 680 + 60;
	float OvuleY = rand() % 680 + 60;

	float SpermX = 80;
	float SpermY = SplashY;
	float vitesseX = 0.02;
	float vitesseY = 0.02;
	float SpermRot = 0;

	float vitesseOvule = 0.02;
	float vitesseSplash = 0.02;

	int collision = 0;
	int perdu = 0;

	float tab[50][6];
	int nombre_mst = 48;

	for (int i = 0; i < 50; i++)
	{
		tab[i][0] = rand() % 1280;
		tab[i][1] = rand() % 800;
		tab[i][2] = (rand() % 14 - 7) / 100.0;
		tab[i][3] = (rand() % 14 - 7) / 100.0;
		tab[i][4] = (rand() % 8) / 100.0;
		tab[i][5] = 0;
	}


	horloge = sfClock_create();


	//sfSound_setVolume(STrois, 50);


	musique = sfMusic_createFromFile("western.wav"); //Chargement à partir du fichier
	sfMusic_setVolume(musique, 100); //Volume réduit de moitié (sur 100)
	sfMusic_setLoop(musique, 1); //Lecture en boucle
	sfMusic_play(musique); //Lancement de la musique

	while (sfRenderWindow_isOpen(window))
	{
		sfEvent event;
		while (sfRenderWindow_pollEvent(window, &event))
		{
			if (event.type == sfEvtClosed) exit(0); //Fermeture en appuyant sur le bouton Fermer

			if (event.type == sfEvtKeyPressed && barreEnergy > 0)
			{
				if (win1 == 0 && win2 == 0 && !(SpermX < 120 && SpermX > 40 && SpermY < (SplashY + 40) && SpermY >(SplashY - 40)))
				{
					barreEnergy = barreEnergy - 5;
				}
				if (event.key.code == sfKeyUp)
				{
					vitesseY = vitesseY - 0.04;
				}
				if (event.key.code == sfKeyDown)
				{
					vitesseY = vitesseY + 0.04;
				}
				if (event.key.code == sfKeyLeft)
				{
					vitesseX = vitesseX - 0.04;
				}
				if (event.key.code == sfKeyRight)
				{
					vitesseX = vitesseX + 0.04;
				}
			}
		}

		for (int b = 0; b < nombre_mst; b++)
		{
			if (SpermX <= (tab[b][0] + 80) && SpermX >= (tab[b][0] - 80) && SpermY <= (tab[b][1] + 80) && SpermY >= (tab[b][1] - 80))
			{
				collision = 1;
			}
		}

		if (win1 == 0 && win2 == 0)
		{
			if (collision == 0)
				barreLife = barreLife - 0.003;
			else
				barreLife = barreLife - 0.015;
		}
		if (SpermX < 120 && SpermX > 40 && SpermY < (SplashY + 40) && SpermY >(SplashY - 40))
		{
			barreEnergy = 200;
			barreLife = 200;
		}

		collision = 0;


		if (OvuleY <= 740 && OvuleY >= 60)
		{
			OvuleY = OvuleY + vitesseOvule;
		}
		else
		{
			OvuleY = OvuleY - vitesseOvule;
			vitesseOvule = -vitesseOvule;
		}

		if (SplashY <= 740 && SplashY >= 60)
		{
			SplashY = SplashY + vitesseSplash;
		}
		else
		{
			SplashY = SplashY - vitesseSplash;
			vitesseSplash = -vitesseSplash;
		}

		if (phase == 0)
		{
			if (SpermX < 1190 && SpermX > 1110 && SpermY < (OvuleY + 40) && SpermY >(OvuleY - 40) && (fabs(vitesseX) + fabs(vitesseY)) < 0.2)
			{
				phase = 1;
				SpermRot = 180;
				win1 = 1;
				sfClock_restart(horloge);
			}
		}
		if (phase == 1)
		{
			if (SpermX < 120 && SpermX > 40 && SpermY < (SplashY + 40) && SpermY >(SplashY - 40) && (fabs(vitesseX) + fabs(vitesseY)) < 0.2)
			{
				phase = 0;
				SpermRot = 0;
				win2 = 1;
				sfClock_restart(horloge);
				nombre_mst = nombre_mst + 2;
			}
		}

		if (win1 == 1)
		{
			if (sfTime_asSeconds(sfClock_getElapsedTime(horloge)) < 5)
			{
				SpermX = 1150;
				SpermY = OvuleY;
			}
			else
			{
				win1 = 0;
			}
			vitesseX = -0.02;
			vitesseY = -0.02;
		}

		if (win2 == 1)
		{
			if (sfTime_asSeconds(sfClock_getElapsedTime(horloge)) < 5)
			{
				SpermX = 80;
				SpermY = SplashY;
			}
			else
			{
				barreEnergy = 200;
				barreLife = 200;
				win2 = 0;
			}
			vitesseX = 0.02;
			vitesseY = 0.02;
		}
		
		

		SpermX = SpermX + vitesseX;
		SpermY = SpermY + vitesseY;
		for (int j = 0; j < 50; j++)
		{
			tab[j][0] = tab[j][0] + tab[j][2];
			if (tab[j][0] < -100)
			{
				tab[j][0] = 1380;
			}
			else if (tab[j][0] > 1380)
			{
				tab[j][0] = -100;
			}
			tab[j][1] = tab[j][1] + tab[j][3];
			if (tab[j][1] < -100)
			{
				tab[j][1] = 900;
			}
			else if (tab[j][1] > 900)
			{
				tab[j][1] = -100;
			}
			tab[j][5] = tab[j][5] + tab[j][4];
		}

		/*printf("%f\n", SpermX);
		printf("%f\n", SpermY);*/

		if (barreLife < 0)
		{
			perdu = 1;
		}

		sfRenderWindow_clear(window, sfWhite);

		BlitSprite(fond, 0, 0, 0, window);
		BlitSprite(ovule, 1150, OvuleY, 0, window);
		BlitSprite(splash, 80, SplashY, 0, window);
		BlitSprite(sperm, SpermX, SpermY, SpermRot, window);
		for (int a = 0; a < nombre_mst; a++)
		{
			BlitSprite(mst, tab[a][0], tab[a][1], tab[a][5], window);
		}
		if (win1 == 1)
		{
			if (sfTime_asSeconds(sfClock_getElapsedTime(horloge)) < 5 && sfTime_asSeconds(sfClock_getElapsedTime(horloge)) >= 4)
				BlitSprite(txt, 1150, OvuleY - 100, 0, window);
			if (sfTime_asSeconds(sfClock_getElapsedTime(horloge)) < 3.5 && sfTime_asSeconds(sfClock_getElapsedTime(horloge)) >= 2.5)
				BlitSprite(txt, 1150, OvuleY - 100, 0, window);
			if (sfTime_asSeconds(sfClock_getElapsedTime(horloge)) < 2 && sfTime_asSeconds(sfClock_getElapsedTime(horloge)) >= 1)
				BlitSprite(txt, 1150, OvuleY - 100, 0, window);
			if (sfTime_asSeconds(sfClock_getElapsedTime(horloge)) < 0.5 && sfTime_asSeconds(sfClock_getElapsedTime(horloge)) >= 0)
				BlitSprite(txt, 1150, OvuleY - 100, 0, window);
		}

		BlitSpriteRect(life, 200, 20, 0, (int)barreLife, window);
		BlitSpriteRect(energy, 200, 60, 0, (int)barreEnergy, window);

		if (win2 == 1)
		{
			BlitSprite(victoire, 0, 0, 0, window);
		}
		if (perdu == 1)
		{
			BlitSprite(defaite, 0, 0, 0, window);
		}

		sfRenderWindow_display(window);
	}

	return 0;
}