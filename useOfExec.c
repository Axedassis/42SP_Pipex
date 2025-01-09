#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	char *args[] = {"ls", "-l", NULL}; //programn name | argument | NULL(terminator)
	if (execv("/bin/ls", args) == -1)
	{
		perror("execv failed : 10");
		exit (EXIT_FAILURE);
	}

	printf("This code will never be execut if the function execv works");
	return (0);
}