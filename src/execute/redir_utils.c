/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcyril-a <qcyril-a@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 15:14:07 by qcyril-a          #+#    #+#             */
/*   Updated: 2026/04/21 15:14:08 by qcyril-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	restore_termios_flags(void)
{
	struct termios	t;

	if (tcgetattr(STDIN_FILENO, &t) == -1)
		return ;
	t.c_lflag |= (ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

void	heredoc_child_loop(int wfd, char *del)
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

void	clear_stdin_buffer(void)
{
	if (!isatty(STDIN_FILENO))
		return ;
	tcflush(STDIN_FILENO, TCIFLUSH);
}

void	cleanup_readline_after_signal(void)
{
	rl_cleanup_after_signal();
	rl_replace_line("", 0);
	rl_on_new_line();
}

int	wait_heredoc_child(int rfd, pid_t pid)
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
