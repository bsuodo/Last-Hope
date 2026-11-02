#include "Renderer.h"

extern Object* list;
extern int size;

static float cameraX = 0.0f;
static float cameraY = 0.0f;
static float cameraRotation = 0.0f;

void UpdateCamera(float deltaTime)
{
    const bool *keyboard = SDL_GetKeyboardState(NULL);
    float moveX = (float)(keyboard[SDL_SCANCODE_D] - keyboard[SDL_SCANCODE_A]);
    float moveY = (float)(keyboard[SDL_SCANCODE_S] - keyboard[SDL_SCANCODE_W]);
    float rotate = (float)(keyboard[SDL_SCANCODE_RIGHT] - keyboard[SDL_SCANCODE_LEFT]);
    float movementScale = (moveX != 0.0f && moveY != 0.0f) ? 0.70710678f : 1.0f;
    const float cameraSpeed = 300.0f;
    const float rotationSpeed = SDL_PI_F / 2.0f;

    cameraX += moveX * movementScale * cameraSpeed * deltaTime;
    cameraY += moveY * movementScale * cameraSpeed * deltaTime;
    cameraRotation = SDL_fmodf(cameraRotation + rotate * rotationSpeed * deltaTime, 2.0f * SDL_PI_F);
}

void RenderObjects()
{
    int outputWidth;
    int outputHeight;
    if (!SDL_GetRenderOutputSize(Renderer, &outputWidth, &outputHeight))
        return;

    float centerX = outputWidth * 0.5f;
    float centerY = outputHeight * 0.5f;
    float rotationCos = SDL_cosf(cameraRotation);
    float rotationSin = SDL_sinf(cameraRotation);
    float rotationDegrees = cameraRotation * (180.0f / SDL_PI_F);
    bool reverseLayers = rotationCos < 0.0f;

    for (int c = 0; c < size; c++)
    {
        if (!list[c].texture)
            continue;

        int layer_width = 0;
        int layer_height = 0;
        for (int c2 = 0; c2 < Assets.Texture_Size; c2++)
        {
            if (Assets.Textures[c2] == list[c].texture)
            {
                layer_width = Assets.width[c2];
                layer_height = Assets.height[c2];
                break;
            }
        }

        float texture_width;
        float texture_height;
        if (layer_width <= 0 || layer_height <= 0 ||
            !SDL_GetTextureSize(list[c].texture, &texture_width, &texture_height) ||
            texture_width < layer_width || texture_height < layer_height ||
            (int)texture_width % layer_width != 0)
        {
            continue;
        }

        int layers = (int)texture_width / layer_width;
        int repeats_per_layer = (int)list[c].scale;

        for (int stackLayer = 0; stackLayer < layers; stackLayer++)
        {
            int textureLayer = reverseLayers ? layers - 1 - stackLayer : stackLayer;
            SDL_FRect src = { textureLayer * layer_width, 0, layer_width, layer_height };
            for (int repeat = 0; repeat < repeats_per_layer; repeat++)
            {
                float x = list[c].x - cameraX - centerX;
                float y = list[c].y - cameraY - stackLayer * repeats_per_layer - repeat - centerY;
                SDL_FRect dst = {
                    centerX + x * rotationCos - y * rotationSin,
                    centerY + x * rotationSin + y * rotationCos,
                    layer_width * list[c].scale,
                    layer_height * list[c].scale
                };
                SDL_RenderTextureRotated(Renderer, list[c].texture, &src, &dst, rotationDegrees + list[c].rotation, NULL, SDL_FLIP_NONE);
            }
        }
    }
}