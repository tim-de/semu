#include<string>
#include<iostream>
#include<unordered_map>

#include"MemoryMap.hpp"
#include"Port.hpp"

MemoryMap::MemoryMap(Width::Enum width):
	_width(width),
	_ram(width)
{}

MemoryMap::~MemoryMap(void)
{
	auto iter = _mappings.begin();
	while (iter != _mappings.end()) {
		delete iter->second;
		iter++;
	}
}

void MemoryMap::addMap(uint32_t addr)//void (*writeFunc) (uint32_t), uint32_t (*readFunc) (void))
{
	_mappings[addr] = new IoPort;
}

void MemoryMap::addMap(uint32_t addr, uint32_t& value)
{
	_mappings[addr] = new LinkPort(value);
}

void MemoryMap::addMap(uint32_t addr, uint32_t& r_value, uint32_t& w_value)
{
	_mappings[addr] = new LinkPort(r_value, w_value);
}

void MemoryMap::ramInit(const size_t length, const uint8_t* values)
{
	_ram.init(length, values);
}

const uint32_t MemoryMap::fetchVal(const uint32_t addr) const
{
	auto location = _mappings.find(addr);
	if (location != _mappings.end()) {
		return location->second->read();
	}
	else {
		return _ram.get(addr);
	}
}

void MemoryMap::putVal(const uint32_t value, const uint32_t addr)
{
	auto location = _mappings.find(addr);
	if (location != _mappings.end()) {
		location->second->write(value);
	}
	else {
		_ram.set(value, addr);
	}
}
