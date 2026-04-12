/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 19:44:04 by nalfonso          #+#    #+#             */
/*   Updated: 2026/04/12 20:31:21 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int ft_built_pwd(char **av, t_shell *shell)
{
    char *cwd;
    (void)av;
    (void)shell;
    cwd = getcwd(NULL, 0);
    if (!cwd)
        return (perror("pwd"), 1);
    printf("%s\n", cwd);
    free(cwd);
    return (0);
}
