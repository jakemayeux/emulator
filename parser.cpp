#include <fstream>
#include <vector>
#include <cstring>
#include <map>

#include "instruction.h"

using namespace std;

vector<Instruction> parse(string filename) {

	ifstream ifs(filename, ifstream::in);

	string line;
	while(getline(ifs, line)) {
		//printf("%s\n", line.c_str());
		char* lcstr = new char[line.length() + 1];
		strcpy(lcstr, line.c_str());

		char* pch = strtok(lcstr, " ");
		while (pch != NULL) {
			printf("%s\n", pch);
			pch = strtok(NULL, " ");
		}

		delete [] lcstr;
		delete [] pch;
	}
}

Instruction makeInstruction(char* str) {
	Instruction instr;
	char* token = strtok(str, " ");

	if (strcmp(token, "data") == 0) {
		instr.code = DATA;

		token = strtok(NULL, " ");
		instr.num = atoi(token);

		token = strtok(NULL, "\0");
		instr.data = token;

		printf("instruction:\n");
		printf("%d\n", instr.code);
		printf("%d\n", instr.num);
		printf("%s\n", instr.data);
	} else if (strcmp(token, "loadimm") == 0) {
		instr.code = LOADIMM;
	} else if (strcmp(token, "load") == 0) {
		instr.code = LOAD;
	} else if (strcmp(token, "store") == 0) {
		instr.code = STORE;
	} else if (strcmp(token, "inb") == 0) {
		instr.code = INB;
	} else if (strcmp(token, "outb") == 0) {
		instr.code = OUTB;
	} else if (strcmp(token, "outnum") == 0) {
		instr.code = OUTNUM;
	} else if (strcmp(token, "outstr") == 0) {
		instr.code = OUTSTR;
	} else if (strcmp(token, "add") == 0) {
		instr.code = ADD;
	} else if (strcmp(token, "sub") == 0) {
		instr.code = SUB;
	} else if (strcmp(token, "j") == 0) {
		instr.code = J;
	} else if (strcmp(token, "jnz") == 0) {
		instr.code = JNZ;
	} else if (strcmp(token, "jreg") == 0) {
		instr.code = JREG;
	} else if (strcmp(token, "halt") == 0) {
		instr.code = HALT;
	}




	//while(token != NULL) {
	//	
	//}
}

//char* getToken(char* str) {
//
//}
