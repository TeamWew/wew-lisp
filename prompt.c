#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <string.h>

static char buffer[2048];

char* readline(char* prompt) {
	fputs(prompt, stdout);
	fgets(buffer, 2048, stdin);
	char* copy = malloc(strlen(buffer)+1);
	strcpy(copy, buffer)
	copy[strlen(copy)-1] = '\0';
	return cpy;
}

char* add_history(char* _) {}
#endif

#ifdef __APPLE__
#include <editline/readline.h>
#endif

#ifdef __linux
#include <editline/readline.h>
#include <editline/history.h>
#endif


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