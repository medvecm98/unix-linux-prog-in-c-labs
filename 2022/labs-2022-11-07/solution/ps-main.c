#include <unistd.h>
int main() {
	fork();
	fork();
	fork();
	fork();
	fork();
	sleep(42);
	return 0;
}
