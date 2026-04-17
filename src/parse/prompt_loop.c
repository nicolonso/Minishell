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

int	prompt_loop(t_shell *shell)
{
	char	*input;
	t_cmd	*cmd;

	setup_signals_prompt();
	while (1)
	{
		input = readline("minishell$ ");

		/* Ctrl-C: readline may return "" or NULL depending on handler */
		if (g_sig == SIGINT)
		{
			g_sig = 0;
			shell->exit_status = 130;
			free(input);
			continue;
		}

		if (!input) /* Ctrl-D (EOF) */
		{
			write(1, "exit\n", 5);
			break;
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
	return (shell->exit_status);
}
