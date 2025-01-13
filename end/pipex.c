#include "./pipex.h"

int main(int argc, char *argv[], char *envp[])
{
	int		fd[2];
	pid_t	pid1;

	if (argc == 5)
	{
		if (pipe(fd) == -1)
			error_handler("pipe error");
		pid1 = fork();
		if (pid1 == -1)
			error_handler("fork error");
		if (pid1 == 0)
			handle_read(argv, envp, fd);
	}
	else
	{

	}
	return (0);
}
