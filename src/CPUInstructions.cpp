/*
This file is a part of OKUR.
This file contais code to implement
all Chip8 OPS.

IMPORTANT NOTE : Super Chip48 Opcodes
are not supported and never will be !

Copyright (c) 2022 - Yann BOYER.
*/
#include "CPUInstructions.hpp"

void cls(CPU &cpu, MMU &mmu) {
	for(uint8_t y = 0; y < 32; y++) {
		for(uint8_t x = 0; x < 64; x++) {
			mmu.gfx[y][x] = 0;
		}
	}

	cpu.drawFlag = true;
	cpu.PC += 2;
}

void ret(CPU &cpu) {
	cpu.SP--;
	cpu.PC = cpu.stack[cpu.SP];
	cpu.PC += 2;
}

void jump(CPU &cpu) {
	uint16_t nnn = cpu.opcode & 0x0FFF;

	cpu.PC = nnn;
}

void call(CPU &cpu) {
	uint16_t nnn = cpu.opcode & 0x0FFF;

	cpu.stack[cpu.SP] = cpu.PC;
	cpu.SP++;
	cpu.PC = nnn;
}

void seByte(CPU &cpu) {
	uint8_t x = (cpu.opcode & 0x0F00) >> 8;
	uint8_t kk = cpu.opcode & 0x00FF;

	if(cpu.V[x] == kk) cpu.PC += 4;
	else cpu.PC += 2;
}

void sneByte(CPU &cpu) {
	uint8_t x = (cpu.opcode & 0x0F00) >> 8;
	uint8_t kk = cpu.opcode & 0x00FF;

	if(cpu.V[x] != kk) cpu.PC += 4;
	else cpu.PC += 2;
}

void seRegister(CPU &cpu) {
	uint8_t x = (cpu.opcode & 0x0F00) >> 8;
	uint8_t y = (cpu.opcode & 0x00F0) >> 4;

	if(cpu.V[x] == cpu.V[y]) cpu.PC += 4;
	else cpu.PC += 2;
}

void ldByte(CPU &cpu) {
	uint8_t x = (cpu.opcode & 0x0F00) >> 8;
	uint8_t kk = cpu.opcode & 0x00FF;

	cpu.V[x] = kk;
	cpu.PC += 2;
}

void addByte(CPU &cpu) {
	uint8_t x = (cpu.opcode & 0x0F00) >> 8;
	uint8_t kk = cpu.opcode & 0x00FF;

	cpu.V[x] += kk;
	cpu.PC += 2;
}

void ldRegToReg(CPU &cpu) {
	uint8_t x = (cpu.opcode & 0x0F00) >> 8;
	uint8_t y = (cpu.opcode & 0x00F0) >> 4;

	cpu.V[x] = cpu.V[y];
	cpu.PC += 2;
}

void logicalOR(CPU &cpu) {
	uint8_t x = (cpu.opcode & 0x0F00) >> 8;
	uint8_t y = (cpu.opcode & 0x00F0) >> 4;

	cpu.V[x] = cpu.V[x] | cpu.V[y];
	cpu.PC += 2;
}

void logicalAND(CPU &cpu) {
	uint8_t x = (cpu.opcode & 0x0F00) >> 8;
	uint8_t y = (cpu.opcode & 0x00F0) >> 4;

	cpu.V[x] = cpu.V[x] & cpu.V[y];
	cpu.PC += 2;
}

void exclusiveOR(CPU &cpu) {
	uint8_t x = (cpu.opcode & 0x0F00) >> 8;
	uint8_t y = (cpu.opcode & 0x00F0) >> 4;

	cpu.V[x] = cpu.V[x] ^ cpu.V[y];
	cpu.PC += 2;
}

void addRegisterCarry(CPU &cpu) {
	uint8_t x = (cpu.opcode & 0x0F00) >> 8;
	uint8_t y = (cpu.opcode & 0x00F0) >> 4;
	uint16_t sum = cpu.V[x] + cpu.V[y];

	// Set VF to 1 if sum is greater than 8bit.
	// 8bit = 255 = 0xFF.
	cpu.V[0xF] = sum > 0xFF ? 1 : 0;

	cpu.V[x] = sum & 0xFF;
	cpu.PC += 2;
}

void sub(CPU &cpu) {
	uint8_t x = (cpu.opcode & 0x0F00) >> 8;
	uint8_t y = (cpu.opcode & 0x00F0) >> 4;

	// Set VF to 1 if Vx is greater than Vy.
	cpu.V[0xF] = cpu.V[x] > cpu.V[y] ? 1 : 0;

	cpu.V[x] -= cpu.V[y];
	cpu.PC += 2;
}	

void shr(CPU &cpu) {
	uint8_t x = (cpu.opcode & 0x0F00) >> 8;

	cpu.V[0xF] = cpu.V[x] % 2 == 1 ? 1 : 0;

	cpu.V[x] >>= 1; // Right Shift by 1.
	cpu.PC += 2;
}

void subn(CPU &cpu) {
	uint8_t x = (cpu.opcode & 0x0F00) >> 8;
	uint8_t y = (cpu.opcode & 0x00F0) >> 4;

	// Set VF to 1 if Vy is greater than Vx.
	cpu.V[0xF] = cpu.V[y] > cpu.V[x] ? 1 : 0;

	cpu.V[x] = cpu.V[y] - cpu.V[x];
	cpu.PC += 2;
}

