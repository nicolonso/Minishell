/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 19:34:46 by nalfonso          #+#    #+#             */
/*   Updated: 2026/04/12 22:12:36 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

int     execute_external(t_cmd *cmd, t_shell *shell)
{
    pid_t   pid;
    int     status;
    char    *path;
    char    **env_arr;    /* ← new */

    pid = fork();
    if (pid < 0)
        return (perror("fork"), 1);
    if (pid == 0)
    {
        path    = get_command_path(cmd->av[0], shell);
        env_arr = env_to_arr(shell->env);  /* ← convert list → char** */
        if (!path)
        {
            fprintf(stderr, "%s: command not found\n", cmd->av[0]);
            ft_free_split(env_arr);
            exit(127);
        }
        execve(path, cmd->av, env_arr);     /* ← char** now, no error */
        perror("execve");
        free(path);
        ft_free_split(env_arr);
        exit(126);
    }
    waitpid(pid, &status, 0);
    if (WIFEXITED(status))
        return (WEXITSTATUS(status));
    if (WIFSIGNALED(status))
        return (128 + WTERMSIG(status));
    return (1);
}

int ft_executor(t_cmd *cmd, t_shell *shell)
{
	if (!cmd || !cmd->av || !cmd->av[0])
		return (0);
	return (execute_pipeline(cmd, shell));
}
