#ifndef ALL_H
#define ALL_H

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
#include "Display.h"
#include "FallingState.h"
#include "JumpingState.h"
#include "RunningState.h"

enum PHASE
{
	Running,
	Jumping,
	Falling
};

struct GAMEDATA
{
	sfSprite* Action;
	sfRenderWindow* window;
	float x;
	float y;
	enum PHASE phase;
};

#endif // !ALL_H

