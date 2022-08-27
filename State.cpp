#include<string>
#include<iostream>
#include<cstdlib>

#include"State.h"

State::State(Width::Enum width, bool debug):
	_width(width),
	_pc(0),
	_debug(debug)
{
	// This line allocates the correct amount of heap memory
	// to store the emulated RAM. It is calculated by converting
	// the Width::Enum type to the actual bitwidth (8 << _width)
	// and then by calculating 2^n where n is the bitwidth
	_ram = (uint8_t*) calloc(1 << (8 << _width), sizeof(uint8_t));
	if (_ram == NULL) {
		exit(EXIT_FAILURE);
	}
}

State::~State(void)
{
	free(_ram);
}

void State::cycle(void)
{
	uint32_t b;
	size_t A, B, C;

	A = (size_t) ramGet(_pc);
	B = (size_t) ramGet(_pc+1);
	C = (size_t) ramGet(_pc+2);

	if (_debug) {
		std::cout << _pc << ": ";
		std::cout << A << " ";
		std::cout << B << " ";
		std::cout << C << std::endl;
	}

	b = ramGet(B) - ramGet(A);

	if (_debug) {
		std::cout << ramGet(B) << " - " << ramGet(A) << " = " << b << std::endl;
	}

	ramSet(b, B);
	if (b == 0 || (b && (128 << (8 * _width)) != 0)) {
		_pc = C;
	}
	else {
		_pc += 3;
	}
}

void State::ramInit(const size_t length, const uint8_t* values)
{
	for (size_t i=0; i < length; i++) {
		_ram[i] = values[i];
	}
}

const uint32_t State::ramGet(const size_t addr) const
{
	size_t loc;
	loc = addr << _width;
	switch (_width) {
		case Width::b8:
			return (uint8_t) _ram[loc];
		case Width::b16:
			return (uint16_t) _ram[loc];
		case Width::b32:
			return (uint32_t) _ram[loc];
	}
}

void State::ramSet(const uint32_t value, const size_t addr)
{
	size_t loc;
	loc = addr << _width;
	switch (_width) {
		case Width::b8:
			_ram[loc] = (uint8_t) value;
		case Width::b16:
			_ram[loc] = (uint16_t) value;
		case Width::b32:
			_ram[loc] = (uint32_t) value;
	}
}
