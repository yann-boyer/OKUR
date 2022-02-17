/*
This file is a part of OKUR.
This file is a header.

Copyright (c) 2022 - Yann BOYER.
*/
#ifndef CPU_HPP
#define CPU_HPP

#include<iostream>
#include<cstdlib>
#include<array>
#include<SDL2/SDL.h>
#include<SDL2/SDL_mixer.h>

#include "MMU.hpp"

class CPU {
	public:
		CPU();
		MMU mmu;
		static const uint8_t REGISTERS_COUNT = 16;
		static const uint8_t STACK_SIZE = 16;
		static const uint8_t KEYS_COUNT = 16;
		static const uint16_t PC_START = 0x200;

		std::array<uint8_t, REGISTERS_COUNT> V; // V1 - VE Register.
		std::array<uint16_t, STACK_SIZE> stack; // Stack.
		std::array<uint8_t, KEYS_COUNT> keyboard;
		static constexpr std::array<uint8_t, KEYS_COUNT> KEYMAP = {
			SDLK_x, // 0
			SDLK_1, // 1
			SDLK_2, // 2
			SDLK_3, // 3
			SDLK_q, // 4
			SDLK_w, // 5
			SDLK_e, // 6
			SDLK_a, // 7
			SDLK_s, // 8
			SDLK_d, // 9
			SDLK_z, // A
			SDLK_c, // B
			SDLK_4, // C
			SDLK_r, // D
			SDLK_f, // E
			SDLK_v, // F
		};
		uint16_t I; // Index Registers.
		uint8_t DT; // Delay Timer.
		uint8_t ST; // Sound Timer.
		uint16_t SP; // Stack Pointer.
		uint16_t PC; // Program Counter.
		uint16_t opcode; // Current OP.

		// Flags.
		bool isRunningFlag;
		bool isPausedFlag;
		bool wasKeyPressed;
		bool drawFlag;

		Mix_Music *beepSound;

		// Functions.
		void loadROM(const std::string &prgPath);
		void updateTimers(void);
		void executeInstruction(void);
		void processInput(void);

	private:
		void fetchOpcode(void);
};

#endif