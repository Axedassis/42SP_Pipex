#include "./pipex.h"

/*
envp[] -> enviroment pointer, hold all local variable ("metadata")
*/

int main(int argc, char *argv[], char *envp[])
{
	int		fd[2]; //create pipe to child and main process
	/*como fork cria uma copia exata do main process o child process copia o 
	pipe que contem descritores de read e write que aponto no mesmo lugar da memoria
	logo ambos podem ler e escrever no mesmo arquivo */
	pid_t	pid1;

	if (argc == 5) //<prog_name> <infile> <cmd1> <cmd2> <outfile> = 5
	{
		if (pipe(fd) == -1)
			error_handler("pipe error");
		pid1 = fork();
		if (pid1 == -1)
			error_handler("fork error");
		if (pid1 == 0)
			handle_read(argv, envp, fd);
		waitpid(pid1, NULL, 0);
		handle_write(argv, envp, fd);
	}
	else
	{
		printf("bad argument\n");
	}
	return (0);
}
