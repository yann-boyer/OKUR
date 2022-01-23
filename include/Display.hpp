/*
This file is a part of OKUR.
This file is a header.

Copyright (c) 2022 - Yann BOYER.
*/
#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include<iostream>
#include<cstdlib>
#include<SDL2/SDL.h>

#include "MMU.hpp"

class Display {
	public:
		Display();
		void bufferGraphics(MMU &mmu);
		void drawGraphics(void);
		void destroyDisplay(void);
	private:
		static const uint16_t WINDOW_WIDTH = 1280;
		static const uint16_t WINDOW_HEIGHT = 640;
		static const uint8_t SCREEN_WIDTH = 64;
		static const uint8_t SCREEN_HEIGHT = 32;

		SDL_Window *chip8Window;
		SDL_Renderer *chip8Renderer;
		SDL_Texture *chip8Texture;
		uint32_t *pixelBuffer = new uint32_t[32 * 64];
};

#endif