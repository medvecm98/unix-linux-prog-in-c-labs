#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char ** argv) {
	int grid_dim = atoi(argv[1]);
	char* file_name = argv[2];
	int fd = open(file_name, O_TRUNC | O_CREAT | O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

	char* line = malloc(sizeof(char) * grid_dim + 1);
	//strcpy(line, "..........");
	
	for (int i = 0; i < grid_dim; i++) {
		line[i] = '.';
	}

	for (int i = 0; i < grid_dim; i++) {
		write(fd, line, grid_dim + 1);
	}
	
	for (int i = 1; i <= ((grid_dim + 1) * (grid_dim + 1)); i += (grid_dim + 1)) {
		lseek(fd, i - 1, SEEK_SET);
		write(fd, "\n", 1);
	}

	//lseek(fd, 2, SEEK_SET);
	//write(fd, "x", 1);

	close(fd);

	return 0;
}
