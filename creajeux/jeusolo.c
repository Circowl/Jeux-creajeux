int i = 0;
int j = 0;
int Taille = 2;
int Raquettex = 15;
int Raquettey = 18;
int z = 0;

int x = 15;
int y = 10;
int directionx = -1;
int directiony = -1;

int k = 0;

void GameLoop()
{
	for (i = 0; i < 30; i++)
		for (j = 0; j < 20; j++)
			if (i == 0 || i == 29 || j == 0)
				KPrintSquare(i, j);
	KPrintSquare(Raquettex, Raquettey);
	for (z = 0; z < (Taille + 1); z++)
	{
		KPrintSquare(Raquettex + z, Raquettey);
		KPrintSquare(Raquettex - z, Raquettey);
	}
	if (KGetRight())
		if (Raquettex < (28 - Taille))
			Raquettex++;
	if (KGetLeft())
		if (Raquettex > (1 + Taille))
			Raquettex--;


	if (directionx == (-1))
		x--;
	if (directionx == 1)
		x++;
	if (directiony == (-1))
		y--;
	if (directiony == 1)
		y++;
	if (x == 28 || x == 1)
		directionx = directionx * (-1);
	for (k = 0; k<(Taille + 1); k++)
	{
		if (y == 1 || (y == (Raquettey - 1) && (x == (Raquettex + k) || x == (Raquettex - k))))
			directiony = directiony * (-1);
	}
	if (y == 19)
	{
		x = 15;
		y = 10;
		directionx = -1;
		directiony = -1;
	}

	KPrintBall(x, y);
}