/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 20:32:10 by qcyril-a          #+#    #+#             */
/*   Updated: 2026/04/17 00:00:00 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	free_redirs(t_redir *redir)
{
	t_redir	*next;

	while (redir)
	{
		next = redir->next;
		free(redir->file);
		free(redir);
		redir = next;
	}
}

static void	free_cmd(t_cmd *cmd)
{
	t_cmd	*next;

	while (cmd)
	{
		next = cmd->next;
		ft_free_split(cmd->av);
		free_redirs(cmd->redirs);
		free(cmd);
		cmd = next;
	}
}

static void	process_input(char *input, t_shell *shell)
{
	t_cmd	*cmd;

	if (!*input)
		return ;
	add_history(input);
	cmd = parse_input(input, shell);
	if (cmd)
	{
		ft_executor(cmd, shell);
		free_cmd(cmd);
	}
}

void	prompt_loop(t_shell *shell)
{
	char	*input;

	setup_signals_prompt();
	while (1)
	{
		g_sig = 0;
		input = readline("minishell$ ");
		if (!input)
		{
			write(STDOUT_FILENO, "exit\n", 5);
			break ;
		}
		process_input(input, shell);
		if (g_sig == SIGINT)
			shell->exit_status = 130;
		free(input);
	}
	rl_clear_history();
}
