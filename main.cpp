#include <iostream>
#include <string>
#include <tclap/CmdLine.h>

#include"State.hpp"

int main(int argc, char** argv)
{
	bool debug;
	int cmdwidth;
	Width::Enum width;
	
	try {
		TCLAP::CmdLine cmd("Emulator for subleq computer architectures.", ' ', "0.1");

		TCLAP::SwitchArg debugswitch("d", "debug", "Output debug information", cmd, false);

		TCLAP::ValueArg<int> widtharg("w", "width", "Set bus width, can be 8, 16, or 32", false, 8, "8|16|32", cmd);

		cmd.parse(argc, argv);

		debug = debugswitch.getValue();
		cmdwidth = widtharg.getValue();

	} catch (TCLAP::ArgException &e)
	{
		std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl;
	}

	if (cmdwidth <= 8) {
		width = Width::b8;
	}
	else if (cmdwidth <= 16) {
		width = Width::b16;
	}
	else {
		width = Width::b32;
	}

	uint8_t* init;
	uint32_t init_len;
	
	// Bootloaders for different bit widths
	uint8_t init8[] = {
		// Entry point 37
		0x00,0x00,0x03,
		0xff,0x00,0x06,
		0x00,0x01,0x09,
		0x00,0x00,0x0c,
		0xff,0x00,0x0f,
		0x25,0x25,0x12,
		0x00,0x25,0x15,
		0x03,0x0f,0x18,
		0x03,0x10,0x1b,
		0x03,0x13,0x1e,
		0x24,0x01,0x25,
		0x00,0x00,0x0c,
		0x01,0x00,
	};
	uint16_t init16[] = {
		// Entry point 80
		0x0000,0x0000,0x0006,
		0xffff,0x0000,0x000c,
		0xffff,0x0001,0x0012,
		0x0000,0x0002,0x0018,
		0x0000,0x0000,0x001e,
		0xffff,0x0000,0x0024,
		0x0050,0x0050,0x002a,
		0x0000,0x0050,0x0030,
		0x0006,0x0024,0x0036,
		0x0006,0x0026,0x003c,
		0x0006,0x002c,0x0042,
		0x004e,0x0002,0x0050,
		0x0000,0x0000,0x001e,
		0x0001,0x0000,
	};
	uint32_t init32[] = {
		// Entry point 184
		0x00000000,0x00000000,0x0000000c,
		0xffffffff,0x00000000,0x00000018,
		0xffffffff,0x00000001,0x00000024,
		0xffffffff,0x00000002,0x00000030,
		0xffffffff,0x00000003,0x0000003c,
		0x00000000,0x00000004,0x00000048,
		0x00000000,0x00000000,0x00000054,
		0xffffffff,0x00000000,0x00000060,
		0x000000b8,0x000000b8,0x0000006c,
		0x00000000,0x000000b8,0x00000078,
		0x0000000c,0x00000060,0x00000084,
		0x0000000c,0x00000064,0x00000090,
		0x0000000c,0x00000070,0x0000009c,
		0x000000b4,0x00000004,0x000000b8,
		0x00000000,0x00000000,0x00000054,
		0x00000001,0x00000000,
	};
	
	switch (width) {
		case Width::b8:
			init_len = sizeof(init8);
			init = (uint8_t*) init8;
			break;
		case Width::b16:
			init_len = sizeof(init16);
			init = (uint8_t*) init16;
			break;
		case Width::b32:
			init_len = sizeof(init32);
			init = (uint8_t*) init32;
			break;
	}

	State state(width, debug);
	state.ramInit(init_len * (1 << width), init);

	while (! state.isHalted()) {
		state.cycle();
	}
}
