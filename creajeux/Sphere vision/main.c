#include "All.h"






int _tmain(int argc, _TCHAR* argv[])
{

	sfVideoMode mode = { 1280, 900, 32 };
	sfRenderWindow* window = sfRenderWindow_create(mode, "SFML window", sfResize | sfClose, NULL);
	sfEvent event;
	srand((unsigned int)time(NULL));

	sfSprite* sphere[2];

	sphere[0] = LoadSprite("sphere.png", 1);
	sphere[1] = LoadSprite("sphere2.png", 1);

	sfSprite* point = LoadSprite("point.png", 1);
	sfSprite* fond = LoadSprite("fond.png", 0);

	sfFont* font = sfFont_createFromFile("segoeprb.ttf");


	int red = 0;

	float X = 0;
	float Y = 0;

	float sphereX = 640;
	float sphereY = 450;

	float directionX = 0;
	float directionY = 0;

	float forward = 1;

	float PointFictifX[2] = { 0, 0 };
	float PointFictifY[2] = { 0, 0 };

	//---------------------------------------------------------------------- Q Z S D pour déplacer la sphère ----------- UP / DOWN pour changer l'angle -----------------------------------//

	while (sfRenderWindow_isOpen(window))
	{
		while (sfRenderWindow_pollEvent(window, &event))
		{
			if (event.type == sfEvtClosed) exit(0);

			if (event.type == sfEvtKeyPressed)
			{
				if (event.key.code == sfKeySpace)
				{

				}
				if (event.key.code == sfKeyZ)
				{
					directionX = 0;
					directionY = -0.05;
				}
				if (event.key.code == sfKeyS)
				{
					directionX = 0;
					directionY = 0.05;
				}
				if (event.key.code == sfKeyD)
				{
					directionX = 0.05;
					directionY = 0;
				}
				if (event.key.code == sfKeyQ)
				{
					directionX = -0.05;
					directionY = 0;
				}


				if (event.key.code == sfKeyUp && forward <= 2)
				{
					forward = forward + 0.1;
				}
				if (event.key.code == sfKeyDown && forward >= 0)
				{
					forward = forward - 0.1;
				}

			}

			if (event.type == sfEvtMouseButtonPressed)
			{

				if (event.mouseButton.button == sfMouseLeft)
				{
					
				}
			}
		}

		X = sfMouse_getPositionRenderWindow(window).x;
		Y = sfMouse_getPositionRenderWindow(window).y;



		sphereX = sphereX + directionX;
		sphereY = sphereY + directionY;

		if (directionX < 0)
		{
			PointFictifX[0] = sphereX - 100 * forward;
			PointFictifY[0] = sphereY - 100 * (2 - forward);
			PointFictifX[1] = sphereX - 100 * forward;
			PointFictifY[1] = sphereY + 100 * (2 - forward);

			sfVector2f AB = { PointFictifX[0] - sphereX, PointFictifY[0] - sphereY };
			sfVector2f AD = { PointFictifX[1] - sphereX, PointFictifY[1] - sphereY };


			if ((AB.y * ((X - sphereX) / AB.x)) <= (Y - sphereY) && (AD.y * ((X - sphereX) / AD.x)) >= (Y - sphereY)) // je verifie que mon point et en dessous de la droite AB et au dessus de la droite AD
			{
				red = 1;
			}
			else
			{
				red = 0;
			}


		}
		if (directionX > 0)
		{
			PointFictifX[0] = sphereX + 100 * forward;
			PointFictifY[0] = sphereY - 100 * (2 - forward);
			PointFictifX[1] = sphereX + 100 * forward;
			PointFictifY[1] = sphereY + 100 * (2 - forward);

			sfVector2f AB = { PointFictifX[0] - sphereX, PointFictifY[0] - sphereY };
			sfVector2f AD = { PointFictifX[1] - sphereX, PointFictifY[1] - sphereY };

			if ((AB.y * ((X - sphereX) / AB.x)) <= (Y - sphereY) && (AD.y * ((X - sphereX) / AD.x)) >= (Y - sphereY))
			{
				red = 1;
			}
			else
			{
				red = 0;
			}

		}
		if (directionY < 0)
		{
			PointFictifX[0] = sphereX - 100 * forward;
			PointFictifY[0] = sphereY - 100 * (2 - forward);
			PointFictifX[1] = sphereX + 100 * forward;
			PointFictifY[1] = sphereY - 100 * (2 - forward);

			sfVector2f AB = { PointFictifX[0] - sphereX, PointFictifY[0] - sphereY };
			sfVector2f AD = { PointFictifX[1] - sphereX, PointFictifY[1] - sphereY };

			if ((AB.y * ((X - sphereX) / AB.x)) >= (Y - sphereY) && (AD.y * ((X - sphereX) / AD.x)) >= (Y - sphereY))
			{
				red = 1;
			}
			else
			{
				red = 0;
			}
		}
		if (directionY > 0)
		{
			PointFictifX[0] = sphereX + 100 * forward;
			PointFictifY[0] = sphereY + 100 * (2 - forward);
			PointFictifX[1] = sphereX - 100 * forward;
			PointFictifY[1] = sphereY + 100 * (2 - forward);

			sfVector2f AB = { PointFictifX[0] - sphereX, PointFictifY[0] - sphereY };
			sfVector2f AD = { PointFictifX[1] - sphereX, PointFictifY[1] - sphereY };

			if ((AB.y * ((X - sphereX) / AB.x)) <= (Y - sphereY) && (AD.y * ((X - sphereX) / AD.x)) <= (Y - sphereY))
			{
				red = 1;
			}
			else
			{
				red = 0;
			}
		}

		sfRenderWindow_clear(window, sfBlack);

		BlitSprite(fond, 0, 0, window);
		BlitFloat(font, 180 - (forward*90), 1147, 810, window);
		BlitSprite(sphere[red], sphereX, sphereY, window);
		BlitSprite(point, PointFictifX[0], PointFictifY[0], window);
		BlitSprite(point, PointFictifX[1], PointFictifY[1], window);


		sfRenderWindow_display(window);
	}

	return 0;
}
