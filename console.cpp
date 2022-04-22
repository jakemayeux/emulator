#include <iostream>

#include "console.h"

Console::Console() {
	bufi = 0;
}

void Console::write(char c) {
	printf("%c", c);
}

char Console::read() {
	while (true) {
		if (bufi >= buffer.size()) {
			bufi = 0;
			cin >> buffer;
		} else {
			return buffer[bufi++];
		}
	}
}
