/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 20:05:05 by nalfonso          #+#    #+#             */
/*   Updated: 2026/04/12 20:31:35 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int ft_built_env(char **av, t_shell *shell)
{
    t_env *e;
    (void)av;
    e = shell->env;
    while (e)
    {
        printf("%s=%s\n", e->key, e->value ? e->value : "");
        e = e->next;
    }
    return (0);
}
