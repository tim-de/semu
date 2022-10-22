#include<string>
#include<iostream>

#include"Utils.hpp"

#include"State.hpp"

State::State(Width::Enum width, bool debug):
	_width(width),
	_interface(width),
	_pc(0),
	_debug(debug)
{
	_interval = 1 << _width;

	uint32_t io_addr;
	switch (_width) {
		case Width::b8:
			io_addr = (uint32_t) UINT8_MAX;
			break;
		case Width::b16:
			io_addr = (uint32_t) UINT16_MAX;
			break;
		case Width::b32:
			io_addr = (uint32_t) UINT32_MAX;
			break;
	}
	_interface.addMap(io_addr);
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
	/*if (_halted) {
		return;
	}*/

	A = _interface.fetchVal(_pc, Element::addr);
	B = _interface.fetchVal(_pc+_interval, Element::addr);
	C = _interface.fetchVal(_pc+(2*_interval), Element::addr);

	if (_debug) {
		std::cerr << std::showbase << std::hex << _pc << ": ";
		std::cerr << std::showbase << std::hex << A << " ";
		std::cerr << std::showbase << std::hex << B << " ";
		std::cerr << std::showbase << std::hex << C << std::endl;
	}

	min = _interface.fetchVal(B, Element::min);
	sub = _interface.fetchVal(A, Element::sub);
	dif = min - sub;

	if (_debug) {
		std::cerr << std::dec << getSigned(min) << " - " << getSigned(sub) << " = " << getSigned(dif) << std::endl;
	}

	_interface.putVal(dif, B);

	if (getSigned(dif) > 0) {
		_pc += 3 * _interval;
		_pc &= -1 - (_interval-1);
	}
	else {
		_pc = C;
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
