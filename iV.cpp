//#include <iostream>
//#define _NO_CRT_STDIO_INLINE 
#include "includes.h"


int main(int argc, char* argv[])
{
	printf_s("Response\n");

	SDL_Point iwdim{960,640};
	SDL_Window* mainwx; SDL_Renderer* rex;
	SDL_CreateWindowAndRenderer("ImageView", iwdim.x, iwdim.y, SDL_WindowFlags(0ULL), &mainwx, &rex);
	//Render not RenderER

	if(!mainwx) { printf_s(SDL_GetError()); }
	SDL_SetRenderDrawColor(rex, 0x64, 0x95, 0xED, 0xFF);
	SDL_RenderClear(rex);
	SDL_ShowWindow(mainwx);

	SDL_SetRenderVSync(rex, SDL_RENDERER_VSYNC_ADAPTIVE);

	//auto imgTx = IMG_LoadTexture(rex, "img.ppm");
	//SDL_SetWindowSize(mainwx, iwdim.x, iwdim.y);
	const char* png_path = "img.png";
	SDL_Surface* surface = SDL_LoadPNG(png_path);
	if(!surface) {
		SDL_Log("Couldn't load png: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	auto imgTx = SDL_CreateTextureFromSurface(rex, surface);
	iwdim = {imgTx->w, imgTx->h};
	SDL_DestroySurface(surface);

	if(!imgTx) {
		SDL_Log("Couldn't create static texture: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	SDL_FRect dst_rect = {0,0,96,64};

	SDL_RenderTexture(rex, imgTx, NULL, &dst_rect);
	if(!SDL_SetRenderLogicalPresentation(rex, iwdim.x, iwdim.y, SDL_LOGICAL_PRESENTATION_INTEGER_SCALE)){
		SDL_Log("Couldn't set mode: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}
	SDL_RenderPresent(rex);

	SDL_Event m_event;
	bool running = true;

	do {
		SDL_PollEvent(&m_event);
		if(m_event.type >= SDL_EVENT_WINDOW_FIRST && m_event.type <= SDL_EVENT_WINDOW_LAST) {
			//SDL_RenderClear(rex);
			SDL_RenderTexture(rex, imgTx, NULL, &dst_rect);
			SDL_RenderPresent(rex);
		} else if(m_event.type == SDL_EVENT_QUIT) {
			running = false;
		}
	} while(running);

	SDL_DestroyTexture(imgTx);
	SDL_DestroyRenderer(rex);
	SDL_DestroyWindow(mainwx);

	return 0;

}
