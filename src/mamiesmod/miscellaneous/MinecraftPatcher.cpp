#include "MinecraftPatcher.hpp"
#include "MinecraftDataProvider.hpp"
#include "kernel.h"

MinecraftPatcher *MinecraftPatcher::instance = NULL;
char MinecraftPatcher::executable_buffer[sizeof(int) * 1024];
char * MinecraftPatcher::executable_buffer_begin = executable_buffer;

//MinecraftPatcher::MinecraftPatcher() {}

void MinecraftPatcher::patchFunctions() {
    this->patchedFunctions = true;
}

void * MinecraftPatcher::replaceFunction(void * original_func, void * my_func) {
    if((unsigned int)original_func % 4 != 0 || (unsigned int)my_func % 4 != 0) {
        return NULL;
    }

    int jump_length = (int)my_func - (int)original_func;

    if(jump_length > BRANCH_MAX_DISTANCE_POSITIVE || jump_length < BRANCH_MAX_DISTANCE_NEGATIVE) {
        int big_jump[4];
        big_jump[0] = 0x3D800000 | ((unsigned int)my_func >> 16); // lis r12, my_func@h
        big_jump[1] = 0x618C0000 | ((int)my_func & 0xFFFF); // ori r12, r12, my_func@l
        big_jump[2] = 0x7D8903A6; // mtctr r12
        big_jump[3] = 0x4E800420; // bctr

        void * destination = MinecraftDataProvider::getInstance()->allocateExecutable(sizeof(big_jump));
        kernel_memcpy_flush(destination, big_jump, sizeof(big_jump));

        jump_length = (int)destination - (int)original_func;
    }

    int real_func_buffer[2];
    void * real_func = MinecraftDataProvider::getInstance()->allocateExecutable(sizeof(real_func_buffer));
    real_func_buffer[0] = *(int*)original_func;
    real_func_buffer[1] = INSTRUCTION_BRANCH | ((((int)original_func + 4) - ((int)real_func + 4)) & INSTRUCTION_BRANCH_OFFSET_BIT);
    kernel_memcpy_flush(real_func, real_func_buffer, sizeof(real_func_buffer));

    int instr_jump_to_my_func = INSTRUCTION_BRANCH | (jump_length & INSTRUCTION_BRANCH_OFFSET_BIT);
    kernel_write_value(original_func, instr_jump_to_my_func);

    return real_func;
}

void MinecraftPatcher::injectInstruction(void *dest, void *instruction, std::size_t instr_size) {
    if((unsigned int)dest % 4 != 0 || instr_size % 4 != 0) {
        return;
    }

    int inject_size = instr_size + sizeof(int) * 2;

    int *allocated_space = (int *)MinecraftDataProvider::getInstance()->allocateExecutable(inject_size);
    int jump_length = (int)allocated_space - (int)dest;
    int jump_return_length = ((unsigned int)dest + sizeof(int)) - (((unsigned int)allocated_space + sizeof(unsigned int) + instr_size));
    unsigned int instr_jump_to_injected = INSTRUCTION_BRANCH | (jump_length & INSTRUCTION_BRANCH_OFFSET_BIT);
    unsigned int instr_return_to_original = INSTRUCTION_BRANCH | (jump_return_length & INSTRUCTION_BRANCH_OFFSET_BIT);
    unsigned int instr_real = *(int *)dest;

    if(jump_length > BRANCH_MAX_DISTANCE_POSITIVE || jump_length < BRANCH_MAX_DISTANCE_NEGATIVE) {
        return;
    }

    if(jump_return_length > BRANCH_MAX_DISTANCE_POSITIVE || jump_return_length < BRANCH_MAX_DISTANCE_NEGATIVE) {
        return;
    }

    /*unsigned int *inject = new unsigned int(inject_size / sizeof(unsigned int));
    inject[0] = instr_real;
    memcpy(inject + 1, instruction, instr_size);
    inject[inject_size / sizeof(unsigned int) - 1] = instr_return_to_original;

    kernel_memcpy_flush(allocated_space, inject, inject_size);
    kernel_write_value(dest, instr_jump_to_injected);

    delete inject;*/

    kernel_write_value(allocated_space, instr_real);
    allocated_space++;
    kernel_memcpy_flush(allocated_space, instruction, instr_size);
    allocated_space += instr_size / sizeof(unsigned int);
    kernel_write_value(allocated_space, instr_return_to_original);

    kernel_write_value(dest, instr_jump_to_injected);
}