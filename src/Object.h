#ifndef OBJECT_H
#define OBJECT_H

#include "Assets.h"

void CreateObject(char* name, float x, float y, float scale, Texture_Buffer* texture_buffer_p);
void RenderObject();

#endif//OBJECT_H