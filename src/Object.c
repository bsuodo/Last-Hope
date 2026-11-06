#include "Object.h"

typedef struct Object {
    int x, y;
    float scale;
    double angle;
    Texture_Buffer* texture_buffer;
    // hide and show maybe??
} Object;

static Object* objects = NULL;
static int object_size = 0;

void CreateObject(char* name, float x, float y, float scale, Texture_Buffer* texture_buffer_p)
{
    objects = SDL_realloc(objects, (object_size+1)*sizeof(Object));
    objects[object_size] = (Object){
        .x = x,
        .y = y,
        .scale = scale,
        .texture_buffer = texture_buffer_p
    };

    object_size++;
}

void RenderObject()
{
    for (int c=0; c < object_size; c++)
    {
        int w = 0;
        int h = 0;
        SDL_FRect src;
        SDL_FRect dst = {
            .x = objects[c].x,
            .y = objects[c].y,
            .w = objects[c].texture_buffer->w * objects[c].scale,
            .h = objects[c].texture_buffer->h * objects[c].scale,
        };

        for (int layer=0; layer<objects[c].texture_buffer->z; layer++)
        {
            src = (SDL_FRect){
                .x = ((float)layer * (float)w),
                .y = (objects[c].texture_buffer->h * objects[c].texture_buffer->z) - ((layer+1) * objects[c].texture_buffer->h),
                .w = objects[c].texture_buffer->w,
                .h = objects[c].texture_buffer->h
            };

            for (int r = 0; r < objects[c].scale; r++)
            {
                dst.y--;
                SDL_RenderTextureRotated(Renderer, objects[c].texture_buffer->texture, &src, &dst, objects[c].angle, NULL, SDL_FLIP_NONE);
            }
        }

    }
    objects[0].angle+=0.1; // voeg in rotate object en dan naam met en NULL boolean als het is gevonden;
    objects[1].angle+=0.1; // IDEM
}