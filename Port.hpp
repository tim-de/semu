#ifndef _NUZUIQM_PORT_H
#define _NUZUIQM_PORT_H

#include<string>
#include<iostream>

#include"Utils.hpp"

namespace PortType {
	enum Enum {
		IO,
		Link
	};
}

class GPort {
	public:
		GPort();
		virtual ~GPort() =0;
		virtual void write(const uint32_t value) =0;
		virtual const uint32_t read(const Element::Enum elem) const =0;
};

class Port {
	private:
		GPort* _port;
		bool _owned;
	public:
		Port();
		Port(uint32_t& value);
		Port(uint32_t& r_value, uint32_t& w_value);
		Port(GPort* port);
		~Port();
		void write(const uint32_t value);
		const uint32_t read(const Element::Enum elem) const;
};

class IoPort: public GPort {
	public:
		const uint32_t read(const Element::Enum elem) const;
		void write(const uint32_t value);
};

class LinkPort: public GPort {
	private:
		uint32_t& _rval;
		uint32_t& _wval;
	public:
		LinkPort(LinkPort& oldport);
		LinkPort(uint32_t& value);
		LinkPort(uint32_t& r_value, uint32_t& w_value);
		const uint32_t read(const Element::Enum elem) const;
		void write(const uint32_t value);
};

#endif
