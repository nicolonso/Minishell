/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcyril-a <qcyril-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 19:48:44 by nalfonso          #+#    #+#             */
/*   Updated: 2026/03/13 21:42:42 by qcyril-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		ft_strcmp(char *s1, const char *s2)
{
    size_t  i;

    if (!s1 || !s2)
        return (0);
    i = 0;
    while (s1[i] && s1[i] == s2[i])
        i++;
    return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	main(int ac, char **av)
{
	(void)ac;
	(void)av;
//	while (1)
//	{
		// Read Line
	prompt_loop();
		// Parse Line
		// Execute command 
//	}
	return (0);
}
