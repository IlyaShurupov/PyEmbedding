

#include "Interp.h"

#include <iostream>
#include <string>

int main() {
	
	PyInterp py_int;

	std::string cmd;

	while (std::getline(std::cin, cmd)) {
		py_int.exec(cmd);
	}
}

