/*
This file is a part of OKUR.
This file is a header.

Copyright (c) 2022 - Yann BOYER.
*/
#ifndef CPU_INSTRUCTIONS_HPP
#define CPU_INSTRUCTIONS_HPP

#include<iostream>
#include<cstdlib>

#include "MMU.hpp"
#include "CPU.hpp"

void cls(CPU &cpu, MMU &mmu);
void ret(CPU &cpu);
void jump(CPU &cpu);
void call(CPU &cpu);
void seByte(CPU &cpu);
void sneByte(CPU &cpu);
void seRegister(CPU &cpu);
void ldByte(CPU &cpu);
void addByte(CPU &cpu);
void ldRegToReg(CPU &cpu);
void logicalOR(CPU &cpu);
void logicalAND(CPU &cpu);
void exclusiveOR(CPU &cpu);
void addRegisterCarry(CPU &cpu);
void sub(CPU &cpu);
void shr(CPU &cpu);
void subn(CPU &cpu);
void shl(CPU &cpu);
void sneRegister(CPU &cpu);
void ldi(CPU &cpu);
void jumpV0(CPU &cpu);
void rnd(CPU &cpu);
void drw(CPU &cpu, MMU &mmu);
void skp(CPU &cpu);
void sknp(CPU &cpu);
void ldDTOnRegister(CPU &cpu);
void waitKey(CPU &cpu);
void ldRegisterOnDT(CPU &cpu);
void ldRegisterOnST(CPU &cpu);
void addI(CPU &cpu);
void ldF(CPU &cpu);
void stBCD(CPU &cpu, MMU &mmu);
void stRegisters(CPU &cpu, MMU &mmu);
void ldRegisters(CPU &cpu, MMU &mmu);

#endif