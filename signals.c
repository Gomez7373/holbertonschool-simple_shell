#include "main.h"

void ctrlc_handler(int signum)
{
	(void)signum;
	if (write(STDOUT_FILENO, "\n$ ", 3) == -1)
		perror("write");
}
