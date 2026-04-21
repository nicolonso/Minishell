/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 00:00:00 by nalfonso          #+#    #+#             */
/*   Updated: 2026/04/13 00:00:00 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	parse_heredoc_delim(char **out_delim, char *raw)
{
	int	len;

	if (!raw)
		return (0);
	len = ft_strlen(raw);
	if ((raw[0] == '\'' || raw[0] == '"') && len >= 2 && raw[len - 1] == raw[0])
	{
		*out_delim = ft_strndup(raw + 1, len - 2);
		if (!*out_delim)
			return (-1);
		return (0);
	}
	*out_delim = ft_strdup(raw);
	if (!*out_delim)
		return (-1);
	return (1);
}

void	heredoc_child_loop(int wfd, char *del, int do_expand, t_shell *shell)
{
	char	*line;

	setup_signals_child();
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			close(wfd);
			exit(130);
		}
		if (ft_strcmp(line, del) == 0)
		{
			free(line);
			break ;
		}
		write_heredoc_output(wfd, line, do_expand, shell);
		free(line);
	}
	close(wfd);
	exit(0);
}

int	handle_heredoc(char *delimiter, t_shell *shell)
{
	int		pipefd[2];
	pid_t	pid;
	char	*del;
	int		do_expand;

	if (pipe(pipefd) < 0)
		return (perror("pipe"), -1);
	do_expand = parse_heredoc_delim(&del, delimiter);
	if (do_expand < 0)
		return (perror("malloc"), close(pipefd[0]), close(pipefd[1]), -1);
	setup_signals_exec();
	pid = fork();
	if (pid < 0)
		return (perror("fork"), free(del), close(pipefd[0]), \
close(pipefd[1]), -1);
	if (pid == 0)
	{
		close(pipefd[0]);
		heredoc_child_loop(pipefd[1], del, do_expand, shell);
	}
	close(pipefd[1]);
	free(del);
	if (wait_heredoc_child(pipefd[0], pid) == -1)
		return (-1);
	return (pipefd[0]);
}

static int	open_redir_fd(t_redir *redir, t_shell *shell)
{
	int	fd;

	fd = -1;
	if (redir->type == REDIR_IN)
		fd = open(redir->file, O_RDONLY);
	else if (redir->type == REDIR_OUT)
		fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redir->type == REDIR_APPEND)
		fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (redir->type == HEREDOC)
		fd = handle_heredoc(redir->file, shell);
	return (fd);
}

int	apply_redirections(t_redir *redir, t_shell *shell)
{
	int	fd;

	while (redir)
	{
		fd = open_redir_fd(redir, shell);
		if (fd < 0)
		{
			if (redir->type != HEREDOC)
				perror(redir->file);
			return (-1);
		}
		if (redir->type == REDIR_IN || redir->type == HEREDOC)
			dup2(fd, STDIN_FILENO);
		else
			dup2(fd, STDOUT_FILENO);
		close(fd);
		redir = redir->next;
	}
	return (0);
}
