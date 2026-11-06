#ifndef ENGINE_H
#define ENGINE_H

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include <dirent.h>
#include <stdio.h>

#include <cJSON.h>

extern SDL_Window *Window;
extern SDL_Renderer *Renderer;

void EngineInit();

#endif//ENGINE_H