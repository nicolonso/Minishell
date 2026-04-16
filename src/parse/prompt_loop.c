/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 20:32:10 by qcyril-a          #+#    #+#             */
/*   Updated: 2026/04/16 20:09:46 by qcyril-a         ###   ########.fr       */
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

void  free_cmd(t_cmd *cmd)
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

	setup_signals_prompt();

    while (1)
    {
		rl_done = 0; //extra safety
        input = readline("minishell$ ");
		if (g_sig == SIGINT)
		{
			g_sig = 0;
			rl_done = 0;
			shell->exit_status = 130;
			free(input);
			continue;
		}
        if (!input)
		{
			write(1, "exit\n", 5);
            //break ;
			//exit(shell->last_status);
			exit(shell->exit_status);
        }
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
