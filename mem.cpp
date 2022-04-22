#include <iostream>
#include <cstring>
#include <map>

#include "mem.h"

using namespace std;

//
// RAM
//
RAM::RAM(int s) {
	this->size = s;
	this->data = (char*) malloc(sizeof(char) * size);
}

char RAM::read(int address) {
	return this->data[address];
}

void RAM::write(int address, char c) {
	this->data[address] = c;
}

void RAM::initialize(int address, char* string) {
	memcpy(data + address, string, strlen((char*)string));
}


//
// ROM
//
void ROM::write(int address, char data) {
	return;
}


//
// MMU
//
void MMU::attach(IMemory *mem, int address) {
	printf("attach to %d\n", address);
	modules[address] = mem;
}

char MMU::read(int address) {
	auto result = findModule(address);

	int localAddress = get<0>(result);
	IMemory *module = get<1>(result);

	return module->read(localAddress);
}

void MMU::write(int address, char c) {
	auto result = findModule(address);

	int localAddress = get<0>(result);
	IMemory *module = get<1>(result);

	return module->write(localAddress, c);
}

void MMU::initialize(int address, char* string) {
	auto result = findModule(address);

	int localAddress = get<0>(result);
	IMemory *module = get<1>(result);

	return module->initialize(localAddress, string);
}

tuple<int, IMemory*> MMU::findModule(int address) {
	int i = 0;
	for (auto it = modules.rbegin(); it != modules.rend(); it++) {
		if (address >= it->first) {
			return make_tuple(address - it->first, it->second);
		}
	}

	return make_tuple(0, nullptr);
}
