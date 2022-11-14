#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

void read_and_print(int fd, char* name) {
	if (fd == -1) {
		int errsv = errno;
		if (errsv == ENOENT) {
			printf("No such file or directory: %s\n", name);
		}
		return;
	}
	char* buf = malloc(sizeof(char) * 4096);
	ssize_t bytes_read = read(fd, buf, 4096);
	while (bytes_read != 0) {
		write(1, buf, bytes_read);
		bytes_read = read(fd, buf, 4096);
	}
	free(buf);
	close(fd);
}

int main(int argc, char ** argv) {
	if ((argc < 2) || (argv[1] == "-")) {
		while(1) {
			read_and_print(1, "");
		}
		return 0;
	}
	for (int i = 1; i < argc; i++) {
		int fd = open(argv[i], O_RDONLY);
		read_and_print(fd, argv[i]);	
	}
	return 0;
}
