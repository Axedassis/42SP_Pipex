/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 00:19:06 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/01/13 16:51:04 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "./libft/includes/libft.h"

void	error_handler(const char *msg_perror);
void	handle_read(char **argv, char **envp, int *fd);
void	handle_write(char **argv, char **envp, int *fd);
char	*find_path(char *cmd, char **envp);
void	execute(char *cmd1, char **envp);

#endif