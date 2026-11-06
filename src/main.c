#include "Object.h"

#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL_main.h>

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    Window = SDL_CreateWindow("Last Hope", 1280, 768, SDL_WINDOW_HIDDEN);
    Renderer = SDL_CreateRenderer(Window, NULL);
    
    LoadAssets(); // return false means not valid textures.json or maybe textures file png
    
    CreateObject("doos_clone_ID_1", 100, 100, 10, GetTextureBuffer("box"));

    SDL_ShowWindow(Window);

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate)
{
    SDL_SetRenderDrawColorFloat(Renderer, 0.3, 0.3, 0.3, 1);
    SDL_RenderClear(Renderer);

    RenderObject();

    SDL_RenderPresent(Renderer);

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    return event->type == SDL_EVENT_QUIT ? SDL_APP_SUCCESS : SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    return;
}
