#include<string>
#include<iostream>
#include<unordered_map>

#include"MemoryMap.h"

MemoryMap::MemoryMap(Width::Enum width):
	_width(width),
	_ram(width)
{}

void MemoryMap::addMap(uint32_t addr, void (*writeFunc) (uint32_t), uint32_t (*readFunc) (void))
{
	Mapping map(addr, writeFunc, readFunc);
	_mappings[addr] = map;
}

void MemoryMap::ramInit(const size_t length, const uint8_t* values)
{
	_ram.init(length, values);
}

MemoryMap::Mapping::Mapping(uint32_t addr, void (*writeFunc) (uint32_t), uint32_t (*readFunc) (void)):
	_addr(addr),
	_writeFunc(writeFunc),
	_readFunc(readFunc)
{}

const uint32_t MemoryMap::Mapping::addr(void) const
{
	return _addr;
}

void MemoryMap::Mapping::write(const uint32_t value)
{
	_writeFunc(value);
}

const uint32_t MemoryMap::Mapping::read(void) const
{
	return _readFunc();
}