void shl(CPU &cpu) {
	uint8_t x = (cpu.opcode & 0x0F00) >> 8;

	cpu.V[0xF] = (cpu.V[x] & 10000000) == 1 ? 1 : 0;

	cpu.V[x] <<= 1; // Left Shift by 1.
	cpu.PC += 2;
}

void sneRegister(CPU &cpu) {
	uint8_t x = (cpu.opcode & 0x0F00) >> 8;
	uint8_t y = (cpu.opcode & 0x00F0) >> 4;

	if(cpu.V[x] != cpu.V[y]) cpu.PC += 4;
	else cpu.PC += 2;
}

void ldi(CPU &cpu) {
	uint16_t nnn = cpu.opcode & 0x0FFF;

	cpu.I = nnn;
	cpu.PC += 2;
}

void jumpV0(CPU &cpu) {
	uint16_t nnn = cpu.opcode & 0x0FFF;

	cpu.PC = nnn + cpu.V[0x0];
}

void rnd(CPU &cpu) {
	uint8_t x = (cpu.opcode & 0x0F00) >> 8;
	uint8_t kk = cpu.opcode & 0x00FF;
	uint8_t rnum = rand() % 256;

	cpu.V[x] = rnum & kk;
	cpu.PC += 2;
}

void drw(CPU &cpu, MMU &mmu) {
	uint8_t x = (cpu.opcode & 0x0F00) >> 8;
	uint8_t y = (cpu.opcode & 0x00F0) >> 4;
	uint8_t xLoc = cpu.V[x];
	uint8_t yLoc = cpu.V[y];
	uint8_t spriteHeight = cpu.opcode & 0x000F;
	uint8_t pixel;

	cpu.V[0xF] = 0;
	for(int yCoord = 0; yCoord < spriteHeight; yCoord++) {
		pixel = mmu.readRAM(cpu.I + yCoord);
		for(int xCoord = 0; xCoord < 8; xCoord++) {
			if((pixel & (0x80 >> xCoord)) != 0) {
				if(mmu.gfx[yLoc + yCoord][xLoc + xCoord] == 1) {
					cpu.V[0xF] = 1;
				}
				mmu.gfx[yLoc + yCoord][xLoc + xCoord] ^= 1;
			}
		}
	}

	cpu.drawFlag = true;
	cpu.PC += 2;
}

void skp(CPU &cpu) {
	uint8_t x = (cpu.opcode & 0x0F00) >> 8;
	uint8_t vxValue = cpu.V[x];

	if(cpu.keyboard[vxValue] != 0) cpu.PC += 4;
	else cpu.PC += 2;
}

void sknp(CPU &cpu) {
	uint8_t x = (cpu.opcode & 0x0F00) >> 8;
	uint8_t vxValue = cpu.V[x];

	if(cpu.keyboard[vxValue] == 0) cpu.PC += 4;
	else cpu.PC += 2;
}

void ldDTOnRegister(CPU &cpu) {
	uint8_t x = (cpu.opcode & 0x0F00) >> 8;

	cpu.V[x] = cpu.DT;
	cpu.PC += 2;
}

void waitKey(CPU &cpu) {
	uint8_t x = (cpu.opcode & 0x0F00) >> 8;

	cpu.wasKeyPressed = false;

	for(uint8_t i = 0; i < cpu.KEYS_COUNT; i++) {
		if(cpu.keyboard[i] != 0) {
			cpu.V[x] = i;
			cpu.wasKeyPressed = true;
		}
	}

	if(!cpu.wasKeyPressed) {
		return;
	}

	cpu.PC += 2;
}

void ldRegisterOnDT(CPU &cpu) {
	uint8_t x = (cpu.opcode & 0x0F00) >> 8;

	cpu.DT = cpu.V[x];
	cpu.PC += 2;
}

void ldRegisterOnST(CPU &cpu) {
	uint8_t x = (cpu.opcode & 0x0F00) >> 8;

	cpu.ST = cpu.V[x];
	cpu.PC += 2;
}

void addI(CPU &cpu) {
	uint8_t x = (cpu.opcode & 0x0F00) >> 8;

	cpu.I += cpu.V[x];
	cpu.PC += 2;
}

void ldF(CPU &cpu) {
	uint8_t x = (cpu.opcode & 0x0F00) >> 8;

	cpu.I = cpu.V[x] * 0x5;
	cpu.PC += 2;
}

void stBCD(CPU &cpu, MMU &mmu) {
	uint8_t x = (cpu.opcode & 0x0F00) >> 8;

	// Hundreds.
	mmu.writeRAM(cpu.I, cpu.V[x] / 100);
	// Tens.
	mmu.writeRAM(cpu.I + 1, (cpu.V[x] / 10) % 10);
	// Units.
	mmu.writeRAM(cpu.I + 2, (cpu.V[x] % 100) % 10);

	cpu.PC += 2;
}

void stRegisters(CPU &cpu, MMU &mmu) {
	uint8_t endReg = (cpu.opcode & 0x0F00) >> 8;

	for(uint8_t i = 0; i <= endReg; i++) {
		mmu.writeRAM(cpu.I + i, cpu.V[i]);
	}

	cpu.PC += 2;
}

void ldRegisters(CPU &cpu, MMU &mmu) {
	uint8_t endReg = (cpu.opcode & 0x0F00) >> 8;

	for(uint8_t i = 0; i <= endReg; i++) {
		cpu.V[i] = mmu.readRAM(cpu.I + i);
	}

	cpu.PC += 2;
}