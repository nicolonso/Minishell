/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 20:32:10 by qcyril-a          #+#    #+#             */
/*   Updated: 2026/04/16 15:14:27 by qcyril-a         ###   ########.fr       */
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

void	sigint_handler(int signum)
{
	(void) signum;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void    prompt_loop(t_shell *shell)
{
    char    *input;
    t_cmd   *cmd;

	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);

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
