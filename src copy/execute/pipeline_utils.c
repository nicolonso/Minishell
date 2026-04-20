/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcyril-a <qcyril-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 13:43:34 by nalfonso          #+#    #+#             */
/*   Updated: 2026/04/20 12:12:14 by qcyril-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_builtin_with_redir(t_cmd *cmd, t_shell *shell)
{
	int	saved_in;
	int	saved_out;

	saved_in = dup(STDIN_FILENO);
	saved_out = dup(STDOUT_FILENO);
	if (apply_redirections(cmd->redirs) < 0)
	{
		restore_stdio(saved_in, saved_out);
		shell->exit_status = 1;
		return (1);
	}
	shell->exit_status = execute_built_in_parent(cmd, shell);
	restore_stdio(saved_in, saved_out);
	return (shell->exit_status);
}

int	create_pipes(int (*pipes)[2], int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (pipe(pipes[i]) < 0)
		{
			close_all_pipes(pipes, i);
			perror("pipe");
			return (-1);
		}
		i++;
	}
	return (0);
}

void	exec_path_error(char *path, int code, char *msg)
{
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	exit(code);
}

void	check_direct_path_or_exit(char *path)
{
	struct stat	st;

	if (stat(path, &st) != 0)
	{
		perror(path);
		exit(127);
	}
	if (S_ISDIR(st.st_mode))
		exec_path_error(path, 126, "Is a directory");
	if (access(path, X_OK) != 0)
	{
		perror(path);
		exit(126);
	}
}
