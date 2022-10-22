#ifndef _EBQVRNQ_STATE_H
#define _EBQVRNQ_STATE_H

#include<string>
#include<iostream>

#include"MemoryMap.hpp"
#include"Utils.hpp"

// State holds the internal state of the emulated computer,
// and has methods for performing processor cycles, as
// well as setting and getting from ram regardless of the
// bit width
class State {
	public:
		// The constructor for the State class, taking a value for
		// data width (as a valid Width::Enum) and an optional bool
		// debug flag
		State(Width::Enum width = Width::b8, bool debug = false);
		// A destructor for State, necessary because of the need
		// to assign heap space for ram
		//~State(void);
		// A getter for the _width member
		const Width::Enum width(void) const;
		// Performs a single cycle of computation
		void cycle(void);
		// copies <length> bytes of <values> into the beginning of ram
		void ramInit(const size_t length, const uint8_t* values);
		// Returns the current state of the internal _halted flag
		const bool isHalted(void) const;
	private:
		//Members:

		Width::Enum _width;
		uint8_t _interval;
		MemoryMap _interface;
		uint32_t _pc;
		bool _debug;
		bool _halted;

		//Methods:

		// Fetches a value from ram, using the width member to
		// determine the number of bytes to read
		// TODO: Write replacement methods in MemoryMap.cpp and Ram.cpp
		const uint32_t ramGet(const uint32_t addr) const;
		// Puts a value into ram, using the width member to determine
		// how to interpret the value to write, and how many bytes to
		// store
		void ramSet(const uint32_t value, const uint32_t addr);
		// Gets a value taken from memory by ramGet() and returns
		// it as a signed value for output
		const int32_t getSigned(const uint32_t memval) const;
};

#endif
