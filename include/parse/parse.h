/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcyril-a <qcyril-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 20:33:21 by qcyril-a          #+#    #+#             */
/*   Updated: 2026/03/25 17:01:20 by quintondell      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <readline/readline.h>
# include <readline/history.h>

void	prompt_loop(void);
ssize_t	parse_input(char *str);

