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

template<typename T>
T* _new(size_t size) {
    T* t = code::Func<T*, 0x0382AACC, size_t>()(sizeof(T) * size);
    memset(t, 0, sizeof(T) * size);
    return t;
}

template<typename T>
T* _new1(T t) {
    T* allocDest = _new<T>(1);
    memcpy(allocDest, &t, sizeof(T));
    return allocDest;
}

void* operator new(size_t size) {
    return _new<char>(size);
}

void* operator new[](size_t size) {
    return _new<char>(size);
}

void operator delete(void* ptr) _GLIBCXX_USE_NOEXCEPT {
    return _delete(ptr);
}

void operator delete[](void* ptr) _GLIBCXX_USE_NOEXCEPT {
    return _delete(ptr);
}