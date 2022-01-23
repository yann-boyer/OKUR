/*
This file is a part of OKUR.
This file contais code to emulate
CPU module of the Chip8.

Copyright (c) 2022 - Yann BOYER.
*/
#include "CPU.hpp"
#include "CPUInstructions.hpp"

CPU::CPU() {
	std::fill(V.begin(), V.end(), 0x0);
	std::fill(stack.begin(), stack.end(), 0x0);
	std::fill(keyboard.begin(), keyboard.end(), 0x0);

	I = 0x0;
	DT = 0x0;
	ST = 0x0;
	SP = 0x0;
	PC = PC_START;
	opcode = 0x0000;

	// Flags.
	isRunningFlag = true;
	isPausedFlag = false;
	wasKeyPressed = false;
	drawFlag = false;
}

void CPU::updateTimers(void) {
	if(DT > 0x0) DT--;
	if(ST > 0x0) ST--;
}

void CPU::fetchOpcode(MMU &mmu) {
	uint8_t msB = mmu.readRAM(PC);
	uint8_t lsB = mmu.readRAM(PC + 1);

	opcode = msB << 8 | lsB;
}

void CPU::executeInstruction(CPU &cpu, MMU &mmu) {
	fetchOpcode(mmu);

	std::cout << "Current OPCODE -> 0x" << std::hex << opcode << std::dec << std::endl;
	switch(opcode & 0xF000) {
		case 0x0000:
			switch(opcode & 0x00FF) {
				case 0x00E0:
					cls(cpu, mmu);
					break;
				case 0x00EE:
					ret(cpu);
					break;
				default:
					std::cerr << "Unhandled opcode !" << std::endl;
					exit(EXIT_FAILURE);
			}
			break;
		case 0x1000:
			jump(cpu);
			break;
		case 0x2000:
			call(cpu);
			break;
		case 0x3000:
			seByte(cpu);
			break;
		case 0x4000:
			sneByte(cpu);
			break;
		case 0x5000:
			seRegister(cpu);
			break;
		case 0x6000:
			ldByte(cpu);
			break;
		case 0x7000:
			addByte(cpu);
			break;
		case 0x8000:
			switch(opcode & 0x000F) {
				case 0x0000:
					ldRegToReg(cpu);
					break;
				case 0x0001:
					logicalOR(cpu);
					break;
				case 0x0002:
					logicalAND(cpu);
					break;
				case 0x0003:
					exclusiveOR(cpu);
					break;
				case 0x0004:
					addRegisterCarry(cpu);
					break;
				case 0x0005:
					sub(cpu);
					break;
				case 0x0006:
					shr(cpu);
					break;
				case 0x0007:
					subn(cpu);
					break;
				case 0x000E:
					shl(cpu);
					break;
				default:
					std::cerr << "Unhandled opcode !" << std::endl;
					exit(EXIT_FAILURE);
			}
			break;
		case 0x9000:
			sneRegister(cpu);
			break;
		case 0xA000:
			ldi(cpu);
			break;
		case 0xB000:
			jumpV0(cpu);
			break;
		case 0xC000:
			rnd(cpu);
			break;
		case 0xD000:
			drw(cpu, mmu);
			break;
		case 0xE000:
			switch(opcode & 0x00FF) {
				case 0x009E:
					skp(cpu);
					break;
				case 0x00A1:
					sknp(cpu);
					break;
				default:
					std::cerr << "Unhandled opcode !" << std::endl;
					exit(EXIT_FAILURE);
			}
			break;
		case 0xF000:
			switch(opcode & 0x00FF) {
				case 0x0007:
					ldDTOnRegister(cpu);
					break;
				case 0x000A:
					waitKey(cpu);
					break;
				case 0x0015:
					ldRegisterOnDT(cpu);
					break;
				case 0x0018:
					ldRegisterOnST(cpu);
					break;
				case 0x001E:
					addI(cpu);
					break;
				case 0x0029:
					ldF(cpu);
					break;
				case 0x0033:
					stBCD(cpu, mmu);
					break;
				case 0x0055:
					stRegisters(cpu, mmu);
					break;
				case 0x0065:
					ldRegisters(cpu, mmu);
					break;
				default:
					std::cerr << "Unhandled opcode !" << std::endl;
					exit(EXIT_FAILURE);
			}
			break;
		default:
			std::cerr << "Unhandled opcode !" << std::endl;
			exit(EXIT_FAILURE);
	}
}

void CPU::processInput(void) {
	SDL_Event event;

	while(SDL_PollEvent(&event)) {
		if(event.type == SDL_KEYDOWN) {
			switch(event.key.keysym.sym) {
				case SDLK_ESCAPE:
					isRunningFlag = false;
					break;
				case SDLK_SPACE:
					if(isPausedFlag) isPausedFlag = false;
					else isPausedFlag = true;
					break;
				default:
					break;
			}

			for(uint8_t i = 0; i < KEYS_COUNT; i++) {
				if(event.key.keysym.sym == KEYMAP[i]) {
					keyboard[i] = 1;
				}
			}
		}

		if(event.type == SDL_KEYUP) {
			for(uint8_t i = 0; i < KEYS_COUNT; i++) {
				if(event.key.keysym.sym == KEYMAP[i]) {
					keyboard[i] = 0;
				}
			}
		}

		if(event.type == SDL_QUIT) {
			isRunningFlag = false;
		}
	}
}