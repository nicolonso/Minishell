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

static void	exec_external_cmd(t_cmd *cmd, t_shell *shell)
{
	char	*path;
	char	**env_arr;

	env_arr = env_to_arr(shell->env);
	if (ft_strchr(cmd->av[0], '/'))
	{
		check_direct_path_or_exit(cmd->av[0]);
		execve(cmd->av[0], cmd->av, env_arr);
		perror(cmd->av[0]);
		ft_free_split(env_arr);
		exit(126);
	}
	path = get_command_path(cmd->av[0], shell);
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

static void	exec_child(t_cmd *cmd, t_shell *shell, int (*pipes)[2],
				int i_and_count[2])
{
	setup_signals_child();
	child_pipe_setup(pipes, i_and_count[0], i_and_count[1]);
	if (apply_redirections(cmd->redirs, shell) < 0)
	{
		if (g_sig == SIGINT)
			exit (130);
		exit(1);
	}
	if (is_builtin(cmd->av[0]))
	{
		execute_built_in_parent(cmd, shell);
		exit(shell->exit_status);
	}
	exec_external_cmd(cmd, shell);
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
			{
				last_status = 128 + WTERMSIG(status);
				if (WTERMSIG(status) == SIGINT)
					write(1, "\n", 1);
			}
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
	if (!pipes)
		return (free(pipes), 1);
	pids = malloc(sizeof(pid_t) * cmd_count);
	if (!pids)
		return (free(pids), 1);
	if (create_pipes(pipes, cmd_count - 1) < 0)
		return (free(pipes), free(pids), 1);
	setup_signals_exec();
	fork_commands(cmd, shell, pipes, pids);
	close_all_pipes(pipes, cmd_count - 1);
	shell->exit_status = wait_children(pids, cmd_count);
	setup_signals_prompt();
	free(pipes);
	free(pids);
	return (shell->exit_status);
}
