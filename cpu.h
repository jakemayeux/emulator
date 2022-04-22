#ifndef CPU_H
#define CPU_H

#include <tuple>
#include <vector>

#include "mem.h"
#include "console.h"
#include "instruction.h"

using namespace std;

class CPU {
	public:
		CPU(IMemory*);
		void attach(Console *console, int);
		void run(vector<Instruction>);
		void eval(Instruction, int*);
	private:
		int registers[8];
		IMemory *mem;
		Console io[4];
};

#endif
