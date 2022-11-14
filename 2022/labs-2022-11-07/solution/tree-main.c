#include <unistd.h>
#include <stdio.h>

#define PRINT_PIDS(NAME) printf("%s: My PID: %u, parent PID: %u, group ID: %u\n", NAME, getpid(), getppid(), getpgrp());

int main() {
	int pid;
	switch(pid = fork()) {
		case -1:
			printf("Error\n");
			break;
		case 0:
			PRINT_PIDS("C1");
			switch(pid = fork()) {
				case -1:
					printf("Error\n");
					break;
				case 0:
					PRINT_PIDS("C2");
					pid = fork();
					if (pid == 0) {
						char buf[16];
						snprintf(buf, 16, "%u", getpid());
						execl("/usr/bin/pstree", "pstree", "-p", "-s", "-t", buf, NULL);
					}
					break;
				default:
					PRINT_PIDS("P2");
					break;
			}
			break;
		default:
			PRINT_PIDS("P1");
			break;
	}
	sleep(1);
	return 0;
}
