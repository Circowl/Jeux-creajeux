int x = 15;
int y = 10;
int directionx = 1;
int directiony = 1;
void GameLoop()
{

		if (directionx == (-1))
			x--;
		if (directionx == 1)
			x++;
		if (directiony == (-1))
			y--;
		if (directiony == 1)
			y++;
		if (x == 29 || x == 0)
			directionx = directionx * (-1);
		if (y == 19 || y == 0)
			directiony = directiony * (-1);
	KPrintSquare(x, y);
}