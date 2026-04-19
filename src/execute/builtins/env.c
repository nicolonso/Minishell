/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 20:05:05 by nalfonso          #+#    #+#             */
/*   Updated: 2026/04/18 22:12:02 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_built_env(char **av, t_shell *shell)
{
	t_env	*e;

	(void)av;
	e = shell->env;
	while (e)
	{
		if (e->value)
			printf("%s=%s\n", e->key, e->value);
		else
			printf("%s=\n", e->key);
		e = e->next;
	}
	return (0);
}
