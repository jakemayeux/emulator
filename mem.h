#ifndef MEM_H
#define MEM_H

#include<map>

using namespace std;

class IMemory {
	public:
		virtual unsigned char read(int) = 0;
		virtual void write(int, unsigned char) = 0;
		virtual void initialize(int, unsigned char*) = 0;
};

class RAM: public IMemory {
	public:
		RAM(int);
		unsigned char read(int);
		virtual void write(int, unsigned char);
		void initialize(int, unsigned char*);
	private:
		int size;
		unsigned char* data;
};

class ROM: public RAM {
	public:
		using RAM::RAM;
		//ROM(int);
		void write(int, unsigned char);
		//unsigned char read(int);
	private:
		int size;
		unsigned char* data;
};

class MMU: public IMemory {
	public:
		void attach(IMemory*, int);
		unsigned char read(int);
		void write(int, unsigned char);
		void initialize(int, unsigned char*);
	private:
		map<int, IMemory*> modules;
		tuple<int, IMemory*> findModule(int);
};

#endif
