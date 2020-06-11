#include "hello.h"

int main(int argc, char* argv[]) {

	char* name = "hello.txt";
	const char* content = "Hello World!";
	
	writeToFileILA(name, content);

	return 0;
}
