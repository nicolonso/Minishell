#include "minishell.h"

static const char	*redir_type_name(int type)
{
	if (type == REDIR_IN)
		return ("REDIR_IN (<)");
	if (type == REDIR_OUT)
		return ("REDIR_OUT (>)");
	if (type == REDIR_APPEND)
		return ("REDIR_APPEND (>>)");
	if (type == HEREDOC)
		return ("HEREDOC (<<)");
	return ("UNKNOWN_REDIR");
}

static void	put_argv(char **av)
{
	int	i;

	i = 0;
	if (!av)
	{
		printf("(null)\n");
		return ;
	}
	while (av[i])
	{
		printf("\"%s\"", av[i]);
		if (av[i + 1])
			printf(" ");
		i++;
	}
	printf("\n");
}

static void	put_redirs(t_redir *r)
{
	int	i;

	i = 0;
	if (!r)
	{
		printf("  redirs: (none)\n");
		return ;
	}
	printf("  redirs:\n");
	while (r)
	{
		printf("    - #%d type=%s (%d) file=\"%s\"\n",
			i, redir_type_name(r->type), r->type,
			(r->file ? r->file : "(null)"));
		r = r->next;
		i++;
	}
}

void	ft_putcmds(t_cmd *cmds)
{
	int	n;

	n = 0;
	printf("!!ft_putcmds here!!\n");
	while (cmds)
	{
		printf("cmd #%d\n", n);
		printf("  av: ");
		put_argv(cmds->av);
		put_redirs(cmds->redirs);
		cmds = cmds->next;
		n++;
	}
	printf("!!ft_putcmds finished now!!\n");
}

t_cmd	*parse_input(char *str, t_shell *shell)
{
	t_token	*tokens;
	t_cmd	*cmds;

	tokens = tokenize(str);
	if (!tokens)
		return (parse_tokenize_error(str, shell), NULL);
	if (validate_tokens(tokens) != 0)
		return (free_tokens(tokens), parse_validate_error(shell), NULL);
	if (expand_tokens(tokens, shell) != 0)
		return (free_tokens(tokens), NULL);
	remove_quotes_tokens(tokens);
	remove_empty_words(&tokens);
	cmds = parse_build_cmds(tokens, shell);
	free_tokens(tokens);
	ft_putcmds(cmds);
	return (cmds);
}