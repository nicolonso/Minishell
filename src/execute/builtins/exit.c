/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 20:05:54 by nalfonso          #+#    #+#             */
/*   Updated: 2026/04/12 22:12:07 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int     ft_built_exit(char **av, t_shell *shell)
{
    int code;

    printf("exit\n");
    if (!av[1])
        code = shell->exit_status;  /* exit with last status */
    else if (av[2])
    {
        fprintf(stderr, "exit: too many arguments\n");
        return (1);
    }
    else
        code = atoi(av[1]) & 255; /* exit codes are 0-255 */
    exit(code);
}

/* ── executor.c — already correct, just verify ───── */
/* ft_executor sets shell->exit_status after every    */
/* command so $? is always up to date:                */
