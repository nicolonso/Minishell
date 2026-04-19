#include "minishell.h"

static int	unclosed_quote(char *s)
{
	int		i;
	char	q;

	i = 0;
	q = 0;
	while (s[i])
	{
		if (!q && (s[i] == '\'' || s[i] == '"'))
			q = s[i];
		else if (q && s[i] == q)
			q = 0;
		i++;
	}
	return (q);
}

static void	put_eof_quote_error(char q)
{
	ft_putstr_fd("minishell: syntax error: unexpected EOF ", 2);
	ft_putstr_fd("while looking for matching '", 2);
	ft_putchar_fd(q, 2);
	ft_putstr_fd("'\n", 2);
}

int	parse_tokenize_error(char *str, t_shell *shell)
{
	int	q;

	q = unclosed_quote(str);
	if (q)
		put_eof_quote_error((char)q);
	else
		ft_putstr_fd("minishell: syntax error\n", 2);
	shell->exit_status = 2;
	return (1);
}

int	parse_validate_error(t_shell *shell)
{
	ft_putstr_fd("minishell: syntax error\n", 2);
	shell->exit_status = 2;
	return (1);
}

int	parse_redir_error(t_shell *shell)
{
	ft_putstr_fd("minishell: syntax error near redirection\n", 2);
	shell->exit_status = 2;
	return (1);
}