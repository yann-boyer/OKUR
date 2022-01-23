/*
This file is a part of OKUR.
This file contains code to emulate
Chip8 screen.

Copyright (c) 2022 - Yann BOYER.
*/
#include "Display.hpp"

Display::Display() {
	chip8Window = SDL_CreateWindow(
		"OKUR Chip8 Emu by Yann BOYER.",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		SDL_WINDOW_SHOWN |
		SDL_WINDOW_OPENGL |
		SDL_WINDOW_RESIZABLE |
		SDL_WINDOW_ALLOW_HIGHDPI
		);

	if(chip8Window == nullptr) {
		std::cerr << "Unable to create and initialize window !" << std::endl;
		exit(EXIT_FAILURE);
	}

	chip8Renderer = SDL_CreateRenderer(chip8Window, -1, 0);

	if(chip8Renderer == nullptr) {
		std::cerr << "Unable to create and initialize renderer !" << std::endl;
		exit(EXIT_FAILURE);
	}

	chip8Texture = SDL_CreateTexture(
		chip8Renderer,
		SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_TARGET,
		SCREEN_WIDTH,
		SCREEN_HEIGHT
		);

	if(chip8Texture == nullptr) {
		std::cerr << "Unable to create and initialize texture !" << std::endl;
		exit(EXIT_FAILURE);
	}

	SDL_SetRenderDrawColor(chip8Renderer, 0, 0, 0, 0);
	SDL_RenderClear(chip8Renderer);
	SDL_RenderPresent(chip8Renderer);
}

void Display::bufferGraphics(MMU &mmu) {
	for(uint8_t y = 0; y < 32; y++) {
		for(uint8_t x = 0; x < 64; x++) {
			uint8_t pixel = mmu.gfx[y][x];
			pixelBuffer[(y * SCREEN_WIDTH) + x] = (pixel * 0xFFFFFF00) | 0x000000FF;
		}
	}
}

void Display::drawGraphics(void) {
	SDL_UpdateTexture(chip8Texture, NULL, pixelBuffer, SCREEN_WIDTH * sizeof(uint32_t));
	SDL_RenderClear(chip8Renderer);
	SDL_RenderCopy(chip8Renderer, chip8Texture, NULL, NULL);
	SDL_RenderPresent(chip8Renderer);
}

void Display::destroyDisplay(void) {
	SDL_DestroyWindow(chip8Window);
	SDL_DestroyRenderer(chip8Renderer);
	SDL_DestroyTexture(chip8Texture);

	delete[] pixelBuffer;

	SDL_Quit();
}