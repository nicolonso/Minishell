/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 18:48:02 by nalfonso          #+#    #+#             */
/*   Updated: 2026/04/21 18:29:43 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	update_pwd_vars(t_shell *shell, char *oldpwd)
{
	char	*newpwd;

	if (oldpwd)
		update_env_value(shell->env, "OLDPWD", oldpwd);
	newpwd = getcwd(NULL, 0);
	if (newpwd)
	{
		update_env_value(shell->env, "PWD", newpwd);
		free (newpwd);
	}
}

static char	*get_cd_path(char **av, t_shell *shell, int *is_dash)
{
	char	*path;

	*is_dash = 0;
	if (!av[1])
		path = get_env_value(shell->env, "HOME");
	else if (strcmp(av[1], "-") == 0)
	{
		*is_dash = 1;
		path = get_env_value(shell->env, "OLDPWD");
	}
	else
		path = av[1];
	return (path);
}

static int	change_directory(char *path, char *oldpwd)
{
	if (chdir(path) != 0)
	{
		perror("cd");
		free(path);
		free(oldpwd);
		return (1);
	}
	return (0);
}

int	ft_built_cd(char **av, t_shell *shell)
{
	char	*path;
	char	*oldpwd;
	int		is_dash;

	if (av[1] && av[2])
		return (ft_putstr_fd("cd: too many arguments\n", 2), 1);
	oldpwd = getcwd(NULL, 0);
	path = get_cd_path(av, shell, &is_dash);
	if (!path)
		return (ft_putstr_fd("cd: path not set\n", 2), free(oldpwd), 1);
	path = ft_strdup(path);
	if (!path)
		return (free(oldpwd), 1);
	if (change_directory(path, oldpwd))
		return (1);
	if (is_dash)
		printf("%s\n", path);
	update_pwd_vars(shell, oldpwd);
	free(path);
	free(oldpwd);
	return (0);
}
