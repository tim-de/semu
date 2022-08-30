#include<string>
#include<iostream>

#include"State.h"

// TODO:
// Add more documentation comments to methods


State::State(Width::Enum width, bool debug):
	_width(width),
	_pc(0),
	_debug(debug)
{
	// This line allocates the correct amount of heap memory
	// to store the emulated RAM. It is calculated by converting
	// the Width::Enum type to the actual bitwidth (8 << _width)
	// and then by calculating 2^n where n is the bitwidth
	_ram = new uint8_t[1 << (8 << _width)];
	if (_ram == NULL) {
		exit(EXIT_FAILURE);
	}
}

State::~State(void)
{
	delete _ram;
}

void State::cycle(void)
{
	int32_t b;
	uint32_t A, B, C;

	// If the computer has reached a halt state then do not perform
	// any cpu cycles
	if (_halted) {
		return;
	}

	A = ramGet(_pc);
	B = ramGet(_pc+1);
	C = ramGet(_pc+2);

	if (_debug) {
		std::cout << std::showbase << std::hex << _pc << ": ";
		std::cout << std::showbase << std::hex << A << " ";
		std::cout << std::showbase << std::hex << B << " ";
		std::cout << std::showbase << std::hex << C << std::endl;
	}

	b = ramGet(B) - ramGet(A);

	if (_debug) {
		std::cout << std::dec << getSigned(ramGet(B)) << " - " << getSigned(ramGet(A)) << " = " << getSigned(b) << std::endl;
	}

	ramSet(b, B);
	if (b == 0 || (b && (128 << (8 << _width)) != 0)) {
		_pc = C;
	}
	else {
		_pc += 3;
	}

	if (getSigned(_pc) < 0) {
		_halted = true;
	}
}

// Initialises <length> bytes of ram to the contents of <values>,
// note that it operates on 8 bits at a time, regardless of the
// value set for data width
void State::ramInit(const size_t length, const uint8_t* values)
{
	for (size_t i=0; i < length; i++) {
		_ram[i] = values[i];
	}
}

// A getter for the internal halt flag, returns true if a halt
// condition has been reached
const bool State::isHalted() const
{
	return _halted;
}

const size_t State::ramGet(const size_t addr) const
{
	size_t loc;
	int s, i;
	int32_t value;
	loc = addr << _width;
	s = 1 << _width;
	value = 0;
	for (i = 0; i < s; i++) {
		value >>= 8;
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

void State::ramSet(const size_t value, const size_t addr)
{
	size_t loc;
	int s, i;
	loc = addr << _width;
	s = 1 << _width;
	for (i = 0; i < s; i++) {
		_ram[loc+i] = value >> (8 * i);
	}
}

const int32_t State::getSigned(const size_t value) const {
	int32_t signed_value;

	switch (_width) {
		case Width::b8:
			signed_value = (int8_t) value;
			break;
		case Width::b16:
			signed_value = (int16_t) value;
			break;
		case Width::b32:
			signed_value = (int32_t) value;
			break;
	}

	return signed_value;
}
