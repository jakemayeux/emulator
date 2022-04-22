#ifndef INSTRUCTION_H
#define INSTRUCTION_H

enum OpCode {
	DATA,
	LOADIMM,
	LOAD,
	STORE,
	INB,
	OUTB,
	OUTNUM,
	OUTSTR,
	ADD,
	SUB,
	J,
	JZ,
	JNZ,
	JREG,
	HALT
};

class Instruction {
	public:
		OpCode code;
		int regA;
		int regB;
		int regC;
		char* data;
		int num; // address, offset, immediate
		int port;
};

#endif
