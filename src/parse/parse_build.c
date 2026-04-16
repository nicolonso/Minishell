/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_build.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcyril-a <qcyril-a@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 19:55:06 by qcyril-a          #+#    #+#             */
/*   Updated: 2026/04/16 19:58:34 by qcyril-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	is_redir_token(int type)
{
	return (type == TOK_REDIR_IN || type == TOK_REDIR_OUT
		|| type == TOK_APPEND || type == TOK_HEREDOC);
}

static int	redir_type_from_token(int tok_type)
{
	if (tok_type == TOK_REDIR_IN)
		return (REDIR_IN);
	if (tok_type == TOK_REDIR_OUT)
		return (REDIR_OUT);
	if (tok_type == TOK_APPEND)
		return (REDIR_APPEND);
	return (HEREDOC);
}

static t_token	*append_redir(t_token *tok, t_cmd *cmd)
{
	t_redir	*redir;
	t_redir	*last;

	redir = ft_calloc(1, sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->type = redir_type_from_token(tok->type);
	redir->file = ft_strdup(tok->value);
	redir->next = NULL;
	if (!cmd->redirs)
		cmd->redirs = redir;
	else
	{
		last = cmd->redirs;
		while (last->next)
			last = last->next;
		last->next = redir;
	}
	return (tok->next);
}

static t_token	*skip_redir(t_token *tok, t_cmd *cmd, t_shell *shell)
{
	tok = tok->next;
	if (!tok || tok->type != TOK_WORD)
		return (parse_redir_error(shell), NULL);
	return (append_redir(tok, cmd));
}

static int	count_words_until_pipe(t_token *tok)
{
	int	n;

	n = 0;
	while (tok && tok->type != TOK_PIPE)
	{
		if (tok->type == TOK_WORD)
			n++;
		if (is_redir_token(tok->type) && tok->next)
			tok = tok->next;
		tok = tok->next;
	}
	return (n);
}

static int	fill_cmd(t_cmd *cmd, t_token **cur, t_shell *shell)
{
	t_token	*tok;
	int		i;

	tok = *cur;
	i = 0;
	while (tok && tok->type != TOK_PIPE)
	{
		if (is_redir_token(tok->type))
		{
			tok = skip_redir(tok, cmd, shell);
			if (!tok)
				return (1);
			continue ;
		}
		if (tok->type == TOK_WORD)
			cmd->av[i++] = ft_strdup(tok->value);
		tok = tok->next;
	}
	cmd->av[i] = NULL;
	if (tok && tok->type == TOK_PIPE)
		tok = tok->next;
	*cur = tok;
	return (0);
}

static t_cmd	*build_cmd(t_token **cur, t_shell *shell)
{
	t_cmd	*cmd;
	int		words;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	words = count_words_until_pipe(*cur);
	cmd->av = ft_calloc(words + 1, sizeof(char *));
	if (!cmd->av)
		return (free(cmd), NULL);
	if (fill_cmd(cmd, cur, shell) != 0)
		return (free_cmd(cmd), NULL); 
	return (cmd);
}

t_cmd	*parse_build_cmds(t_token *tokens, t_shell *shell)
{
	t_token	*cur;
	t_cmd	*head;
	t_cmd	*tail;
	t_cmd	*new;

	cur = tokens;
	head = NULL;
	tail = NULL;
	while (cur)
	{
		new = build_cmd(&cur, shell);
		if (!new)
			break ;
		if (!head)
			head = new;
		else
			tail->next = new;
		tail = new;
	}
	return (head);
}
