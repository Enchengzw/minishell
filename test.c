#include <stdio.h>
#include <unistd.h>

int main() {
	int pipefd[2];
	int fd1, fd2, fd3;

	// Create the pipe
	if (pipe(pipefd) == -1) {
		perror("pipe");
		return 1;
	}

	fd3 = dup(STDOUT_FILENO);
	// Open the first file descriptor for writing
	fd1 = dup2(pipefd[1], STDOUT_FILENO);
	if (fd1 == -1) {
		perror("dup2");
		return 1;
	}

	// Open the second file descriptor for reading
	fd2 = dup2(pipefd[0], STDIN_FILENO);
	if (fd2 == -1) {
		perror("dup2");
		return 1;
	}

	// Now you can use fd1 for writing and fd2 for reading

	// Close the pipe file descriptors
	close(pipefd[0]);
	close(pipefd[1]);

	char buf[15];
	write(fd1, "Hello, world!\n", 14);
	read(fd2, buf, 14);
	write(fd3, buf, 14);
	return 0;
}