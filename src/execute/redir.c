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

#include "../include/minishell.h"

static int	handle_heredoc(char *delimiter)
{
	int		pipefd[2];
	char	*line;

	if (pipe(pipefd) < 0)
	{
		perror("pipe");
		return (-1);
	}
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
	close(pipefd[1]);
	return (pipefd[0]);
}

static int	open_redir_fd(t_redir *redir)
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
		fd = handle_heredoc(redir->file);
	return (fd);
}

void	apply_redirections(t_redir *redir)
{
	int	fd;

	while (redir)
	{
		fd = open_redir_fd(redir);
		if (fd < 0)
		{
			perror(redir->file);
			exit(1);
		}
		if (redir->type == REDIR_IN || redir->type == HEREDOC)
			dup2(fd, STDIN_FILENO);
		else
			dup2(fd, STDOUT_FILENO);
		close(fd);
		redir = redir->next;
	}
}
