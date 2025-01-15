/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_search.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 11:19:06 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/01/15 16:47:11 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	free_pp(char **cmdpath)
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

static char	*findpath(char **envp)
{
	int	i;

	i = 0;
	if (!envp)
		return (NULL);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

static char	*try_path(char *cmd, char *path)
{
	char	*node_path;
	char	*full_path;

	node_path = ft_strjoin(path, "/");
	if (!node_path)
		return (NULL);
	full_path = ft_strjoin(node_path, cmd);
	free(node_path);
	if (!full_path)
		return (NULL);
	if (access(full_path, F_OK) == 0)
		return (full_path);
	free(full_path);
	return (NULL);
}

char	*verify_full_path(char *cmd)
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

char	*path_searcher(char *cmd, char **envp)
{
	char	**splited_path;
	char	*full_path;
	char	*path_vars;
	int		i;

	if (!cmd || !envp)
		return (NULL);
	full_path = verify_full_path(cmd);
	if (full_path)
		return (full_path);
	path_vars = findpath(envp);
	if (!path_vars)
		return (NULL);
	splited_path = ft_split(path_vars, ':');
	if (!splited_path)
		return (NULL);
	i = -1;
	while (splited_path[++i])
	{
		full_path = try_path(cmd, splited_path[i]);
		if (full_path)
			return (free_pp(splited_path), full_path);
	}
	return (free_pp(splited_path), NULL);
}
