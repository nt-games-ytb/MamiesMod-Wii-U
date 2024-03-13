#include <cstddef>
#include <cassert>
#include "../../../../../temp/library/types.hpp"

namespace linkmc {
    static const uint32_t _wcscpy                                                                                                                                                                                             = 0x0382C734;
}

inline void wcscppy(wchar_t* table, const wchar_t* wc) {
    return ((void(*)(wchar_t*, const wchar_t*))linkmc::_wcscpy)
        (table, wc);
}