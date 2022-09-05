#include<string>
#include<iostream>

#include"Port.hpp"
#include"Utils.hpp"

GPort::GPort() { }
GPort::~GPort() { }

Port::Port()
{
	_port = new IoPort;
}

Port::Port(uint32_t& value)
{
	_port = new LinkPort(value);
}

Port::Port(uint32_t& r_value, uint32_t& w_value)
{
	_port = new LinkPort(r_value, r_value);
}

Port::~Port()
{
	delete _port;
}

void Port::write(const uint32_t value) {
	_port->write(value);
}
const uint32_t Port::read(const Element::Enum elem) const {
	return _port->read(elem);
}

const uint32_t IoPort::read(const Element::Enum elem) const
{
	switch (elem) {
		case Element::min:
			return 0;
			break;
		default:
			return (uint32_t) getchar();
	}
}

void IoPort::write(const uint32_t value)
{
	putchar((int8_t) value & 0xff);
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

const uint32_t LinkPort::read(const Element::Enum elem) const
{
	return _rval;
}

void LinkPort::write(const uint32_t value)
{
	_wval = value;
}
