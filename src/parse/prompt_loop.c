/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 13:35:10 by nalfonso          #+#    #+#             */
/*   Updated: 2026/04/19 13:35:12 by nalfonso         ###   ########.fr       */
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

void	free_cmd(t_cmd *cmd)
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

static int	handle_prompt_input(char *input, t_shell *shell)
{
	if (g_sig == SIGINT)
	{
		g_sig = 0;
		shell->exit_status = 130;
		free(input);
		return (1);
	}
	if (!input)
	{
		write(1, "exit\n", 5);
		return (2);
	}
	return (0);
}

static void	execute_prompt_input(char *input, t_shell *shell)
{
	t_cmd	*cmd;

	if (*input)
		add_history(input);
	if (ft_strcmp(input, "") == 0)
		return ;
	cmd = parse_input(input, shell);
	if (!cmd)
		return ;
	ft_executor(cmd, shell);
	free_cmd(cmd);
}

int	prompt_loop(t_shell *shell)
{
	char	*input;
	int		status;

	setup_signals_prompt();
	while (1)
	{
		input = readline("minishell$ ");
		status = handle_prompt_input(input, shell);
		if (status == 1)
			continue ;
		if (status == 2)
			break ;
		execute_prompt_input(input, shell);
		free(input);
	}
	return (shell->exit_status);
}
