#ifndef CONSOLE_H
#define CONSOLE_H

#include <vector>
#include <string>

using namespace std;

class Console {
	public:
		Console();
		void write(char);
		char read();
	private:
		int bufi;
		string buffer;
};

#endif
