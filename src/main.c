// main.c - Flyby Pheobe source - Written by Kuba Felendzer 2022

//! code is uncommented because this is just a test for SDL being set up on my developement machine.

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

#define QUITKEY SDLK_ESCAPE
#define WIDTH 800
#define HEIGHT 800

SDL_Window* screen = NULL;
SDL_Renderer* renderer;
SDL_Event event;
SDL_Rect source, destination, dst;

int keypressed;
int rectCount = 0;

int dr_ret = -1;

void setup() {
	srand((unsigned int) time(NULL));

	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, SDL_WINDOW_SHOWN, &screen, &renderer);

	if (!screen) {
		return 1;
	}

	SDL_SetWindowTitle(screen, "SDL Initial Test");
}

void cleanup() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(screen);

	SDL_Quit();
	exit(0);
}

void draw_rectangle() {
	if(rectCount == 10000) {
		SDL_RenderPresent(renderer);
		
		SDL_SetWindowTitle(screen, "SDL Initial Test - Done!");

		dr_ret = 0;
	}

	SDL_Rect rect;

	SDL_SetRenderDrawColor(renderer, rand() % 256, rand() % 256, rand() % 256, 255);

	rect.h = 200;
	rect.w = 200;
	rect.y = rand() % (HEIGHT - rect.h);

	SDL_RenderFillRect(renderer, &rect);

	rectCount++;

	dr_ret = rectCount;
}

void gameloop() {
	int game_running = 1;

	while(game_running) {
		if(dr_ret != 0) draw_rectangle();

		while(SDL_PollEvent(&event)) {
			switch(event.type) {
				case SDL_KEYDOWN:
					keypressed = event.key.keysym.sym;

					if (keypressed == QUITKEY) {
						game_running = 0;
						break;
					}

					break;

				case SDL_QUIT:
					game_running = 0;
					break;

				case SDL_KEYUP:
					break;
			}
		}
	}
}

int main(void) {
	setup();
	gameloop();
	cleanup();

	return 0;
}
		



	
