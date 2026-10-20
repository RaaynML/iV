#pragma once

#include <stdio.h>
#include <stdlib.h> //includes limits.h
#include <memory>
#include <string_view>

extern "C" {
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_surface.h>
//#include <SDL3_image/SDL_image.h>
}

#define kys exit(1)
#define cast static_cast
