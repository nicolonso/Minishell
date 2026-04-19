/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 18:48:02 by nalfonso          #+#    #+#             */
/*   Updated: 2026/04/19 13:58:42 by nalfonso         ###   ########.fr       */
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

int	ft_built_cd(char **av, t_shell *shell)
{
	char	*path;
	char	*oldpwd;

	if (av[1] && av[2])
		return (ft_putstr_fd("cd: too many arguments\n", 2),1);
	oldpwd = getcwd(NULL, 0);
	if (!av[1])
		path = get_env_value(shell->env, "HOME");
	else if (strcmp(av[1], "-") == 0)
		path = get_env_value(shell->env, "OLDPWD");
	else
		path = av[1];
	if (!path)
		return (ft_putstr_fd("cd: path not set\n", 2), free(oldpwd), 1);
	if (chdir(path) != 0)
		return (perror("cd"), free(oldpwd), 1);
	if (av[1] && strcmp(av[1], "-") == 0)
	{
		write(STDOUT_FILENO, path, ft_strlen(path));
		write(STDOUT_FILENO, "\n", 1);		
	}
	update_pwd_vars(shell, oldpwd);
	free(oldpwd);
	return (0);
}
