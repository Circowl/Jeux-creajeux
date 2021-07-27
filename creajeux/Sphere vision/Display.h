#ifndef DISPLAY_H
#define DISPLAY_H

#include "All.h"

sfSprite* LoadSprite(char* nom, int isCentered);
sfSound* LoadSon(char* nom);
void BlitSprite(sfSprite* Sprite, float x, float y, sfRenderWindow* window);
void BlitInt(sfFont* font, int Nombre, float x, float y, sfRenderWindow* window);
void BlitFloat(sfFont* font, float Nombre, float x, float y, sfRenderWindow* window);

#endif // !DISPLAY_H
