#include <tuple>
#include <thread>
#include <chrono>

#include "cpu.h"
#include "instruction.h"

using namespace std;

CPU::CPU(IMemory *mem) {
	this->mem = mem;
}

void CPU::attach(Console *console, int port) {
	io[port] = *console;
}

void CPU::run(vector<Instruction*> instructions) {
	registers[7] = 0; // stack starts at 0

	for(int iptr = 0; iptr < instructions.size(); ) {
		//this_thread::sleep_for(chrono::milliseconds(100));
		if (instructions[iptr]->code == HALT) {
			break;
		}

		this->eval(instructions[iptr], &iptr);
	}
}

void outstr(IMemory *mem, Console *console, int address) {
	int i = address;
	while(true) {
		char c = mem->read(i++);
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
	//console->write('\n');
	//printf("start sleep...\n");
	//this_thread::sleep_for(chrono::milliseconds(10));
	//printf("awake!\n");
}

void CPU::eval(Instruction *instr, int *iptr) {
	switch (instr->code) {
		case DATA:
			mem->initialize(instr->num, instr->data);
			break;
		case LOADIMM:
			registers[instr->regA] = instr->num;
			break;
		case LOAD:
			registers[instr->regA] = mem->read(instr->num);
			break;
		case STORE:
			mem->write(instr->num, (char)registers[instr->regA]);
			break;
		case INB:
			registers[instr->regA] = io[instr->port].read();
			break;
		case OUTB:
			io[instr->port].write(registers[instr->regA]);
			break;
		case OUTNUM:
			outnum(registers[instr->regA], &io[instr->port]);
			//printf("OUTNUMMING");
			//this_thread::sleep_for(chrono::seconds(1));
			break;
		case OUTSTR:
			outstr(mem, &io[instr->port], instr->num);
			break;
		case ADD:
			registers[instr->regA] = registers[instr->regB] + registers[instr->regC];
			break;
		case SUB:
			registers[instr->regA] = registers[instr->regB] - registers[instr->regC];
			break;
		case J:
			*iptr += instr->num;
			return;
		case JZ:
			if (registers[instr->regA] == 0) {
				*iptr += instr->num;
				return;
			}
			break;
		case JNZ:
			if (registers[instr->regA] != 0) {
				*iptr += instr->num;
				return;
			}
			break;
		case JREG:
			*iptr += registers[instr->regA];
			break;
		case HALT:
			break;
		case MOV:
			registers[instr->regA] = registers[instr->regB];
			break;
		case PUSH:
			mem->write(registers[7], (char)registers[instr->regA]);
			registers[7]++;
			break;
		case POP:
			registers[7]--;
			if (registers[7] < 0) registers[7] = 0;
			registers[instr->regA] = mem->read(registers[7]);
			break;
		case JSR:
			mem->write(registers[7], (char)*iptr);
			registers[7]++;
			*iptr += instr->num;
			return;
		case RETURN:
			registers[7]--;
			if (registers[7] < 0) registers[7] = 0;
			*iptr = mem->read(registers[7]);
			*iptr += 1;
			return;
		case RSTORE:
			mem->write(registers[instr->regB], (char)registers[instr->regA]);
			break;
		case RLOAD:
			registers[instr->regA] = mem->read(registers[instr->regB]);
			break;
	}

	*iptr += 1;
	return;
}
