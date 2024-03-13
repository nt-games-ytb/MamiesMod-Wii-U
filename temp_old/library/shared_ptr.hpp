#ifndef __BOOST_SHARED_PTR_H__
#define __BOOST_SHARED_PTR_H__

#include "memory.hpp"

class ClientboundChatPacket;

namespace boost {

	template<typename T>
	class sp_counted_impl {
	public:

		int use_count;
		int weak_count;
		void *vtable;
		T *instance;

		sp_counted_impl(T *ptr) {
			use_count  = 1;
			weak_count = 1;
			instance   = ptr;
			vtable = getVtbl();
		}

		void *operator new(unsigned int size) {
			return mem::malloc(size);
		}

		void *getVtbl() {
			return nullptr;
		}

	};

	template<>
	inline void *sp_counted_impl<ClientboundChatPacket>::getVtbl() {
		return (void*)0x10576D68;
	}

	template<typename T>
	class shared_ptr {
	public:
		T *ptr;
		sp_counted_impl<T> *detail;
		
		inline shared_ptr() : 
			ptr(nullptr),
			detail(nullptr) {
			
		}
		
		inline shared_ptr(T *ptr) : detail(nullptr) {
			this->ptr = ptr;
			this->detail = new sp_counted_impl<T>(ptr);
		}
		
		inline T *get() {
			return this->ptr;
		}
		
		inline T operator* () {
			return *this->ptr;
		}
		
		inline T *operator-> () {
			return this->ptr;
		}
		
		inline operator bool() {
			return get() != nullptr;
		}
	};

}

#endif //__BOOST_SHARED_PTR_H_