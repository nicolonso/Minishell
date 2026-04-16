#include "../../include/minishell.h"

volatile sig_atomic_t g_sig = 0;

void	sigint_handler(int signum)
{
	g_sig = signum;
}

static int	rl_sigint_hook(void)
{
	if (g_sig == SIGINT)
	{
		rl_done = 1;
		return 0;
	}
	return 0;
}

void setup_signals_prompt(void)
{
	struct sigaction sa;

	rl_catch_signals = 0;
	rl_event_hook = rl_sigint_hook;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = sigint_handler;
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);

	signal(SIGQUIT, SIG_IGN);
}

