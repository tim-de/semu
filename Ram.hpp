#ifndef _FOGEOQA_RAM_H
#define _FOGEOQA_RAM_H

#include<string>
#include<iostream>

#include "Utils.hpp"

class Ram {
	public:
		Ram(Width::Enum width);
		~Ram();
		const uint32_t get(const uint32_t addr) const;
		void set(const uint32_t value, const uint32_t addr);
		void init(const uint32_t length, const uint8_t* values);
	private:
		Width::Enum _width;
		size_t _ramsize;
		uint8_t* _ram;
		const int getByteCount(const uint32_t addr) const;
};

#endif
