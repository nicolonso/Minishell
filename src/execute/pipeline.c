/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 00:00:00 by nalfonso          #+#    #+#             */
/*   Updated: 2026/04/13 00:00:00 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	exec_child(t_cmd *cmd, t_shell *shell, int (*pipes)[2],
				int i_and_count[2])
{
	char	*path;
	char	**env_arr;

	setup_signals_child();
	child_pipe_setup(pipes, i_and_count[0], i_and_count[1]);
	apply_redirections(cmd->redirs);
	if (is_builtin(cmd->av[0]))
	{
		execute_built_in_parent(cmd, shell);
		exit(shell->exit_status);
	}
	path = get_command_path(cmd->av[0], shell);
	env_arr = env_to_arr(shell->env);
	if (!path)
	{
		ft_putstr_fd(cmd->av[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		ft_free_split(env_arr);
		exit(127);
	}
	execve(path, cmd->av, env_arr);
	perror("execve");
	free(path);
	ft_free_split(env_arr);
	exit(126);
}

static int	wait_children(pid_t *pids, int cmd_count)
{
	int	i;
	int	status;
	int	last_status;

	last_status = 0;
	i = 0;
	while (i < cmd_count)
	{
		waitpid(pids[i], &status, 0);
		if (i == cmd_count - 1)
		{
			if (WIFEXITED(status))
				last_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				last_status = 128 + WTERMSIG(status);
		}
		i++;
	}
	return (last_status);
}

static void	fork_commands(t_cmd *cmd, t_shell *shell,
				int (*pipes)[2], pid_t *pids)
{
	int		cmd_count;
	int		i;
	int		args[2];
	t_cmd	*cur;

	cmd_count = count_cmds(cmd);
	cur = cmd;
	i = 0;
	while (cur)
	{
		args[0] = i;
		args[1] = cmd_count;
		pids[i] = fork();
		if (pids[i] == 0)
			exec_child(cur, shell, pipes, args);
		cur = cur->next;
		i++;
	}
}

int	execute_pipeline(t_cmd *cmd, t_shell *shell)
{
	int		cmd_count;
	int		(*pipes)[2];
	pid_t	*pids;

	cmd_count = count_cmds(cmd);
	if (cmd_count == 1 && cmd->av && cmd->av[0] && is_builtin(cmd->av[0]))
		return (execute_builtin_with_redir(cmd, shell));
	pipes = malloc(sizeof(int [2]) * (cmd_count - 1));
	pids = malloc(sizeof(pid_t) * cmd_count);
	setup_signals_exec();
	fork_commands(cmd, shell, pipes, pids);
	close_all_pipes(pipes, cmd_count - 1);
	shell->exit_status = wait_children(pids, cmd_count);
	setup_signals_prompt();
	free(pipes);
	free(pids);
	return (shell->exit_status);
}
