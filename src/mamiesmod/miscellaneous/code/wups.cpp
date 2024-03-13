/*
** EPITECH PROJECT, 2024
** MamiesMod-Wii-U
** File description:
** The wups.cpp
*/

#include "wups.hpp"

void writeMem(uint32_t addr, uint32_t value) {
    code::Mem(addr).as<uint32_t>() = value;
}

uint32_t branchTo(uint32_t origin, void* to) {
    uint32_t _addr = (uint32_t) to;
    uint32_t temp = (_addr - origin);
    if (0x48000000 > (0x48000000 + temp)) {
        return 0x4C000000 + temp;
    } else {
        return 0x48000000 + temp;
    }
}

misc::Vector<void**> real_instructions;
const int MaxTest = 0x100;
int __test_index = 0;
uint32_t instructionBuffer[MaxTest];

void* setupRealInstructions(uint32_t* buffer, uint32_t startAddr) {
    uint32_t endFor = (uint32_t) &instructionBuffer[__test_index];
    for (int i = 0; i < buffer[0] + 1; i++) {
        uint32_t writeAddr = endFor + (i * 4);
        if (buffer[1 + i] == 0xFFFFFFFF) writeMem(writeAddr, branchTo(writeAddr, (void*) (startAddr + 4)));
        else                             writeMem(writeAddr, buffer[1 + i]);
    }

    __test_index += (buffer[0] + 1);

    return (void*) (endFor);
}

void* safeInstructions(uint32_t startFunction) {
    misc::Vector<uint32_t> instructions;
    instructions.push_back(code::Mem(startFunction).as<uint32_t>());
    instructions.push_back(0xFFFFFFFF);

    uint32_t* ret = new uint32_t[instructions.getSize() + 1];
    int i = 1;
    for (uint32_t t : instructions) {
        ret[i++] = t;
    }

    ret[0] = instructions.getSize();
    return setupRealInstructions(ret, startFunction);
}

void _TEST(uint32_t addr, uint32_t funcPtr, int offset) {
    uint32_t hookPtr = (uint32_t) &instructionBuffer[__test_index];
    uint32_t fFuncPtr = (uint32_t) funcPtr;
    writeMem(addr, branchTo(addr, (void*) hookPtr));
    writeMem(hookPtr + 0x0,  0x4E800421);                                              // bctrl;
    writeMem(hookPtr + 0x4,  0x3D800000 | (fFuncPtr >> 16));                           // lis r12, 0x;
    writeMem(hookPtr + 0x8,  0x618C0000 | (fFuncPtr & 0xFFFF));                        // ori r12, r12, 0x;
    writeMem(hookPtr + 0xC,  0x7D8903A6);                                              // mtctr r12;
    writeMem(hookPtr + 0x10, 0x4E800421);                                              // bctrl;
    writeMem(hookPtr + 0x14, branchTo(hookPtr + 0x14, (void*) (addr + 0x4 + offset))); // b addr+0x4;
    __test_index += 8;
}

void replaceInstructions(uint32_t addr, misc::Vector<uint32_t> _instructions) {
    uint32_t start = (uint32_t) &instructionBuffer[__test_index];
    uint32_t originalInstr = code::Mem(addr).as<uint32_t>();
    writeMem(addr, branchTo(addr, (void*) start));
    for (uint32_t _instr : _instructions) {
        instructionBuffer[__test_index++] = _instr;
    }
    instructionBuffer[__test_index++] = originalInstr;
    instructionBuffer[__test_index] = branchTo((uint32_t) &instructionBuffer[__test_index], (void*) (addr + 4));
    __test_index++;
}

void InitWups(void) {
    uint32_t* data = new uint32_t[0x10]; // Extra Space, if more Data is needed
    code::Mem(0x104D4DDC).as<uint32_t>() = (uint32_t) data;
    data[0] = (uint32_t) &real_instructions;
}