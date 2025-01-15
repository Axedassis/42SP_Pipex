/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 22:34:04 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/01/15 16:40:21 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	handler_error(const char *msg, int cod)
{
	perror(msg);
	if (!cod)
		exit (EXIT_FAILURE);
	else
		exit (cod);
}

int	ft_print_string(const char *str)
{
	int		i;
	int		size;

	i = 0;
	size = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		size++;
		i++;
	}
	return (size);
}

int	main(int argc, char *argv[], char *envp[])
{
	int		fd[2];
	pid_t	pid;

	if (argc == 5)
	{
		if (pipe(fd) == -1)
			handler_error("\033[31mError!\n\033[0m", 0);
		pid = fork();
		if (pid == -1)
			handler_error("\033[31mError!\n\033[0m", 0);
		if (pid == 0)
			first_processing(argv, envp, fd);
		waitpid(pid, NULL, WNOHANG);
		second_processing(argv, envp, fd);
	}
	else
	{
		ft_putstr_fd("\033[31mError: Command is empty.\n\033[0m", 2);
		ft_putstr_fd("Usage: ./pipex <infile> <cmd1> <cmd2> <outfile>\n", 1);
		exit (EXIT_FAILURE);
	}
	return (0);
}
