/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 19:48:56 by nalfonso          #+#    #+#             */
/*   Updated: 2025/08/12 19:05:21 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../hdr/libft.h"

int	ft_atoi(const char *nptr)
{
	int	index;
	int	sign;
	int	result;

	sign = 1;
	index = 0;
	result = 0;
	while (nptr[index] == ' ' || nptr[index] == '\n' || nptr[index] == '\t'
		|| nptr[index] == '\r' || nptr[index] == '\v' || nptr[index] == '\f')
		index++;
	if (nptr[index] == '+' || nptr[index] == '-')
	{
		if (nptr[index] == '-')
			sign = -sign;
		index++;
	}
	while (nptr[index] >= '0' && nptr[index] <= '9')
	{
		result = (result * 10) + (nptr[index] - 48);
		index++;
	}
	return (result * sign);
}

/*int main()
{
	const char *str = "-42";
	int result = ft_atoi (str);
	
	printf ("%d\n", result);
	return (0);
}*/