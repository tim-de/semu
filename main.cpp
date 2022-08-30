#include<iostream>
#include<string>

#include"State.h"

int main(int argc, char** argv)
{
	Width::Enum width = Width::b16;
	int16_t init[] = {-4, -4, 3, 6, -4, 3, 1, 0, 0, 0};
	State state(width, true);
	state.ramInit(sizeof(init) * (1 << width), (uint8_t*) init);

	for (int i=0; i <= 4; i++) {
		state.cycle();
	}
}
