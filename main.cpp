#include<iostream>
#include<string>

#include"State.h"

int main(int argc, char** argv)
{
	uint16_t init[] = {4, 3, 0, 0, 1};
	State state(Width::b16, true);
	state.ramInit(2 * 5, (uint8_t*) init);

	for (int i=0; i <= 32; i++) {
		state.cycle();
	}
}
