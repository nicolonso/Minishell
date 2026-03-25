/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcyril-a <qcyril-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 21:10:00 by qcyril-a          #+#    #+#             */
/*   Updated: 2026/03/13 21:41:03 by qcyril-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STR_H
# define STR_H

size_t	ft_strlen(char *s);
int		ft_strncmp(char *s1, const char *s2, int n);
int		ct_wds(char *str);
int		is_space(int c);

#endif
