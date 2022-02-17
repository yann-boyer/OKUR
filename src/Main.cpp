/*
OKUR is a small Chip8 Emulator written in
C++ with SDL2 made for fun and my high school
assignment.

Copyright (c) 2022 - Yann BOYER.
*/
#include<iostream>
#include<cstdlib>
#include<unistd.h>
#include<string>
#include<SDL2/SDL.h>
#include<SDL2/SDL_mixer.h>

#include "CPU.hpp"
#include "Display.hpp"

const uint16_t CPU_CLOCK_DELAY = 1000;
const uint8_t TIMER_DIVISION_CLOCK = 9;

int main(int argc, char *argv[]) {

	if(argc < 2) {
		std::cerr << "OKUR Usage : ./okur /path/to/rom" << std::endl;
		exit(EXIT_FAILURE);
	}

	srand(time(NULL));
	SDL_Init(SDL_INIT_EVERYTHING);
	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) {
		std::cerr << "Unable to initialize SDL Mixer !" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	std::string romPath = std::string(argv[1]);

	CPU cpu;
	Display display;

	cpu.loadROM(romPath);

	uint8_t divCycles = 0;

	while(cpu.isRunningFlag) {
		cpu.executeInstruction();
		divCycles++;

		if(cpu.drawFlag) {
			display.bufferGraphics(cpu.mmu);
			display.drawGraphics();
			cpu.drawFlag = false;
		}

		do {
			cpu.processInput();
		} while(cpu.isPausedFlag && cpu.isRunningFlag);

		if(divCycles == TIMER_DIVISION_CLOCK) {
			cpu.updateTimers();
			divCycles = 0;
		}

		/*
			TODO : Find a better way
			to handle this.
		*/ 
		usleep(CPU_CLOCK_DELAY);
	}

	display.destroyDisplay();

	Mix_FreeMusic(cpu.beepSound);
	Mix_CloseAudio();

	return EXIT_SUCCESS;
}