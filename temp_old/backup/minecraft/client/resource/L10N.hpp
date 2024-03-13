#ifndef __L10N_H__
#define __L10N_H__

#include <cstddef>
#include <cassert>
#include "../../../../../temp/library/types.hpp"
#include "wcscpy.hpp"

namespace linkmc {
    static const uint32_t GetString__4L10NSFi = 0x02F24864;
}

class L10N {
public:

    static inline wchar_t *GetString(int32_t table) {
        return ((wchar_t*(*)(int32_t))linkmc::GetString__4L10NSFi)
        (table);
    }

    static inline void ReplaceString(uint32_t table, const wchar_t *target) {
        wcscppy((wchar_t*)L10N::GetString(table), target);
    }

};

#endif