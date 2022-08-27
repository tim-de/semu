#ifndef _EBQVRNQ_STATE_H
#define _EBQVRNQ_STATE_H

#include<string>
#include<iostream>
#include<cstdlib>

namespace Width {
	enum Enum {
		b8 = 0,
		b16,
		b32
	};
}

class State {
	public:
		State(Width::Enum width = Width::b8, bool debug = false);
		~State(void);
		void cycle(void);
		void ramInit(const size_t length, const uint8_t* values);
		const bool isHalted() const;
	private:
		//Members
		Width::Enum _width;
		uint8_t* _ram;
		size_t _pc;
		bool _debug;
		bool _halted;
		//Methods
		const uint32_t ramGet(const size_t addr) const;
		void ramSet(const uint32_t value, const size_t addr);
};

#endif
