/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 20:04:22 by nalfonso          #+#    #+#             */
/*   Updated: 2026/04/12 20:31:07 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int ft_built_echo(char **av, t_shell *shell)
{
    (void)shell;
    int i = 1;
    int newline = 1;
    if (av[1] && ft_strcmp(av[1], "-n") == 0)
    {
        newline = 0;
        i = 2;
    }
    while (av[i])
    {
        printf("%s", av[i]);
        if (av[i + 1])
            printf(" ");
        i++;
    }
    if (newline)
        printf("\n");
    return (0);
}