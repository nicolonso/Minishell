/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 19:49:33 by nalfonso          #+#    #+#             */
/*   Updated: 2025/08/12 19:03:17 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../hdr/libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}
/*#include <stdio.h>

int main ()
{
	char str[11] = "YOLO LOLOLO";
	size_t n = 6;
	size_t i = 0;

	printf("Before ft_bezero %s\n" , str);
	ft_bzero(str, n);
	while (i++ < sizeof(str))
		printf("%d",str[i]);
	printf("\n");
	return (0);
}*/