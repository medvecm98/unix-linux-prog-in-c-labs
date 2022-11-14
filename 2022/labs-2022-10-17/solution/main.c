#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <err.h>
#include <string.h>

#define DEBUG 0

extern char ** environ;

extern char * optarg;

extern int optind, opterr, optopt;

extern int errno;

void handle_clear_env(void) {
	clearenv();
}

void handle_set_env(int argc, char ** argv) {
	int i = optind;
	while (i < argc - 1) {
#if DEBUG
		printf("argv[%d] : %s\n", i, argv[i]);
#endif
		char * var = malloc(sizeof(char) * strlen(argv[i]));
		strcpy(var, argv[i]);
#if DEBUG
		printf("var : %s\n", var);
#endif
		int equal_position = 0;
		for (; var[equal_position] != '='; equal_position++) {}
		char * key = malloc(sizeof(char) * equal_position);
		char * value = malloc(sizeof(char) * strlen(var) - equal_position);

		strncpy(key, var, equal_position);
		strcpy(value, var + equal_position + 1);

#if DEBUG
		printf("Key : %s\n", key);
		printf("Value : %s\n", value);
#endif

		setenv(key, value, 1);

		i++;
	}
	
	for (int j = 0; j < strlen(argv[i]); j++) {
		if (argv[i][j] == '=') {
			system("env");
			exit(1);
		}
	}
}

int main(int argc, char ** argv) {
	char* op = ":i:";
	char opc;
	int clear_and_set = 0;
	while ((opc = getopt(argc, argv, "i")) != -1) {
		switch(opc) {
			case 'i':
				clear_and_set = 1;
				break;
			default:
				break;
		}
	}

	if (clear_and_set) {
		handle_clear_env();
		handle_set_env(argc, argv);
	}

	if (system(argc[argv - 1]) == -1) {
		err(errno, NULL);
	}
	
	return 0;
}
