#include<string>
#include<iostream>

#include"Utils.hpp"

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
	uint32_t min, sub, dif;
	uint32_t A, B, C;

	// If the computer has reached a halt state then do not perform
	// any cpu cycles
	if (_halted) {
		return;
	}

	A = _interface.fetchVal(_pc, Element::addr);
	B = _interface.fetchVal(_pc+1, Element::addr);
	C = _interface.fetchVal(_pc+2, Element::addr);

	if (_debug) {
		std::cout << std::showbase << std::hex << _pc << ": ";
		std::cout << std::showbase << std::hex << A << " ";
		std::cout << std::showbase << std::hex << B << " ";
		std::cout << std::showbase << std::hex << C << std::endl;
	}

	min = _interface.fetchVal(B, Element::min);
	sub = _interface.fetchVal(A, Element::sub);
	dif = min - sub;

	if (_debug) {
		std::cout << std::dec << getSigned(min) << " - " << getSigned(sub) << " = " << getSigned(dif) << std::endl;
	}

	_interface.putVal(dif, B);

	if (dif == 0 || (dif && (128 << (8 << _width)) != 0)) {
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
void State::ramInit(const size_t length, const uint8_t* values)
{
	_interface.ramInit(length, values);
}

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
