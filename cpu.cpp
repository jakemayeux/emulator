#include <tuple>

#include "cpu.h"
#include "instruction.h"

using namespace std;

CPU::CPU(IMemory *mem) {
	this->mem = mem;
}

void CPU::attach(Console *console, int port) {
	io[port] = *console;
}

void CPU::run(vector<Instruction> instructions) {

	for(int iptr = 0; iptr < instructions.size(); ) {
		if (instructions[iptr].code == HALT) {
			break;
		}

		this->eval(instructions[iptr], &iptr);
	}
}

void outstr(IMemory *mem, Console *console, int address) {
	int i = address;
	while(true) {
		unsigned char c = mem->read(i++);
		if (c == 0) {
			break;
		}
		console->write(c);
	}
}

void outnum(int regA, Console *console) {
	string str = to_string(regA);
	for (auto &c : str) {
		console->write(c);
	}
}

void CPU::eval(Instruction instr, int *iptr) {
	switch (instr.code) {
		case DATA:
			mem->initialize(instr.num, instr.data);
			break;
		case LOADIMM:
			registers[instr.regA] = instr.num;
			break;
		case LOAD:
			registers[instr.regA] = mem->read(instr.num);
			break;
		case STORE:
			mem->write(instr.num, (unsigned char)registers[instr.regA]);
			break;
		case INB:
			registers[instr.regA] = io[instr.port].read();
			break;
		case OUTB:
			io[instr.port].write(registers[instr.regA]);
			break;
		case OUTNUM:
			outnum(registers[instr.regA], &io[instr.port]);
			break;
		case OUTSTR:
			outstr(mem, &io[instr.port], instr.num);
			break;
		case ADD:
			registers[instr.regC] = registers[instr.regA] + registers[instr.regB];
			break;
		case SUB:
			registers[instr.regC] = registers[instr.regA] - registers[instr.regB];
			break;
		case J:
			iptr += instr.num;
			return;
		case JZ:
			if (registers[instr.regA] == 0) {
				iptr += instr.num;
				return;
			}
			break;
		case JNZ:
			if (registers[instr.regA] != 0) {
				iptr += instr.num;
				return;
			}
			break;
		case JREG:
			iptr += registers[instr.regA];
			break;
		case HALT:
			break;
	}

	*iptr += 1;
	return;
}
