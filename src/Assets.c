#include "Assets.h"

int Texture_Buffer_Array_Size = 0;
Texture_Buffer* Texture_Buffer_Array;

void LoadAssets()
{
    Texture_Buffer_Array = SDL_malloc(0);

    FILE* JSON_Bestand = fopen("assets/textures.json", "r");

    fseek(JSON_Bestand, 0, SEEK_END);
    int JSON_Bestand_Size = ftell(JSON_Bestand);
    fseek(JSON_Bestand, 0, SEEK_SET);

    char JSON_Bestand_Contents[JSON_Bestand_Size+1];
    JSON_Bestand_Contents[JSON_Bestand_Size] = '\0';

    fread(JSON_Bestand_Contents, sizeof(char), JSON_Bestand_Size, JSON_Bestand);
    cJSON *parser = cJSON_Parse(JSON_Bestand_Contents);

    fclose(JSON_Bestand);

    DIR* searcher = opendir("assets/textures/");
    struct dirent* file;

    while ((file = readdir(searcher)) != NULL)
    {
        if (strcmp(file->d_name, ".")==0 || strcmp(file->d_name, "..")==0)
            continue;

        char* file_extension = strchr(file->d_name, '.') + 1;
        if (file_extension != NULL && !strcmp(file_extension, "png"))
        {
            // nieuwe texture buffer
            Texture_Buffer_Array = SDL_realloc(Texture_Buffer_Array, (Texture_Buffer_Array_Size+1)*sizeof(Texture_Buffer));

            // naam
            int naam_lengte = (strlen(file->d_name) - 4);
            Texture_Buffer_Array[Texture_Buffer_Array_Size].naam = SDL_malloc(naam_lengte+1);
            strncpy(Texture_Buffer_Array[Texture_Buffer_Array_Size].naam, file->d_name, naam_lengte);
            Texture_Buffer_Array[Texture_Buffer_Array_Size].naam[naam_lengte] = '\0';

            // texture
            char file_path[1024] = {0};
            strcpy(file_path, "assets/textures/");
            strcat(file_path, file->d_name);
            Texture_Buffer_Array[Texture_Buffer_Array_Size].texture = IMG_LoadTexture(Renderer, file_path);

            // x, y, z, do make it better
            cJSON* JSON_Finder = cJSON_GetObjectItemCaseSensitive(parser, Texture_Buffer_Array[Texture_Buffer_Array_Size].naam);
            Texture_Buffer_Array[Texture_Buffer_Array_Size].w = (char)cJSON_GetNumberValue(cJSON_GetArrayItem(JSON_Finder, 0));
            Texture_Buffer_Array[Texture_Buffer_Array_Size].h = (char)cJSON_GetNumberValue(cJSON_GetArrayItem(JSON_Finder, 1));
            Texture_Buffer_Array[Texture_Buffer_Array_Size].z = (char)cJSON_GetNumberValue(cJSON_GetArrayItem(JSON_Finder, 2));

            Texture_Buffer_Array_Size++;
        }
    }

    closedir(searcher);
    cJSON_Delete(parser);
}

Texture_Buffer* GetTextureBuffer(char* texture_name)
{
    for (int c = 0; c < Texture_Buffer_Array_Size; c++)
    {
        if (strcmp(Texture_Buffer_Array[c].naam, texture_name) == 0) return &Texture_Buffer_Array[c];
    }

    return NULL;
}