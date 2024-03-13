/*
** EPITECH PROJECT, 2024
** MamiesMod-Wii-U
** File description:
** The MallocOperator.cpp
*/

#include "MallocOperator.hpp"

void _delete(void* ptr) {
    code::Func<void, 0x0382ABB4, void*>()(ptr);
}

void* operator new[](size_t size) {
    return _new<char>(size);
}

void operator delete[](void* ptr) _GLIBCXX_USE_NOEXCEPT {
    return _delete(ptr);
}