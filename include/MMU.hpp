/*
This file is a part of OKUR.
This file is a header.

Copyright (c) 2022 - Yann BOYER.
*/
#ifndef MMU_HPP
#define MMU_HPP

#include<iostream>
#include<cstdlib>
#include<array>
#include<vector>
#include<fstream>
#include<sstream>
#include<string>

class MMU {
	public:
		MMU();
		std::array<std::array<uint8_t, 64>, 32> gfx;

		// Functions.
		uint8_t readRAM(uint16_t addr);
		void writeRAM(uint16_t addr, uint8_t value);
		void loadROM(const std::string &romPath);

	private:
		static const uint16_t RAM_SIZE = 0x1000;
		static const uint16_t PROGRAM_START_ADDR = 0x200;
		static const uint16_t PROGRAM_END_ADDR = 0xFFF;
		static const uint8_t FONTSET_SIZE = 80;
		std::array<uint8_t, RAM_SIZE> ram;
		static constexpr std::array<uint8_t, FONTSET_SIZE> FONTSET = {
			// 0
			0xF0, 0x90, 0x90, 0x90, 0xF0,
			// 1
			0x20, 0x60, 0x20, 0x20, 0x70,
			// 2
			0xF0, 0x10, 0xF0, 0x80, 0xF0,
			// 3
			0xF0, 0x10, 0xF0, 0x10, 0xF0,
			// 4
			0x90, 0x90, 0xF0, 0x10, 0x10,
			// 5
			0xF0, 0x80, 0xF0, 0x10, 0xF0,
			// 6
			0xF0, 0x80, 0xF0, 0x90, 0xF0,
			// 7
			0xF0, 0x10, 0x20, 0x40, 0x40,
			// 8
			0xF0, 0x90, 0xF0, 0x90, 0xF0,
			// 9
			0xF0, 0x90, 0xF0, 0x10, 0xF0,
			// A
			0xF0, 0x90, 0xF0, 0x90, 0x90,
			// B
			0xE0, 0x90, 0xE0, 0x90, 0xE0,
			// C
			0xF0, 0x80, 0x80, 0x80, 0xF0,
			// D
			0xE0, 0x90, 0x90, 0x90, 0xE0,
			// E
			0xF0, 0x80, 0xF0, 0x80, 0xF0,
			// F
			0xF0, 0x80, 0xF0, 0x80, 0x80
		};
};

#endif