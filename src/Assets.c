#include "Assets.h"

// textures resource
SDL_Texture** Texture_files;
char** Texture_names;
int Texture_size;

void LoadAssets()
{
    SDL_SetDefaultTextureScaleMode(Renderer, SDL_SCALEMODE_NEAREST);

    Texture_files = SDL_malloc(0);
    Texture_names = SDL_malloc(0);
    Texture_size  = 0;

    DIR* searcher = opendir("assets/textures/");
    struct dirent* file;

    while ((file = readdir(searcher)) != NULL)
    {
        if (strcmp(file->d_name, ".")==0 || strcmp(file->d_name, "..")==0)
            continue;

        char* file_extension = strchr(file->d_name, '.') + 1;
        if (!strcmp(file_extension, "png"))
        {
            int naam_lengte = (strlen(file->d_name) - 4);

            Texture_files               = SDL_realloc(Texture_files, (Texture_size+1)*sizeof(SDL_Texture*));
            Texture_names               = SDL_realloc(Texture_names, (Texture_size+1)*sizeof(char*));
            Texture_names[Texture_size] = SDL_malloc (naam_lengte+1                  *sizeof(char));

            char file_path[1024];

            strcpy(file_path, "assets/textures/");
            strcat(file_path, file->d_name);
            Texture_files[Texture_size] = IMG_LoadTexture(Renderer, file_path);

            strncpy(Texture_names[Texture_size], file->d_name, naam_lengte);
            Texture_names[Texture_size][naam_lengte] = '\0';

            Texture_size++;

            SDL_Log(SDL_GetError());
        }
    }
}

SDL_Texture* GetTexture(char* texture_name)
{
    for (int c = 0; c < Texture_size; c++)
    {
        if (strcmp(texture_name, Texture_names[c]) == 0) return Texture_files[c];
    }

    return NULL;
}