/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 18:48:02 by nalfonso          #+#    #+#             */
/*   Updated: 2026/04/20 11:41:03 by qcyril-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_pwd_vars(t_shell *shell, char *oldpwd)
{
	char	*newpwd;

	if (oldpwd)
		update_env_value(shell->env, "OLDPWD", oldpwd);
	newpwd = getcwd(NULL, 0);
	if (newpwd)
	{
		update_env_value(shell->env, "PWD", newpwd);
		free(newpwd);
	}
}

static int	cd_too_many_args(void)
{
	ft_putstr_fd("cd: too many arguments\n", 2);
	return (1);
}

static char	*cd_get_path(char **av, t_shell *shell)
{
	if (!av[1])
		return (get_env_value(shell->env, "HOME"));
	if (strcmp(av[1], "-") == 0)
		return (get_env_value(shell->env, "OLDPWD"));
	return (av[1]);
}

static void	cd_print_oldpwd(char **av, char *path)
{
	if (av[1] && strcmp(av[1], "-") == 0)
	{
		write(STDOUT_FILENO, path, ft_strlen(path));
		write(STDOUT_FILENO, "\n", 1);
	}
}

int	ft_built_cd(char **av, t_shell *shell)
{
	char	*path;
	char	*oldpwd;

	if (av[1] && av[2])
		return (cd_too_many_args());
	oldpwd = getcwd(NULL, 0);
	path = cd_get_path(av, shell);
	if (!path)
	{
		ft_putstr_fd("cd: path not set\n", 2);
		free(oldpwd);
		return (1);
	}
	if (chdir(path) != 0)
	{
		perror("cd");
		free(oldpwd);
		return (1);
	}
	cd_print_oldpwd(av, path);
	update_pwd_vars(shell, oldpwd);
	free(oldpwd);
	return (0);
}
