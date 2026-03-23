/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 19:34:46 by nalfonso          #+#    #+#             */
/*   Updated: 2026/03/23 19:54:16 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int is_builtin(char *cmd_name)
{
	if (!cmd_name)
		return (0);
	if (strcmp(cmd_name, "echo") == 0)
		return (1);
	if (strcmp(cmd_name, "cd") == 0)
		return (1);
	if (strcmp(cmd_name, "pwd") == 0)
		return (1);
	if (strcmp(cmd_name, "export") == 0)
		return (1);
	if (strcmp(cmd_name, "unset") == 0)
		return (1);
	if (strcmp(cmd_name, "env") == 0)
		return (1);
	if (strcmp(cmd_name, "exit") == 0)
		return (1);
	return (0);
}

int execute_built_in_parent(t_cmd *cmd, t_shell *shell)
{
	if (strcmp(cmd->av[0], "cd") == 0)
		return (ft_built_cd(cmd->av, shell));
	else if (strcmp(cmd->av[0], "echo") == 0)
		return (ft_built_echo(cmd->av, shell));
	else if (strcmp(cmd->av[0], "pwd") == 0)
		return (ft_built_pwd(cmd->av, shell));
	else if (strcmp(cmd->av[0], "export") == 0)
		return (ft_built_export(cmd->av, shell));
	else if (strcmp(cmd->av[0], "unset") == 0)
		return (ft_built_unset(cmd->av, shell));
	else if (strcmp(cmd->av[0], "env") == 0)
		return (ft_built_env(cmd->av, shell));
	else if (strcmp(cmd->av[0], "exit") == 0)
		return (ft_built_exit(cmd->av, shell));
	return (1);
}

int execute_external(t_cmd *cmd, t_shell *shell)
{
	pid_t	pid;
	int		status;
	char	*path;
	
	pid = fork();
	if (pid < 0)
		return (perror("fork"), 1);
	if (pid == 0)
	{
		path = get_command_path(cmd->av[0], shell); // I need built this function
		if (!path)
		{
			fprintf(stderr, "%s: command not found\n", cmd->av[0]);
			exit (127);
		}
		execve(path, cmd->av, shell->env);
		perror("execve");
		exit (126);
 	}
	waitpid (pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

int ft_executor(t_cmd *cmd, t_shell *shell)
{
	int status;

	if (!cmd || !cmd->av || !cmd->av[0])
		return (0);
	if (is_builtin(cmd->av[0]))
		status = execute_built_in_parent(cmd, shell);
	else
		status = execute_external(cmd, shell);
	shell->exit_status = status;
	return (status);
}
