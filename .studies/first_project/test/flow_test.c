#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(void)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
	{
		perror ("pipe error");
		exit (EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		perror ("fork errror");
		exit (EXIT_FAILURE);
	}
	if(pid == 0)
	{
		char *str = "hello world\0";
		close(fd[0]);
		write(fd[1], str, strlen(str) + 1); // include null terminator
		close(fd[1]);
		return (0);
	}
	close(fd[1]);
	char str[1000];
	read(fd[0], str, 1000);
	str[999] = '\0'; // ensure null termination
	printf("result: %s\n", str);
	close(fd[0]);
	return (0);
}