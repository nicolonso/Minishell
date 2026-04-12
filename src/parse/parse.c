/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 18:21:12 by nalfonso          #+#    #+#             */
/*   Updated: 2026/04/12 21:18:29 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* size_t	parse_input(char *str)
{
    return (printf("You typed this: %s\n", str));
} */

t_cmd   *parse_input(char *str, t_shell *shell)
{
    t_cmd   *cmd;

    (void)shell;
    cmd = ft_calloc(1, sizeof(t_cmd));
    if (!cmd)
        return (NULL);
    cmd->av = ft_split(str, ' ');
    cmd->redirs = NULL;
    cmd->next = NULL;
    return (cmd);
}