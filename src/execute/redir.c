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
#include <termios.h>

static void	restore_termios_flags(void)
{
	struct termios	t;

	if (tcgetattr(STDIN_FILENO, &t) == -1)
		return ;
	t.c_lflag |= (ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

static void	heredoc_child_loop(int wfd, char *del)
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
		write(wfd, line, ft_strlen(line));
		write(wfd, "\n", 1);
		free(line);
	}
	close(wfd);
	exit(0);
}

static void	clear_stdin_buffer(void)
{
	if (!isatty(STDIN_FILENO))
		return ;
	/* discard any pending input / EOF state */
	tcflush(STDIN_FILENO, TCIFLUSH);
}

static void	cleanup_readline_after_signal(void)
{
	/* reset readline internal state if available */
	rl_cleanup_after_signal();
	/* clear current line buffer and mark a new line */
	rl_replace_line("", 0);
	rl_on_new_line();
}

static int	wait_heredoc_child(int rfd, pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	setup_signals_prompt();
	restore_termios_flags();
	clear_stdin_buffer();
	if ((WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		|| (WIFEXITED(status) && WEXITSTATUS(status) == 130))
	{
		g_sig = SIGINT;
		write(1, "\n", 1);
		cleanup_readline_after_signal();
		close(rfd);
		return (-1);
	}
	cleanup_readline_after_signal();
	return (0);
}

int	handle_heredoc(char *delimiter)
{
	int	pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) < 0)
		return (perror("pipe"), -1);
	setup_signals_exec();
	pid = fork();
	if (pid < 0)
		return (perror("fork"), close(pipefd[0]), close(pipefd[1]), -1);
	if (pid == 0)
	{
		close(pipefd[0]);
		heredoc_child_loop(pipefd[1], delimiter);
	}
	close(pipefd[1]);
	if (wait_heredoc_child(pipefd[0], pid) == -1)
		return (-1);
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

int	apply_redirections(t_redir *redir)
{
	int	fd;

	while (redir)
	{
		fd = open_redir_fd(redir);
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
