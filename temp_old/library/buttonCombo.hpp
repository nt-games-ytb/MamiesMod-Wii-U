#ifndef _LIBRARY_BUTTON_COMBO_H_
#define _LIBRARY_BUTTON_COMBO_H_

#include "timer.hpp"

class ButtonComboEntry {
private:
	bool release;
	int32_t cur_btn;
	int32_t max_btn;
	uint32_t prevBtn;
	bool pressed;
	Timer timer;
	uint32_t btns[16];
public:

	inline
	void start() {
		cur_btn = 0;
		timer.Start();
	}

	inline
	void setButton(int idx, uint32_t btn_hold) {
		btns[idx] = btn_hold;
	}

	inline
	void setMax(int32_t max) {
		max_btn = max;
	}

	inline
	void setRelease(bool flag) {
		release = flag;
	}

	inline
	bool check(uint32_t btn) {
		uint32_t curbtn = btns[cur_btn];
		if(timer.elapsed(TIMER_FREQUENCY / 4 / 10 * 4)) {
			reset();
			return false;
		}
		if(!pressed &&
			(btn & curbtn) == curbtn) {
			if(++cur_btn >= max_btn) {
				reset();
				return true;
			}
			if(release) {
				pressed = true;
				prevBtn = curbtn;
			}
			timer.Start();
		} else if((prevBtn & btn) == 0) {
			pressed = false;
		}
		return false;
	}
    
	inline
	void reset() {
		timer.Start();
		cur_btn = 0;
	}
};

template<uint32_t BUTTONS>
class ButtonCombo {
private:
	bool release;
	int32_t cur_btn;
	uint32_t prevBtn;
	bool pressed;
	Timer timer;
	uint32_t btns[BUTTONS];
public:

	inline ButtonCombo &init() {
		timer.init();
		return *this;
	}

	inline
	void start() {
		cur_btn = 0;
		timer.Start();
	}

	inline
	ButtonCombo &setButton(int idx, uint32_t btn_hold) {
		if(idx < BUTTONS) {
			btns[idx] = btn_hold;
		}
		return *this;
	}

	inline
	ButtonCombo &setRelease(bool flag) {
		release = flag;
		return *this;
	}

	inline
	bool check(uint32_t btn) {
		uint32_t curbtn = btns[cur_btn];
		if(timer.elapsed(TIMER_FREQUENCY / 4 / 10 * 4)) {
			reset();
			return false;
		}
		if(!pressed &&
			(btn & curbtn) == curbtn) {
			if(++cur_btn >= BUTTONS) {
				reset();
				return true;
			}
			if(release) {
				pressed = true;
				prevBtn = curbtn;
			}
			timer.Start();
		} else if((prevBtn & btn) == 0) {
			pressed = false;
		}
		return false;
	}
    
	inline
	void reset() {
		timer.Start();
		cur_btn = 0;
	}
};

#endif //_LIBRARY_BUTTON_COMBO_H_