#include "./pipex.h"

void error_handler(const char *msg_perror)
{
	perror (msg_perror);
	exit (EXIT_FAILURE);
}

int handle_read(char **argv, char **envp, int *fd)
{
	int filein;

	filein = open(*argv[1], O_RDONLY);
	if (filein == -1)
		error_handler("read error");
	dup2(fd[1], STDOUT_FILENO);
	dup2(filein, STDIN_FILENO);
	close(fd[0]);
	execve();
}