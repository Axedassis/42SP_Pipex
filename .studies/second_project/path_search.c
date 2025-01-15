/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_search.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 11:19:06 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/01/14 11:20:40 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex.h"

void	freethe(char **cmdpath)
{
	int	ind;

	ind = 0;
	while (cmdpath[ind])
	{
		free(cmdpath[ind]);
		ind++;
	}
	free(cmdpath);
}

static char	*findpath(char **envar)
{
	int	ind;

	ind = 0;
	if (!envar)
		return (NULL);
	while (envar[ind])
	{
		if (ft_strncmp(envar[ind], "PATH=", 5) == 0)
			return (envar[ind] + 5);
		ind++;
	}
	return (NULL);
}

static char	*trypath(char *cmd, char *path)
{
	char	*partialpath;
	char	*fullpath;

	partialpath = ft_strjoin(path, "/");
	if (!partialpath)
		return (NULL);
	fullpath = ft_strjoin(partialpath, cmd);
	free(partialpath);
	if (!fullpath)
		return (NULL);
	if (access(fullpath, F_OK) == 0)
		return (fullpath);
	free(fullpath);
	return (NULL);
}

char	*check_abspath(char *cmd)
{
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK | X_OK) == 0)
			return (ft_strdup(cmd));
		ft_putstr_fd("\033[31mError: Command not found or executable: \033[0m",
			2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd("\n", 2);
		return (NULL);
	}
	return (NULL);
}

char	*path_searcher(char *cmd, char **envar)
{
	char	**cmdpath;
	char	*fullpath;
	char	*path_vars;
	int		ind;

	if (!cmd || !envar)
		return (NULL);
	fullpath = check_abspath(cmd);
	if (fullpath)
		return (fullpath);
	path_vars = findpath(envar);
	if (!path_vars)
		return (NULL);
	cmdpath = ft_split(path_vars, ':');
	if (!cmdpath)
		return (NULL);
	ind = -1;
	while (cmdpath[++ind])
	{
		fullpath = trypath(cmd, cmdpath[ind]);
		if (fullpath)
			return (freethe(cmdpath), fullpath);
	}
	return (freethe(cmdpath), NULL);
}
