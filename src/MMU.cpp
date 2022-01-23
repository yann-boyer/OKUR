/*
This file is a part of OKUR.
This file contains code to emulate
Memory module of the Chip8.

Copyright (c) 2022 - Yann BOYER.
*/
#include "MMU.hpp"

MMU::MMU() {
	std::fill(ram.begin(), ram.end(), 0x0);
	for(uint8_t y = 0; y < 32; y++) {
		for(uint8_t x = 0; x < 64; x++) {
			gfx[y][x] = 0;
		}
	}
	std::copy(FONTSET.begin(), FONTSET.end(), ram.begin());
}

uint8_t MMU::readRAM(uint16_t addr) {
	if(addr > RAM_SIZE) {
		std::cerr << "Memory Read Error : address out of range !" << std::endl;
		return 0x0;
	}

	return ram[addr];
}

void MMU::writeRAM(uint16_t addr, uint8_t value) {
	if(addr > RAM_SIZE) {
		std::cerr << "Memory Write Error : address out of range !" << std::endl;
		return;
	}

	ram[addr] = value;
}

void MMU::loadROM(const std::string &romPath) {
	std::ifstream romFile(romPath, std::ios::in | std::ios::binary);

	std::vector<char> romData((std::istreambuf_iterator<char>(romFile)), std::istreambuf_iterator<char>());
	// Close the file, we don't need it anymore.
	romFile.close();

	unsigned long romLength = romData.size();
	if((PROGRAM_END_ADDR - PROGRAM_START_ADDR) >= romLength) {
		std::copy(romData.begin(), romData.end(), ram.begin() + PROGRAM_START_ADDR);
		std::cout << "ROM successfuly loaded into memory !" << std::endl;
	} else {
		std::cerr <<  "This ROM file is too large to fit into memory !" << std::endl;
		exit(EXIT_FAILURE);
	}
}