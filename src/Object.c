#include "Object.h"

Object* list = NULL;
int size = 0;

void CreateObject(float x, float y, float scale, SDL_Texture *texture, const char *name)
{
    list = SDL_realloc(list, (size + 1) * sizeof(Object));

    list[size].x       = x;
    list[size].y       = y;
    list[size].scale   = scale;
    list[size].rotation = 0.0f;
    list[size].texture = texture;
    list[size].name    = name;

    size++;
}