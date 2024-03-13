#ifndef __NN_H__
#define __NN_H__

#include "types.hpp"

namespace nn {

    namespace fp {
        
        #pragma longcall(1) 
        int32_t GetFriendList(uint32_t *return_0, uint32_t *return_1, uint32_t friendsMin, uint32_t friendsMax) asm("0x038999FC");
        #pragma longcall(0)

        #pragma longcall(1) 
        int32_t GetFriendAccountId(char *idOut, uint32_t *return_0, uint32_t friendsMax) asm("0x03899CCC");
        #pragma longcall(0)
        
        #pragma longcall(1)
        void UpdateGameModeDescription(const wchar_t *str) asm("0x0389B018");
        #pragma longcall(0)
    }

    namespace nex {

        class StringConversion {
        public:

            #pragma longcall(1) 
            static inline void TToUtf8(wchar_t *wc, char *c, uint32_t length) asm("0x03899CCC");
            #pragma longcall(0) 

        };

    }

}

#endif