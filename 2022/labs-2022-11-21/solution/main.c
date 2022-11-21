#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char** argv) {
	int fildes[2];

	//int process_count = atoi(argv[1]);

	pipe(fildes);
	printf("Pipes: [1]: %d, [2]: %d\n", fildes[0], fildes[1]);

	int count = 0;
	char buf[4096];
	int pid;
	//while (process_count) {
		switch (pid = fork()) {
			case 0: //child
				int fd = open("./mp", O_RDWR || O_TRUNC);
				while (count = read(fildes[0], (void*) &buf, 4096)) {
					write(fd, (const void*) &buf, count);
				}
	//			pipe(fildes);
				close(fildes[0]);
				break;
			default:
	//			process_count = 0;
				int file = open("/etc/passwd", O_RDONLY);
				while (count = read(file, (void*) &buf, 4096)) {
					write(fildes[1], (const void*) &buf, count);
				}
				close(fildes[1]);
				close(file);
				break;
		}
	//}

	return 0;
}
