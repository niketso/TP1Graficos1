#include "SDL.h"
#include <stdio.h>

int main(int argc, char* argv[]) {

	SDL_Window *window;                    // Declare a pointer

	SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL2

										   // Create an application window with the following settings:
	window = SDL_CreateWindow(
		"ventana1",                  // window title
		SDL_WINDOWPOS_UNDEFINED,           // initial x position
		SDL_WINDOWPOS_UNDEFINED,           // initial y position
		640,                               // width, in pixels
		480,                               // height, in pixels
		SDL_WINDOW_OPENGL                  // flags - see below
	);

	// Check that the window was successfully created
	if (window == NULL) {
		// In the case that the window could not be made...
		printf("Could not create window: %s\n", SDL_GetError());
		return 1;
	}

	// The window is open: could enter program loop here (see SDL_PollEvent())

	//SDL_Delay(3000);  // Pause execution for 3000 milliseconds, for example

					  // Close and destroy the window
	//SDL_DestroyWindow(window);
	SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_Surface * image = SDL_LoadBMP("image.bmp");
	SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, image);

	bool quit = false;
	int x=5;
	int y=5;
	while (!quit) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			/* handle your event here */
			
			switch (event.type) {
			case SDL_QUIT:
				quit = true;
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
				case SDLK_LEFT:  x--; break;
				case SDLK_RIGHT: x++; break;
				case SDLK_UP:    y--; break;
				case SDLK_DOWN:  y++; break;
				}
				break;
			}
			
			
				
		}
		/* do some other stuff here -- draw your app, etc. */
		SDL_Rect dstrect = { x, y, 320, 240 };
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, NULL, &dstrect);
		//SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);
	}

	// Clean up
	SDL_Quit();
	return 0;
}