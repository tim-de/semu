#include<string>
#include<iostream>

#include"Ram.h"

Ram::Ram(Width::Enum width):
	_width(width)
{
	// This line allocates the correct amount of heap memory
	// to store the emulated RAM. It is calculated by converting
	// the Width::Enum type to the actual bitwidth (8 << _width)                                  
	// and then by calculating 2^n where n is the bitwidth
	_ram = new uint8_t[1 << (8 << _width)];
	if (_ram == NULL) {
		std::cerr << "ERROR: Failed to initialise ram" << std::endl;
		exit(EXIT_FAILURE);
	}
}

Ram::~Ram()
{
	delete _ram;
}

const uint32_t Ram::get(const uint32_t addr) const
{
	uint32_t loc, value;
	int s, i;
	loc = addr << _width;
	s = 1 << _width;
	value = 0;
	for (i = 0; i < s; i++) {
		value = value >> 8;
		value &= 0x00ffffff;
		value |= _ram[loc+i] << 24;
	}
	switch (_width) {
		case Width::b8:
			value = value >> 24;
			break;
		case Width::b16:
			value = value >> 16;
			break;
		case Width::b32:
			break;
	}
	value &= (1 << (8 << _width)) - 1;
	return value;
}

void Ram::set(const uint32_t value, const uint32_t addr)
{
	uint32_t loc;
	int s, i;
	loc = addr << _width;
	s = 1 << _width;
	for (i = 0; i < s; i++) {
		_ram[loc+i] = value >> (8 * i);
	}
}

void Ram::init(const uint32_t length, const uint8_t* values)
{
	for (size_t i=0; i < length; i++) {
		_ram[i] = values[i];
	}
}
