#include<string>
#include<iostream>

#include"Ram.hpp"
#include"Utils.hpp"

Ram::Ram(Width::Enum width):
	_width(width)
{
	// This line allocates the correct amount of heap memory
	// to store the emulated RAM. It is calculated by converting
	// the Width::Enum type to the actual bitwidth (8 << _width)                                  
	// and then by calculating 2^n where n is the bitwidth

	switch (_width) {
		case Width::b8:
			_ramsize = (size_t) 1 << 8;
			break;
		case Width::b16:
			_ramsize = (size_t) 1 << 16;
			break;
		case Width::b32:
			_ramsize = (size_t) 1 << 24;
			break;
	}
	_ram = new uint8_t[_ramsize];
	if (_ram == NULL) {
		std::cerr << "ERROR: Failed to initialise ram" << std::endl;
		exit(EXIT_FAILURE);
	}
	//std::cerr << "Allocated " << _ramsize << " bytes of ram" << std::endl;
}

Ram::~Ram()
{
	delete _ram;
}

const int Ram::getByteCount(const uint32_t addr) const
{
	int a_end;

	switch (_width) {
		case Width::b8:
			return 1;
			break;
		case Width::b16:
			a_end = addr & 1;
			break;
		case Width::b32:
			a_end = addr & 3;
			break;
	}

	return (1 << _width) - a_end;
}

const uint32_t Ram::get(const uint32_t addr) const
{
	uint32_t value;
	// Return zero if address out of range
	if (addr >= _ramsize) {
		return 0;
	}
	value = 0;

	switch (this->getByteCount(addr)) {
		case 4:
			value += (uint32_t) _ram[addr+3] << 24;
		case 3:
			value += (uint32_t) _ram[addr+2] << 16;
		case 2:
			value += (uint32_t) _ram[addr+1] << 8;
		default:
			value += _ram[addr];
			break;
	}

	return value;
}

void Ram::set(const uint32_t value, const uint32_t addr)
{
	// Do not attempt a write if address out of range
	if (addr >= _ramsize) {
		return;
	}

	int i;
	for (i = 0; i < this->getByteCount(addr); i++) {
		_ram[addr+i] = value >> (8 * i);
	}
}

void Ram::init(const uint32_t length, const uint8_t* values)
{
	for (size_t i=0; (i < length && i < _ramsize); i++) {
		_ram[i] = values[i];
	}
}
