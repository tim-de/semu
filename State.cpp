#include<string>
#include<iostream>

#include"State.hpp"

State::State(Width::Enum width, bool debug):
	_width(width),
	_pc(0),
	_debug(debug),
	_interface(width)
{
	_interface.addMap((1 << (8 << _width)) - 1);
}

const Width::Enum State::width(void) const {
	return _width;
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

	A = _interface.fetchVal(_pc);
	B = _interface.fetchVal(_pc+1);
	C = _interface.fetchVal(_pc+2);

	if (_debug) {
		std::cout << std::showbase << std::hex << _pc << ": ";
		std::cout << std::showbase << std::hex << A << " ";
		std::cout << std::showbase << std::hex << B << " ";
		std::cout << std::showbase << std::hex << C << std::endl;
	}

	b = _interface.fetchVal(B) - _interface.fetchVal(A);

	if (_debug) {
		std::cout << std::dec << getSigned(_interface.fetchVal(B)) << " - " << getSigned(_interface.fetchVal(A)) << " = " << getSigned(b) << std::endl;
	}

	_interface.putVal(b, B);

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

// Initialises length bytes of ram to the contents of values,
// note that it operates on 8 bits at a time, regardless of the
// value set for data width. Behaviour is undefined if length
// is larger than the size of values
// Replaced by _interface.ramInit()
/*void State::ramInit(const size_t length, const uint8_t* values)
{
	for (size_t i=0; i < length; i++) {
		_ram[i] = values[i];
	}
}*/

// A getter for the internal halt flag, returns true if a halt
// condition has been reached
const bool State::isHalted() const
{
	return _halted;
}

const int32_t State::getSigned(const uint32_t value) const {
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
