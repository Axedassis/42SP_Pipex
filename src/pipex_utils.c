/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 10:14:47 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/01/15 16:40:19 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	apply_function(char *cmd, char **envp)
{
	char	**cmd_splited;
	int		i;
	char	*path;

	i = -1;
	cmd_splited = ft_split(cmd, ' ');
	if (!cmd | !cmd[0])
	{
		ft_putstr_fd("\033[31mError: Command is empty.\n\033[0m", 2);
		handler_error("Empty command\n", 127);
	}
	path = path_searcher(cmd_splited[0], envp);
	if (!path)
	{
		ft_putstr_fd("\033[31mError: Command not found. \n\033[0m", 2);
		while (cmd_splited[++i])
			free(cmd_splited[i]);
		free(cmd_splited);
		handler_error("Command not found\n", 127);
	}
	if (execve(path, cmd_splited, envp) == -1)
		handler_error("\033[31mUnable to run the command\n\033[0m", 126);
}

void	first_processing(char **argv, char **envp, int *fd)
{
	int		fd_opened_file;

	fd_opened_file = open(argv[1], O_RDONLY);
	if (fd_opened_file == -1)
		handler_error ("\033[31mUnable to open the file\n\033[0m", 0);
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	dup2(fd_opened_file, STDIN_FILENO);
	close(fd[1]);
	close(fd_opened_file);
	apply_function(argv[2], envp);
}

void	second_processing(char **argv, char **envp, int *fd)
{
	int		fd_read_file;

	fd_read_file = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_read_file == -1)
		handler_error ("\033[31mUnable to Create Output file\n\033[0m", 0);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	dup2(fd_read_file, STDOUT_FILENO);
	close(fd[0]);
	close(fd_read_file);
	apply_function(argv[3], envp);
}
