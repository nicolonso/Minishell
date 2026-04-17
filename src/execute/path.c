/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 20:06:49 by nalfonso          #+#    #+#             */
/*   Updated: 2026/04/13 19:22:14 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_command_path(char *cmd, t_shell *shell)
{
	char	*path_env;
	char	**dirs;
	char	*tmp;
	char	*full_path;
	int		i;

	// If cmd has a '/' it's already a path (e.g. ./myscript or /bin/ls)
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	// Get PATH from env
	path_env = get_env_value(shell->env, "PATH");
	if (!path_env)
		return (NULL);
	dirs = ft_split(path_env, ':');
	if (!dirs)
		return (NULL);
	i = 0;
	while (dirs[i])
	{
		tmp = ft_strjoin(dirs[i], "/");
		full_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(full_path, X_OK) == 0)
		{
			ft_free_split(dirs); // free the dirs array
			return (full_path);
		}
		free(full_path);
		i++;
	}
	ft_free_split(dirs);
	return (NULL);
}
