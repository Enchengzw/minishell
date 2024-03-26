#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd;

	fd = dup2(STDIN_FILENO, 5);
	printf("%d\n", fd);
	if (!fd)
		printf("A");

    return 0;
}