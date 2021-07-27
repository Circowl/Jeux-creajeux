#ifndef DISPLAY_H
#define DISPLAY_H

#include "All.h"

sfSprite* LoadSprite(char* nom, int isCentered);
void BlitSprite(sfSprite* Sprite, float x, float y, sfRenderWindow* window);

#endif // !DISPLAY_H
