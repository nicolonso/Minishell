/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 02:15:47 by nalfonso          #+#    #+#             */
/*   Updated: 2026/04/21 02:16:27 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

volatile sig_atomic_t	g_sig = 0;

static void	sigint_prompt(int signum)
{
	(void)signum;
	g_sig = SIGINT;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	setup_signals_prompt(void)
{
	struct sigaction	sa;

	rl_catch_signals = 0;
	rl_event_hook = NULL;
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = sigint_prompt;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

static void	heredoc_sigint_handler(int signum)
{
	(void)signum;
	g_sig = SIGINT;
	write(1, "\n", 1);
}

void	setup_signals_heredoc(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = heredoc_sigint_handler;
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}
