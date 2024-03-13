#pragma once

#include "mem.hpp"
#include "../Vector.hpp"

void writeMem(uint32_t addr, uint32_t value);

uint32_t branchTo(uint32_t origin, void* to);

void* setupRealInstructions(uint32_t* buffer, uint32_t startAddr);

void* safeInstructions(uint32_t startFunction);

#define DECL_HOOK(func, ...) \
    void hook_##func(__VA_ARGS__) 

void _TEST(uint32_t addr, uint32_t funcPtr, int offset);

#define HOOK(addr, func, offset) \
    _TEST(addr, (uint32_t) hook_##func, offset);

// Only Works when the Address hasn't been called yet for Example
// 0x02000000 blr
// If 0x02000000 gets Called it can't be Overwritten with for Example li r3, 0
// But Before it gets Called it can be Overwritten with for Example li r3, 0
#define REPLACE(sAddr, name) REPLACE_EX(sAddr, name, real_instructions)
#define REPLACE_EX(sAddr, name, ins_list)                       \
    auto lambda_##name = [&]() {                                \
        void* _instructions = safeInstructions(sAddr);          \
        writeMem(sAddr, branchTo(sAddr, (void*) &(my_##name))); \
        void** __data = (void**) new uint32_t[2];               \
        __data[0] = (void*) &(exec_##name);                     \
        __data[1] = _instructions;                              \
        ins_list.push_back(__data);                             \
        real_##name = exec_##name;                              \
    };                                                          \
    lambda_##name();                                                         

/*
 * Original code by Chadderz
 *
 * #define declareFunctionHook(returnType, functionName, ...) \
 *      returnType (* real_ ## functionName)(__VA_ARGS__) __attribute__((section(".data"))); \
 *      returnType my_ ## functionName(__VA_ARGS__)
 *
 */

// Found in WUPS and then TCPGecko (Expanded by david.xf) 
#define DECL_FUNCTION(res, name, ...)                                \
    res(*real_##name)(__VA_ARGS__) __attribute__((section(".ext"))); \
    res exec_##name(__VA_ARGS__) {                                   \
        asm volatile("_" #name "Start:");                            \
        asm volatile("stwu 1, -0x100(1)");                           \
        asm volatile("mflr 0");                                      \
        asm volatile("stw 0, 0x104(1)");                             \
        asm volatile("stw 30, 0x20(1)");                             \
        asm volatile("stw 29, 0x24(1)");                             \
        asm volatile("stw 28, 0x28(1)");                             \
        asm volatile("stw 27, 0x2C(1)");                             \
        asm volatile("stw 26, 0x30(1)");                             \
        asm volatile("stw 25, 0x34(1)");                             \
        asm volatile("stw 24, 0x38(1)");                             \
        asm volatile("stw 23, 0x3C(1)");                             \
        asm volatile("stw 22, 0x40(1)");                             \
        asm volatile("stw 21, 0x44(1)");                             \
        asm volatile("stw 20, 0x48(1)");                             \
        asm volatile("lis 30, 0x104D");                              \
        asm volatile("ori 30, 30, 0x4DDC");                          \
        asm volatile("lwz 30, 0(30)");                               \
        asm volatile("lwz 30, 0(30)");                               \
        asm volatile("lwz 29, 0(30)");                               \
        asm volatile("lwz 28, 4(30)");                               \
        asm volatile("mr 27, 28");                                   \
        asm volatile("li 26, 0");                                    \
        asm volatile("li 25, 4");                                    \
        asm volatile("_" #name ":");                                 \
        asm volatile("mullw 24, 26, 25");                            \
        asm volatile("add 23, 29, 24");                              \
        asm volatile("lwz 23, 0(23)");                               \
        asm volatile("lis 22, " "_" #name "Start@ha");               \
        asm volatile("addi 22, 22, " "_" #name "Start@l");           \
        asm volatile("lwz 30, 0(23)");                               \
        asm volatile("cmpw 22, 30");                                 \
        asm volatile("beq _" #name "Found");                         \
        asm volatile("addi 26, 26, 1");                              \
        asm volatile("b _" #name);                                   \
        asm volatile("_" #name "Found:");                            \
        asm volatile("lwz 21, 4(23)");                               \
        asm volatile("mtctr 21");                                    \
        asm volatile("bctrl");                                       \
        asm volatile("lwz 30, 0x20(1)");                             \
        asm volatile("lwz 29, 0x24(1)");                             \
        asm volatile("lwz 28, 0x28(1)");                             \
        asm volatile("lwz 27, 0x2C(1)");                             \
        asm volatile("lwz 26, 0x30(1)");                             \
        asm volatile("lwz 25, 0x34(1)");                             \
        asm volatile("lwz 24, 0x38(1)");                             \
        asm volatile("lwz 23, 0x3C(1)");                             \
        asm volatile("lwz 22, 0x40(1)");                             \
        asm volatile("lwz 21, 0x44(1)");                             \
        asm volatile("lwz 20, 0x48(1)");                             \
        asm volatile("addi 1, 1, 0x100");                            \
        asm volatile("lwz 0, 4(1)");                                 \
        asm volatile("mtlr 0");                                      \
        asm volatile("blr");                                         \
    }                                                                \
    res my_##name(__VA_ARGS__)

void replaceInstructions(uint32_t addr, misc::Vector<uint32_t> _instructions);

void InitWups(void);