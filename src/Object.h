#ifndef OBJECT_H
#define OBJECT_H

#include "Engine.h"

void CreateObject(char* name, float x, float y, float scale, SDL_Texture* texture);
void RenderObject();

#endif//OBJECT_H