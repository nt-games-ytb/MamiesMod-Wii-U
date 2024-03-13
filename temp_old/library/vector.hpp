#ifndef __STD_VECTOR_H__
#define __STD_VECTOR_H__

#include "types.hpp"
#include "basic_string.hpp"

namespace link {
    static const uint32_t __CPR110__push_back__Q2_3std82vector__tm__68_P17FriendSessionInfoQ2_3std38allocator__tm__21_PJ36JFRCZ1Z_v                                                                             = 0x0346dc3c;
    static const uint32_t __CPR247__push_back__Q2_3std218vector__tm__203_Q2_3std78basic_string__tm__58_wQ2_3std20char_traits__tm__2_wQ2_3std18allocator__tm__2_wQ2_3std105allocator__tm__88_Q2_3stdJ44JFRCZ1Z_v = 0x0200F670;
}

class FriendSessionInfo;

namespace std {

    template<typename T>
    class vector {
    public:
        
        uint32_t unk_0x0;
        T *start;
        T *finish;
        T *end_of_storage;
        
        inline T operator[](int i) {
            return this->start[i];
        }
        
        inline T *begin() {
            return this->start;
        }
        
        inline T *end() {
            return this->finish;
        }
        
        inline int32_t size() {
            return ((int32_t)finish - (int32_t)start) / sizeof(T);
        }
        
        /*
        inline void push_back(T const &wcstr) {
            
        }
        */

        inline void push_back(T info) {
            
        }

    };

    /*
    template<>
    inline void vector<std::basic_string<wchar_t>>::push_back(std::basic_string<wchar_t> const &wcstr) {
        return ((void(*)(vector<std::basic_string<wchar_t>>*, std::basic_string<wchar_t> const &))link::__CPR247__push_back__Q2_3std218vector__tm__203_Q2_3std78basic_string__tm__58_wQ2_3std20char_traits__tm__2_wQ2_3std18allocator__tm__2_wQ2_3std105allocator__tm__88_Q2_3stdJ44JFRCZ1Z_v)
        (this, wcstr);
    }
    */

    template<>
    inline void vector<FriendSessionInfo *>::push_back(FriendSessionInfo *info) {
        return ((void(*)(vector<FriendSessionInfo *>*, FriendSessionInfo *))link::__CPR110__push_back__Q2_3std82vector__tm__68_P17FriendSessionInfoQ2_3std38allocator__tm__21_PJ36JFRCZ1Z_v)
        (this, info);
    }

}


	
#endif