#include "Object.h"

typedef struct Object {
    int x, y;
    float scale;
    double angle;
    SDL_Texture* texture;
    // hide and show maybe??
} Object;

static Object* objects = NULL;
static int object_size = 0;

void CreateObject(char* name, float x, float y, float scale, SDL_Texture* texture)
{
    objects = SDL_realloc(objects, (object_size+1)*sizeof(Object));
    objects[object_size] = (Object){
        .x = x,
        .y = y,
        .scale = scale,
        .texture = texture
    };

    object_size++;
}

void RenderObject()
{
    for (int c=0; c < object_size; c++)
    {
        int w = 0;
        int h = 16;
        SDL_FRect src;
        SDL_FRect dst = {
            .x = objects[c].x,
            .y = objects[c].y,
            .w = 16 * objects[c].scale,
            .h = 16 * objects[c].scale,
        };

        for (int layer=0; layer<16; layer++)
        {
            src = (SDL_FRect){
                .x = ((float)layer * (float)w),
                .y = (16 * 16) - ((layer+1) * 16),
                .w = 16,
                .h = 16
            };

            for (int r = 0; r < 12; r++)
            {
                dst.y--;//plus kant 8 is max 2-4 is chill
                SDL_RenderTextureRotated(Renderer, objects[c].texture, &src, &dst, objects[c].angle, NULL, SDL_FLIP_NONE);
            }
        }

        objects[0].angle+=0.1;
    }
}