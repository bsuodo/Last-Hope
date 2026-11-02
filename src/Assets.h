#ifndef ASSETS_H
#define ASSETS_H

#include "Engine.h"

extern struct Assets
{
    // All the textures info
    char **Texture_Names;
    SDL_Texture **Textures;
    int Texture_Size;
    int* width;
    int* height;

    // audio...

    // fonts...

    // shaders...

} Assets;

void InitAssets();
void LoadTexture(const char *name, const char *path, int width, int height);
SDL_Texture* GetTexture(const char *name);

#endif//ASSETS_H