#include <fstream>
#include <vector>
#include <cstring>
#include <map>

#include "instruction.h"

using namespace std;

Instruction* makeInstruction(char* str) {
	Instruction *instr = (Instruction*) malloc(sizeof(Instruction));
	char* token = strtok(str, " ");

	if (token == NULL) {
		delete instr;
		return NULL;
	}

	if (strcmp(token, "data") == 0) {
		instr->code = DATA;

		token = strtok(NULL, " ");
		instr->num = atoi(token);

		token = strtok(NULL, "\0");
		instr->data = new char[strlen(token) + 1];
		memset(instr->data, '\0', sizeof(instr->data));
		strcpy(instr->data, token);

	} else if (strcmp(token, "loadimm") == 0) {
		instr->code = LOADIMM;

		token = strtok(NULL, " ");
		instr->regA = atoi(token);

		token = strtok(NULL, " ");
		instr->num = atoi(token);

	} else if (strcmp(token, "load") == 0) {
		instr->code = LOAD;

		token = strtok(NULL, " ");
		instr->regA = atoi(token);

		token = strtok(NULL, " ");
		instr->num = atoi(token);

	} else if (strcmp(token, "store") == 0) {
		instr->code = STORE;

		token = strtok(NULL, " ");
		instr->regA = atoi(token);

		token = strtok(NULL, " ");
		instr->num = atoi(token);

	} else if (strcmp(token, "inb") == 0) {
		instr->code = INB;

		token = strtok(NULL, " ");
		instr->regA = atoi(token);

		token = strtok(NULL, " ");
		instr->port = atoi(token);

	} else if (strcmp(token, "outb") == 0) {
		instr->code = OUTB;

		token = strtok(NULL, " ");
		instr->regA = atoi(token);

		token = strtok(NULL, " ");
		instr->port = atoi(token);

	} else if (strcmp(token, "outnum") == 0) {
		instr->code = OUTNUM;

		token = strtok(NULL, " ");
		instr->regA = atoi(token);

		token = strtok(NULL, " ");
		instr->port = atoi(token);

	} else if (strcmp(token, "outstr") == 0) {
		instr->code = OUTSTR;

		token = strtok(NULL, " ");
		instr->num = atoi(token);

		token = strtok(NULL, " ");
		instr->port = atoi(token);

	} else if (strcmp(token, "add") == 0) {
		instr->code = ADD;

		token = strtok(NULL, " ");
		instr->regA = atoi(token);

		token = strtok(NULL, " ");
		instr->regB = atoi(token);

		token = strtok(NULL, " ");
		instr->regC = atoi(token);

	} else if (strcmp(token, "sub") == 0) {
		instr->code = SUB;

		token = strtok(NULL, " ");
		instr->regA = atoi(token);

		token = strtok(NULL, " ");
		instr->regB = atoi(token);

		token = strtok(NULL, " ");
		instr->regC = atoi(token);

	} else if (strcmp(token, "j") == 0) {
		instr->code = J;

		token = strtok(NULL, " ");
		instr->num = atoi(token);

	} else if (strcmp(token, "jz") == 0) {
		instr->code = JZ;

		token = strtok(NULL, " ");
		instr->regA = atoi(token);

		token = strtok(NULL, " ");
		instr->num = atoi(token);

	} else if (strcmp(token, "jnz") == 0) {
		instr->code = JNZ;

		token = strtok(NULL, " ");
		instr->regA = atoi(token);

		token = strtok(NULL, " ");
		instr->num = atoi(token);

	} else if (strcmp(token, "jreg") == 0) {
		instr->code = JREG;

		token = strtok(NULL, " ");
		instr->regA = atoi(token);

	} else if (strcmp(token, "halt") == 0) {
		instr->code = HALT;

	} else if (strcmp(token, "mov") == 0) {
		instr->code = MOV;

		token = strtok(NULL, " ");
		instr->regA = atoi(token);

		token = strtok(NULL, " ");
		instr->regB = atoi(token);

	} else if (strcmp(token, "push") == 0) {
		instr->code = PUSH;

		token = strtok(NULL, " ");
		instr->regA = atoi(token);

	} else if (strcmp(token, "pop") == 0) {
		instr->code = POP;

		token = strtok(NULL, " ");
		instr->regA = atoi(token);

	} else if (strcmp(token, "jsr") == 0) {
		instr->code = JSR;

		token = strtok(NULL, " ");
		instr->num = atoi(token);

	} else if (strcmp(token, "return") == 0) {
		instr->code = RETURN;

	} else if (strcmp(token, "rstore") == 0) {
		instr->code = RSTORE;

		token = strtok(NULL, " ");
		instr->regA = atoi(token);

		token = strtok(NULL, " ");
		instr->regB = atoi(token);

	} else if (strcmp(token, "rload") == 0) {
		instr->code = RLOAD;

		token = strtok(NULL, " ");
		instr->regA = atoi(token);

		token = strtok(NULL, " ");
		instr->regB = atoi(token);

	} else {
		delete instr;
		return NULL;
	}

	return instr;
}

vector<Instruction*> parse(string filename) {

	ifstream ifs(filename, ifstream::in);

	vector<Instruction*> ret;

	string line;
	while(getline(ifs, line)) {
		char* lcstr = new char[line.length() + 1];
		strcpy(lcstr, line.c_str());

		Instruction *instr = makeInstruction(lcstr);
		if (instr == NULL) {
			continue;
		}

		ret.push_back(instr);

		delete [] lcstr;
	}

	return ret;
}
