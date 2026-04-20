/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_internal.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcyril-a <qcyril-a@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 13:25:55 by qcyril-a          #+#    #+#             */
/*   Updated: 2026/04/20 13:26:44 by qcyril-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_INTERNAL_H
# define PARSE_INTERNAL_H

/* ── expand utilities ────────────────────────────── */

int		ms_token_needs_split(t_token *tok);
int		ms_is_name_start(char c);
int		ms_is_name_char(char c);
int		ms_append_char(char **out, char c);
int		ms_append_str(char **out, char *add);
void	ms_update_quote_state(char c, int *state);

#endif
