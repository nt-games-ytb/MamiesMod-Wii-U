#ifndef __STD_BASIC_STRING_H__
#define __STD_BASIC_STRING_H__

#include <cstddef>
#include <cassert>
#include "types.hpp"

#define _sprintf  ((int32_t(*)(char*, const char*, ...))0x0382E03C)
#define swprintf ((int32_t(*)(wchar_t*, int32_t, const wchar_t*, ...))0x0382C8C0)
#define swscanf  ((int32_t(*)(const wchar_t*, const wchar_t*, ...))0x0382B610)
#define _sscanf ((int32_t(*)(const char*, const char*, ...))0x0382F634)

namespace link {
    static const uint32_t __ghs_strcmp                                                                                                                                                                                        = 0x0382CB74;
    static const uint32_t _wcscpy                                                                                                                                                                                             = 0x0382C734;
    static const uint32_t _wcslen                                                                                                                                                                                             = 0x0382C718;
    static const uint32_t _wcscmp                                                                                                                                                                                             = 0x0382C75C;
    static const uint32_t _strlen                                                                                                                                                                                             = 0x034C11B0;
    static const uint32_t assign__Q2_3std78basic_string__tm__58_wQ2_3std20char_traits__tm__2_wQ2_3std18allocator__tm__2_wFPCZ1ZQ4_3std25_String_val__tm__7_Z1ZZ3Z5_Alty9size_type_RQ2_3std30basic_string__tm__10_Z1ZZ2ZZ3Z_26 = 0x030E8BC4;
}

namespace std {

    /*

    class string {
    private:

        static inline std::string *Ctor(std::string *ptr, const char *cstr) {
            return ((std::string*(*)(std::string*, const char*))0x027B0A40)
            (ptr, cstr);
        }

    public:

        inline string(const char *cstr) {
            std::string::Ctor(this, cstr);
        }
    
    };

    class wstring {
    private:

        static inline std::wstring *Ctor(std::wstring *ptr, const wchar_t *wcstr) {
            return ((std::wstring*(*)(std::wstring*, const wchar_t*))0x020B08D4)
            (ptr, wcstr);
        }
    
    public:

        inline wstring(const wchar_t *wcstr) {
            std::wstring::Ctor(this, wcstr);
        }
    
    };

    */

    template <typename T>
    class basic_string {
    private:

        /*
        static inline std::basic_string<char> *Ctor(std::basic_string<char> *ptr, const char *cstr) {
            return ((std::basic_string<char>*(*)(std::basic_string<char>*, const char*))0x027B0A40)
            (ptr, cstr);
        }
        */

        static inline basic_string<wchar_t> *Ctor(basic_string<wchar_t> *ptr, const wchar_t *wcstr) {
            return ((basic_string<wchar_t>*(*)(basic_string<wchar_t>*, const wchar_t*))0x020B08D4)
            (ptr, wcstr);
        }

        unsigned int unk_0x0;
        unsigned int unk_0x4;
        unsigned int unk_0x8;
        unsigned int unk_0xC;
        unsigned int unk_0x10;
        T *buffer;
        unsigned int length;
        unsigned int capacity;

    public:

        inline basic_string() {
            
        }
        
        inline basic_string(const char *cstr) {
            basic_string<char>::Ctor(this, cstr);
        }

        inline basic_string(const wchar_t *wcstr) {
            basic_string<wchar_t>::Ctor(this, wcstr);
        }

        T *c_str() {
            if(length > 7) {
                return this->buffer;
            }
            return (wchar_t*)((uint32_t)this + 4);
        }

        unsigned int size() {
            return this->length;
        }

        inline void concat(const wchar_t *wcstr) {
            wchar_t result[100];
            basic_string<wchar_t>(result, 100, L"%ls%ls", this->c_str(), wcstr);
            this = result;
        }

        /*

        inline std::basic_string<wchar_t> assign(const wchar_t *wcstr, int32_t size) {
            ((void(*)(std::basic_string<wchar_t>&, const wchar_t*, int32_t))link::assign__Q2_3std78basic_string__tm__58_wQ2_3std20char_traits__tm__2_wQ2_3std18allocator__tm__2_wFPCZ1ZQ4_3std25_String_val__tm__7_Z1ZZ3Z5_Alty9size_type_RQ2_3std30basic_string__tm__10_Z1ZZ2ZZ3Z_26)
            (this, wcstr, size);
            return *this;
        }

        */

    };

}

/*
inline int32_t wcslen(const wchar_t *wcstr) {
    return ((int32_t(*)(const wchar_t*))link::_wcslen)
    (wcstr);
}

inline void wcscpy(wchar_t *table, const wchar_t *wc) {
    return ((void(*)(wchar_t*, const wchar_t*))link::_wcscpy)
    (table, wc);
}

inline int32_t wcscmp(const wchar_t *wcstr_1, const wchar_t *wcstr_2) {
    return ((int32_t(*)(const wchar_t*, const wchar_t*))link::_wcscmp)
    (wcstr_1, wcstr_2);
}

inline int32_t _strcmp(const char *cstr_1, const char *cstr_2) {
    return ((int32_t(*)(const char*, const char*))link::__ghs_strcmp)
    (cstr_1, cstr_2);
}

inline int32_t strlen(const char *c) {
    return ((int32_t(*)(const char*))link::_strlen)
    (c);
}*/

#endif