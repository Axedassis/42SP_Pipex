#include "./pipex.h"

void error_handler(const char *msg_perror)
{
	perror (msg_perror);
	exit (EXIT_FAILURE);
}

void handle_read(char **argv, char **envp, int *fd)
{
	int filein;

	filein = open(argv[1], O_RDONLY); //open the <infile>
	if (filein == -1)
		error_handler("read error");
	dup2(fd[1], STDOUT_FILENO);
	dup2(filein, STDIN_FILENO);
	close(fd[0]);
	close(filein);
	execute(argv[2], envp); //passing <cmd1>

}

void handle_write(char **argv, char **envp, int *fd)
{
	int		fileout;

	fileout = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fileout == -1)
		error_handler("create or truncate file error");
	dup2(fd[0], STDIN_FILENO);
	dup2(fileout, STDOUT_FILENO);
	close(fd[1]);
	execute(argv[3], envp);
}

char *find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK | X_OK) == 0) //verify if the binary exists and is executable
			return (path);
		free(path);
		i++;
	}
	i = -1;
	while (paths[++i]) //free all the split
		free(paths[i]);
	free(paths);
	return ((void *)0);
}

void execute(char *cmd1, char **envp)
{
	char	**cmd;
	int		i;
	char	*path;

	i = -1;
	cmd = ft_split(cmd1, ' '); // "ls -l -a" -> "ls" "-l" "-a"
	path = find_path(cmd[0], envp);
	if (!path)
	{
		while (cmd[++i])
			free(cmd[i]);
		free(cmd);
		error_handler("Invalid or non-existent binary");
	}
	if (execve(path, cmd, envp) == -1)
		error_handler("execve error");
}