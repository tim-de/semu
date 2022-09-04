#ifndef _NUZUIQM_PORT_H
#define _NUZUIQM_PORT_H

#include<string>
#include<iostream>

namespace PortType {
	enum Enum {
		IO,
		Link
	};
}

class Port {
	public:
		Port();//uint32_t addr, void (*writeFunc) (uint32_t), uint32_t (*readFunc) (void));
		virtual ~Port();
		virtual void write(const uint32_t value) =0;
		virtual const uint32_t read(void) const =0;
};

class IoPort: public Port {
	public:
		const uint32_t read(void) const;
		void write(const uint32_t value);
};

class LinkPort: public Port {
	private:
		uint32_t& _rval;
		uint32_t& _wval;
	public:
		LinkPort(LinkPort& oldport);
		LinkPort(uint32_t& value);
		LinkPort(uint32_t& r_value, uint32_t& w_value);
		const uint32_t read(void) const;
		void write(const uint32_t value);
};

#endif
