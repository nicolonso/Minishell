/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 20:32:10 by qcyril-a          #+#    #+#             */
/*   Updated: 2026/04/12 22:09:00 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void  free_redirs(t_redir *redir)
{
    t_redir *next;

    while (redir)
    {
        next = redir->next;
        free(redir->file);
        free(redir);
        redir = next;
    }
}

static void  free_cmd(t_cmd *cmd)
{
    t_cmd   *next;

    while (cmd)
    {
        next = cmd->next;
        ft_free_split(cmd->av);
        free_redirs(cmd->redirs);
        free(cmd);
        cmd = next;
    }
}

void    prompt_loop(t_shell *shell)
{
    char    *input;
    t_cmd   *cmd;

    while (1)
    {
        input = readline("minishell$ ");
        if (!input)
            break ;
        if (*input)
            add_history(input);
        if (ft_strcmp(input, "") != 0)
        {
            cmd = parse_input(input, shell);
            if (cmd)
            {
                ft_executor(cmd, shell);
                free_cmd(cmd);
            }
        }
        free(input);
    }
}
