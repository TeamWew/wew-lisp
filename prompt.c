#include <stdio.h>
#include <stdlib.h>

#include <editline/readline.h>

int main(int argc, char** argv) {
	puts("wewlisp version 0.0.1");
	puts("Press Ctrl+c to exit");

	while(1) {
		char* input = readline("wewlisp> ");

		add_history(input);

		printf("No you're a %s\n", input);

		free(input);
	}

	return 0;
}