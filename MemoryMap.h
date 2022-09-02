#ifndef _EFWIUPQ_MEMORYMAP_H
#define _EFWIUPQ_MEMORYMAP_H

#include<string>
#include<iostream>
#include<unordered_map>

#include"Ram.h"

//TODO:
// SORT ALL THIS MESS OUT!

class MemoryMap {
	public:
		MemoryMap(Width::Enum width);

		void addMap(uint32_t addr, void (*writeFunc) (uint32_t), uint32_t (*readFunc) (void));

		const uint32_t fetchVal(const uint32_t addr) const;
		void putVal(const uint32_t value, const uint32_t addr);

		void ramInit(const size_t length, const uint8_t* values);
	private:
		class Port;
		Width::Enum _width;
		Ram _ram;
		std::unordered_map <uint32_t, Port> _mappings;
};

class MemoryMap::Port {
	public:
		Port(uint32_t addr, void (*writeFunc) (uint32_t), uint32_t (*readFunc) (void));
		virtual ~Port();
		const uint32_t addr(void) const;
		virtual void write(const uint32_t);
		virtual const uint32_t read(void) const;
	private:
		uint32_t _addr;
		void (*_writeFunc) (uint32_t);
		uint32_t (*_readFunc) (void);
};


#endif
