/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 22:34:13 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/01/15 16:43:33 by lsilva-x         ###   ########.fr       */
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
# include "../lib/libft/includes/libft.h"

void	handler_error(const char *msg, int cod);
int		ft_print_string(const char *str);
void	apply_function(char *cmd, char **envp);
void	first_processing(char **argv, char **envp, int *fd);
char	*path_searcher(char *cmd, char **envp);
void	second_processing(char **argv, char **envp, int *fd);
char	*verify_full_path(char *cmd);
void	freethe(char **cmdpath);

#endif