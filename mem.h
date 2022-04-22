#ifndef MEM_H
#define MEM_H

#include<map>

using namespace std;

class IMemory {
	public:
		virtual char read(int) = 0;
		virtual void write(int, char) = 0;
		virtual void initialize(int, char*) = 0;
};

class RAM: public IMemory {
	public:
		RAM(int);
		char read(int);
		virtual void write(int, char);
		void initialize(int, char*);
	private:
		int size;
		char* data;
};

class ROM: public RAM {
	public:
		using RAM::RAM;
		//ROM(int);
		void write(int, char);
		//char read(int);
	private:
		int size;
		char* data;
};

class MMU: public IMemory {
	public:
		void attach(IMemory*, int);
		char read(int);
		void write(int, char);
		void initialize(int, char*);
	private:
		map<int, IMemory*> modules;
		tuple<int, IMemory*> findModule(int);
};

#endif
