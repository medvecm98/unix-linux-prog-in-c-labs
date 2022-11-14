#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

void list_directory(char* path, int indentation) {
	DIR* directory = opendir(path);
	if (!directory)
		return;

	struct dirent* de = readdir(directory);
	while (de) {
		int name_len = strlen(de->d_name);
		if (de->d_type == DT_REG) {
			for (int i = 0; i < indentation; i++) {
				write(1, "    ", 4);
			}
			write(1, de->d_name, name_len);
			write(1, "\n", 1);
		}
		else if (de->d_type == DT_DIR) {
			if (strcmp(de->d_name, ".") != 0 && (strcmp(de->d_name, "..") != 0))
			{
				write(1, de->d_name, name_len);
				write(1, ":\n", 2);
				list_directory(de->d_name, indentation + 1);
			}
		}
		de = readdir(directory);
	}
}

int main(int argc, char ** argv) {
	int buffer_inc = 1;
	char* cwd_buf = malloc(sizeof(char) * buffer_inc * 512);

	while (!getcwd(cwd_buf, 512)) {
		free(cwd_buf);
		cwd_buf = malloc(sizeof(char) * ++buffer_inc * 512);
	}

	list_directory(argv[1], 0);

	return 0;
}
