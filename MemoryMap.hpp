#ifndef _EFWIUPQ_MEMORYMAP_H
#define _EFWIUPQ_MEMORYMAP_H

#include<string>
#include<iostream>
#include<unordered_map>

#include"Ram.hpp"
#include"Utils.hpp"
#include"Peripheral.hpp"
#include"Port.hpp"

//TODO:
// SORT ALL THIS MESS OUT!

class MemoryMap {
	private:
		Width::Enum _width;
		Ram _ram;
		std::unordered_map <uint32_t, Port> _mappings;
	public:
		MemoryMap(Width::Enum width);
		//~MemoryMap(void);

		void addMap(uint32_t addr);
		void addMap(uint32_t addr, GPort* port);
		void addMap(uint32_t addr, uint32_t& value);
		void addMap(uint32_t addr, uint32_t& r_value, uint32_t& w_value);

		void addPeripheral(Peripheral& device);

		const uint32_t fetchVal(const uint32_t addr, const Element::Enum elem) const;
		void putVal(const uint32_t value, const uint32_t addr);

		void ramInit(const size_t length, const uint8_t* values);
};

#endif
