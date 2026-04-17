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

	rl_catch_signals = 0;   /* we manage signals ourselves */
	rl_event_hook = NULL;  /* don't depend on it */

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = sigint_prompt;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);

	signal(SIGQUIT, SIG_IGN);
}
