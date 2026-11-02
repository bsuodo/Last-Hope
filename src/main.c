#include "Engine.h"

#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL_main.h>

static Uint64 previousFrameCounter;
static Uint64 performanceFrequency;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    (void)appstate;
    (void)argc;
    (void)argv;

    InitAssets();
    
    Window = SDL_CreateWindow("Last Hope", 800, 600, 0);
    Renderer = SDL_CreateRenderer(Window, NULL);
    
    LoadTexture("box", "Assets/textures/box.png", 16, 16);

    CreateObject(100, 300, 4, GetTexture("box"), "Box");

    performanceFrequency = SDL_GetPerformanceFrequency();
    previousFrameCounter = SDL_GetPerformanceCounter();

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate)
{
    (void)appstate;

    Uint64 currentFrameCounter = SDL_GetPerformanceCounter();
    float deltaTime = (float)((double)(currentFrameCounter - previousFrameCounter) / performanceFrequency);
    previousFrameCounter = currentFrameCounter;
    if (deltaTime > 0.1f)
        deltaTime = 0.1f;

    UpdateCamera(deltaTime);

    SDL_RenderClear(Renderer);

    RenderObjects();

    SDL_RenderPresent(Renderer);

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    if (event->type == SDL_EVENT_QUIT) return SDL_APP_SUCCESS;

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    (void)appstate;
    (void)result;

    return;
}