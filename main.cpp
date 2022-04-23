#include <iostream>
#include <vector>

#include "mem.h"
#include "cpu.h"
#include "instruction.h"
#include "parser.h"

using namespace std;

int main(int argc, char** argv) {

	if (argc < 2) {
		printf("Please specify a .jm file to run\n");
		return 0;
	}

	ROM rom(1000);
	RAM ram(1000);
	MMU mmu;

	mmu.attach(&ram, 0);
	mmu.attach(&rom, 1000);

	Console console;

	CPU cpu(&mmu);
	cpu.attach(&console, 0);
	cpu.run(parse(argv[1]));

	return 0;
}

