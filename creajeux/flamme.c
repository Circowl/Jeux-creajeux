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

sfTime temps;
sfClock* horloge = 0;

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

struct PARTICLE
{
	float x;
	float y;
	float TTL;
	float TTLmax;
	float rotation;
	float deltaY;
};

struct PARTICLE AddParticle(float x, float y)
{
	struct PARTICLE temp;

	temp.TTL = 0;
	temp.TTLmax = 1;
	temp.x = x + (rand() % 20 - 10);
	temp.y = y + (rand() % 20 - 10);
	temp.rotation = rand();
	temp.deltaY = 0;
	return(temp);
}


int _tmain(int argc, _TCHAR* argv[])
{

	sfVideoMode mode = { 1024, 768, 32 };
	window = sfRenderWindow_create(mode, "SFML window", sfResize | sfClose, NULL);

	horloge = sfClock_create();
	sfSprite* smoke;
	sfSprite* fond;
	sfSprite* flamme[10];

	smoke = LoadSprite("smoke.png", 1);
	fond = LoadSprite("Background.png", 0);
	flamme[0] = LoadSprite("flamme/fumee1.png", 1);
	flamme[1] = LoadSprite("flamme/fumee2.png", 1);
	flamme[2] = LoadSprite("flamme/fumee3.png", 1);
	flamme[3] = LoadSprite("flamme/fumee4.png", 1);
	flamme[4] = LoadSprite("flamme/fumee5.png", 1);
	flamme[5] = LoadSprite("flamme/fumee6.png", 1);
	flamme[6] = LoadSprite("flamme/fumee7.png", 1);
	flamme[7] = LoadSprite("flamme/fumee8.png", 1);
	flamme[8] = LoadSprite("flamme/fumee9.png", 1);
	flamme[9] = LoadSprite("flamme/fumee10.png", 1);


	struct PARTICLE particle[20000];
	int i = 0;
	int disp = 0;

	sfClock_restart(horloge);

	while (sfRenderWindow_isOpen(window))
	{
		float frameTime = sfTime_asSeconds(sfClock_restart(horloge));

		while (sfRenderWindow_pollEvent(window, &event))
		{
			if (event.type == sfEvtClosed) exit(0); //Fermeture en appuyant sur le bouton Fermer

			if (event.type == sfEvtMouseButtonPressed)
			{

				if (event.mouseButton.button == sfMouseLeft)
				{
					
				}
			}
		}

		if (sfMouse_isButtonPressed(sfMouseLeft) && i < 20000)
		{
			particle[i] = AddParticle(sfMouse_getPositionRenderWindow(window).x, sfMouse_getPositionRenderWindow(window).y);
			i++;
		}
		

		for (int j = i - 1; j >= 0; j--)
		{
			particle[j].TTL += frameTime;
			if (particle[j].TTL >= particle[j].TTLmax)
			{
				particle[j] = particle[i - 1];
				i--;
			}
			particle[j].deltaY = particle[j].deltaY + 0.1;
		}
	
		sfRenderWindow_clear(window, sfBlack);

		BlitSprite(fond, 0, 0, window);

		for (int j = 0; j < i; j++)
		{
			float factor = (particle[j].TTL / particle[j].TTLmax);
			factor = powf(factor, 1);
			sfColor tempColor = { 0, 0, 0, sin(factor*3.1415) * 20 };
			sfSprite_setColor(smoke, tempColor);
			sfSprite_setRotation(smoke, particle[j].rotation);
			BlitSprite(smoke, particle[j].x, particle[j].y - (1.5 * particle[j].deltaY), window);
			BlitSprite(flamme[(int)(particle[j].TTL * 10)], particle[j].x, particle[j].y - particle[j].deltaY, window);
		}

		sfRenderWindow_display(window);
	}

	return 0;
}



