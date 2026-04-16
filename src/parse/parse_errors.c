/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcyril-a <qcyril-a@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 19:54:35 by qcyril-a          #+#    #+#             */
/*   Updated: 2026/04/16 19:54:38 by qcyril-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

int	parse_tokenize_error(char *str, t_shell *shell)
{
	int	q;

	q = unclosed_quote(str);
	if (q)
		fprintf(stderr,
			"minishell: syntax error: unexpected EOF while looking for matching '%c'\n",
			q);
	else
		fprintf(stderr, "minishell: syntax error\n");
	shell->exit_status = 2;
	return (1);
}

int	parse_validate_error(t_shell *shell)
{
	fprintf(stderr, "minishell: syntax error\n");
	shell->exit_status = 2;
	return (1);
}

int	parse_redir_error(t_shell *shell)
{
	fprintf(stderr, "minishell: syntax error near redirection\n");
	shell->exit_status = 2;
	return (1);
}
