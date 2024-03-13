#ifndef _LIBRARY_TIME_H_
#define _LIBRARY_TIME_H_

#include "types.hpp"

#define TIMER_FREQUENCY 0x0ED1B768
#define TIMER_FREQUENCY_SECOND (TIMER_FREQUENCY / 4)

inline uint64_t getCurrentTime() {
	volatile uint32_t hightemp = 0, 
	high = 0, 
	low = 0;
	asm volatile(
	"mftbu %[hightemp] \n"
	"mftb %[low] \n"
	"mftbu %[high] \n"
	"cmplw %[hightemp], %[high] \n"
	"bne -0x10 \n"
	: [hightemp] "+r" (hightemp), [high] "+r" (high), [low] "+r" (low)
	:
	:);
	return ((uint64_t)high) << 32 | low;
}

class Timer {
public:
	inline Timer() : startTime(0),
	stopTime(0) {
		
	}
	
	inline Timer &init() {
		startTime = 0;
		stopTime = 0;
		return *this;
	}

	inline void Start() {
		this->startTime = getCurrentTime();
	}
	
	inline void Stop() {
		this->stopTime = getCurrentTime();
	}
	
	inline void Resume() {
		this->stopTime = 0;
	}
	
	inline void Reset() {
		this->startTime = 0;
		this->stopTime = 0;
	}
	
	inline bool elapsed(uint64_t time) {
		return getElapsedTime() > time; 
	}

	inline uint64_t getElapsedTime() {
		if(this->startTime == 0) {
			return 0;
		}
		if(this->stopTime == 0) {
			return getCurrentTime() - this->startTime;
		}
		return this->stopTime - this->startTime;
	}
	
private:
	uint64_t startTime;
	uint64_t stopTime;
};

#endif //_LIBRARY_TIME_H_