#include "Assets.h"

struct Assets Assets;

void InitAssets()
{
    Assets.Texture_Names = SDL_malloc(0);
    Assets.Textures = SDL_malloc(0);
    Assets.width = SDL_malloc(0);
    Assets.height = SDL_malloc(0);
    Assets.Texture_Size = 0;
}

void LoadTexture(const char *name, const char *path, int width, int height)
{
    char Texture_Path[1024];
    strcpy(Texture_Path, path);

    Assets.Textures = SDL_realloc(Assets.Textures, sizeof(SDL_Texture*)*(Assets.Texture_Size + 1));
    Assets.Textures[Assets.Texture_Size] = IMG_LoadTexture(Renderer, Texture_Path);

    Assets.width = SDL_realloc(Assets.width, sizeof(int)*(Assets.Texture_Size + 1));
    Assets.width[Assets.Texture_Size] = width;

    Assets.height = SDL_realloc(Assets.height, sizeof(int)*(Assets.Texture_Size + 1));
    Assets.height[Assets.Texture_Size] = height;

    Assets.Texture_Names = SDL_realloc(Assets.Texture_Names, sizeof(char*)*(Assets.Texture_Size + 1));
    Assets.Texture_Names[Assets.Texture_Size] = SDL_malloc(strlen(name) + 1);
    strcpy(Assets.Texture_Names[Assets.Texture_Size], name);

    Assets.Texture_Size++;

    SDL_SetTextureScaleMode(Assets.Textures[Assets.Texture_Size - 1], SDL_SCALEMODE_NEAREST);
}

SDL_Texture* GetTexture(const char *name)
{
    for (int c = 0; c < Assets.Texture_Size; c++)
    {
        if (strcmp(Assets.Texture_Names[c], name) == 0)
            return Assets.Textures[c];
    }

    return NULL;
}