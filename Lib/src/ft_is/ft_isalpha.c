/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 20:36:35 by nalfonso          #+#    #+#             */
/*   Updated: 2025/08/12 19:02:49 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../hdr/libft.h"

int	ft_isalpha(int c)
{
	if (c < 'A' || (c > 'Z' && c < 'a') || c > 'z')
		return (0);
	return (1);
}
/*int main()
{
	printf("A: %d\n", ft_isalpha('A'));  // Expected: 1
	printf("M: %d\n", ft_isalpha('M'));  // Expected: 1
	printf("Z: %d\n", ft_isalpha('Z'));
	return (0);
}*/