/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 00:00:00 by nalfonso          #+#    #+#             */
/*   Updated: 2026/04/17 00:00:00 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** The ONE allowed global variable (42 norm: max 1 global).
** Set to the signal number when a signal fires so the shell
** can check it after readline() or waitpid() returns.
*/
int	g_sig = 0;

/*
** Handler for SIGINT (Ctrl+C) during the prompt phase.
** - Prints a newline so the cursor moves to a clean line.
** - Clears readline's internal buffer so the user gets a
**   blank new prompt instead of seeing leftover text.
** - rl_redisplay() redraws the prompt on the new line.
*/
static void	sigint_prompt(int sig)
{
	g_sig = sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/*
** Called before readline() — while the shell is idle waiting
** for user input.
**   SIGINT  → custom handler: reprints the prompt on a new line
**   SIGQUIT → ignored (Ctrl+\ does nothing at the prompt)
*/
void	setup_signals_prompt(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = sigint_prompt;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

/*
** Called in the PARENT process right before forking children.
** The parent ignores both signals while waiting for children —
** this way Ctrl+C only reaches the child processes (via the
** terminal's process group), not the shell itself.
**
** The children call setup_signals_child() to reset to SIG_DFL
** so they actually die when Ctrl+C is pressed.
*/
void	setup_signals_exec(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

/*
** Called inside each CHILD process immediately after fork().
** Resets SIGINT and SIGQUIT to the kernel default so that:
**   Ctrl+C  → terminates the child (SIGINT  → default = terminate)
**   Ctrl+\  → terminates the child (SIGQUIT → default = core dump)
** Without this reset, the child would inherit SIG_IGN from the
** parent and Ctrl+C would have no effect on running commands.
*/
void	setup_signals_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
