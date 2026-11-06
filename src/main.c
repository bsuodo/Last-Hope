#include "Object.h"

#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL_main.h>

SDL_Texture* Renderer_DownScaled;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    
    Window = SDL_CreateWindow("Last Hope", 1280, 720, SDL_WINDOW_HIDDEN);
    Renderer = SDL_CreateRenderer(Window, NULL);

    SDL_SetDefaultTextureScaleMode(Renderer, SDL_SCALEMODE_NEAREST);
    Renderer_DownScaled = SDL_CreateTexture(Renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET, 480, 270);

    EngineInit();
    LoadAssets(); // return false means not valid textures.json or maybe textures file png
    
    CreateObject("doos_clone_ID_1", 130, 130, 2, GetTextureBuffer("box"));
    CreateObject("doos_clone_ID_2", 330, 130, 2, GetTextureBuffer("box"));

    SDL_ShowWindow(Window);

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate)
{
    SDL_SetRenderTarget(Renderer, Renderer_DownScaled);
    
    SDL_SetRenderDrawColorFloat(Renderer, 0.3, 0.3, 0.3, 1);
    SDL_RenderClear(Renderer);
    
    RenderObject();
    
    SDL_SetRenderTarget(Renderer, NULL);

    SDL_RenderClear(Renderer);

    SDL_RenderTexture(Renderer, Renderer_DownScaled, NULL, NULL);

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
