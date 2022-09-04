#include<string>
#include<iostream>

#include"Port.hpp"

const uint32_t IoPort::read(void) const
{
	return (uint32_t) getchar();
}

void IoPort::write(const uint32_t value)
{
	putchar((int) value & 0xff);
}

LinkPort::LinkPort(LinkPort& oldport):
	_rval(oldport._rval),
	_wval(oldport._wval)
{ }

LinkPort::LinkPort(uint32_t& value):
	_rval(value),
	_wval(value)
{ }

LinkPort::LinkPort(uint32_t& r_value, uint32_t& w_value):
	_rval(r_value),
	_wval(w_value)
{ }

const uint32_t LinkPort::read(void) const
{
	return _rval;
}

void LinkPort::write(const uint32_t value)
{
	_wval = value;
}
