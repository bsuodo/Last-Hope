#ifndef ASSETS_H
#define ASSETS_H

#include "Engine.h"

typedef struct Texture_Buffer {
    SDL_Texture* texture;
    int w, h, z;
    char* naam;
} Texture_Buffer;

void LoadAssets();
Texture_Buffer* GetTextureBuffer(char* texture_name);

#endif//ASSETS_H