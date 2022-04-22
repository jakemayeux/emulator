#include <iostream>
#include <vector>

#include "mem.h"
#include "cpu.h"
#include "instruction.h"
#include "parser.h"

using namespace std;

// copied from https://stackoverflow.com/questions/51854537/convert-stdstring-to-unsigned-char-array
unsigned char (& to_array(std::string const& str))[] {
	static thread_local std::vector<unsigned char> result;
	result.assign(str.data(), str.data() + str.length() + 1);
	return reinterpret_cast<unsigned char (&)[]>(*result.data());
}

int main() {
	ROM rom(1000);
	RAM ram(1000);
	MMU mmu;

	mmu.attach(&rom, 0);
	mmu.attach(&ram, 1000);

	mmu.initialize(10, to_array("hello world\n"));

	Console console;

	CPU cpu(&mmu);
	cpu.attach(&console, 0);

	Instruction outstr;
	outstr.code = OUTSTR;
	outstr.num = 10;
	outstr.port = 0;

	int i = 0;
	cpu.eval(outstr, &i);

	parse("asm");

	//Console console;
	//console.write('a');
	//console.write('a');
	//console.write('a');
	//console.write('a');

	//printf("%c\n", console.read());
	//printf("%c\n", console.read());
	//printf("%c\n", console.read());
	//printf("%c\n", console.read());

	//vector<Instruction> instructions;

	//Instruction a;
	//a.code = HALT;
	//Instruction b;
	//b.code = J;
	//Instruction c;
	//c.code = JNZ;

	//instructions.push_back(a);
	//instructions.push_back(b);
	//instructions.push_back(c);

	//CPU cpu;
	//cpu.run(instructions);

	//ROM rom1(1000);
	//RAM ram1(1000);
	//MMU mmu1;

	//mmu1.attach(&rom1, 0);
	//mmu1.attach(&ram1, 1000);

	//mmu1.initialize(10, to_array("hello world"));
	//mmu1.initialize(1010, to_array("asdfasdf"));

	//printf("initialized\n");
	//
	//printf("%c\n", mmu1.read(10));
	//printf("%c\n", mmu1.read(11));
	//printf("%c\n", mmu1.read(12));
	//printf("%c\n", mmu1.read(13));
	//printf("%c\n", mmu1.read(14));
	//printf("%c\n", mmu1.read(15));
	//printf("%c\n", mmu1.read(16));
	//printf("%c\n", mmu1.read(17));
	//printf("%c\n", mmu1.read(18));
	//printf("%c\n", mmu1.read(19));

	//mmu1.write(10, 'x');
	//printf("%c\n", mmu1.read(10));

	//printf("next\n");

	//printf("%c\n", mmu1.read(1010));
	//mmu1.write(1010, 'x');
	//printf("%c\n", mmu1.read(1010));
}

