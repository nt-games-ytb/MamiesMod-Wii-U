#ifndef __NOT_NULL_PTR_H__
#define __NOT_NULL_PTR_H__

#include "shared_ptr.hpp"

template<typename T>
class not_null_ptr : public boost::shared_ptr<T> {
public:
	
	inline not_null_ptr(T *ptr) : boost::shared_ptr<T>(ptr) {
		this->ptr = ptr;
	}

};

#endif