/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 18:48:02 by nalfonso          #+#    #+#             */
/*   Updated: 2026/04/12 20:28:16 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	update_pwd_vars(t_shell *shell, char * oldpwd)
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

int ft_built_cd(char **av, t_shell *shell)
{
	char	*path;
	char	*oldpwd;

	if (av[1] && av[2])
	{
		fprintf(stderr, "cd: too many arguments\n");
		return (1);
	}
	oldpwd = getcwd(NULL, 0); //Search info about this function
	if (!av[1])
		path = get_env_value(shell->env, "HOME");
	else if (strcmp(av[1], "-") == 0)
		path = get_env_value(shell->env, "OLDPWD");
	else
		path = av[1];
	if (!path)
		return (fprintf(stderr, "cd: path not set\n"), free(oldpwd), 1);
	if (chdir(path) != 0)
		return (perror("cd"), free(oldpwd), 1);
	if (av[1] && strcmp(av[1], "-") == 0)
		printf("%s\n", path);
	update_pwd_vars(shell, oldpwd);
	free(oldpwd);
	return (0);
}
