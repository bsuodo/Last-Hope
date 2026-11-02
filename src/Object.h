#ifndef OBJECT_H
#define OBJECT_H

#include "Engine.h"

typedef struct Object
{
    float x;
    float y;
    float scale;
    float rotation;
    SDL_Texture *texture;
    char *name;
} Object;

void CreateObject(float x, float y, float scale, SDL_Texture *texture, const char *name);

#endif//OBJECT_H