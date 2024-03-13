#pragma once

#include <cmath>
#include "FloatConverter.hpp"
#include "../../miscellaneous/code/code.hpp"

#define GET_LR(valName)                       \
    uint32_t valName;                         \
    asm volatile("mflr %0" : "=r" (valName)); 

wchar_t* getNNID();

wchar_t* getEffectName(int id);

void mc_wcscpy(const wchar_t* out, const wchar_t* in);

int mc_wcslen(const wchar_t* in);

template<typename... Args>
static void mc_swprintf(const wchar_t* outputPointer, uint32_t size, const wchar_t* __format, Args... args) {
    code::Func<void, 0x0382C8C0, const wchar_t*, uint32_t, const wchar_t*, Args...>()(outputPointer, size, __format, args...);
}

template<typename... Args>
static void mc_snprintf(const char* outputPointer, uint32_t size, const char* __format, Args... args) {
    code::Func<void, 0x0382DF78, const char*, uint32_t, const char*, Args...>()(outputPointer, size, __format, args...);
}

float degToRad(float deg);

float radToDeg(float rad);

char* wcharToChar(const wchar_t* str, int length);

wchar_t* charToWChar(const char* str, int length);

// https://stackoverflow.com/questions/2249110/how-do-i-make-a-portable-isnan-isinf-function
int isinf(double x);

// https://stackoverflow.com/questions/2249110/how-do-i-make-a-portable-isnan-isinf-function
int isnan(double x);

char* toCStr(float input, int decimalPlaces);