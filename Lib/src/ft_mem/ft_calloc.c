/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 19:49:38 by nalfonso          #+#    #+#             */
/*   Updated: 2025/08/12 19:03:27 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../hdr/libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	total_len;
	size_t	max_t;
	void	*ptr;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	max_t = nmemb * size;
	if (nmemb != (max_t / size))
		return (NULL);
	total_len = (nmemb * size);
	ptr = malloc(total_len);
	if (!ptr)
		return (NULL);
	ft_bzero (ptr, total_len);
	return (ptr);
}
// Overflow check:

// First we create a size_t variable that will store the value
// of the product of nmemb and size. If the product turns out good
// there won't be an overflow and when we divide it on the next line
// we get the expected result.
//
// Example: 
// Line 23: 5 * 10 = 50, max_t = 50
// Line 24: if ( 5 != (50 / 10) ), condition is FALSE! No overflow.
//
// On the other hand, if the product turns out bad
// there will be an overflow and when we divide it on the next line
// we DON'T get the expected result.
//
// Example: 
// Line 23: 5 * 10 = 7234, max_t = 7234
// Line 24: if ( 5 != (7234 / 10) ), condition is TRUE! Overflow! Return (NULL)
//
// But we have to check for underflow tooo! That's why we use != and not >=
//
// Example: 
// Line 23: 5 * 10 = 24, max_t = 24
// Line 24: if ( 5 != (24 / 10) ), condition is TRUE! Overflow! Return (NULL)
// Is zero check:
//
// In the manual, it says
// "If  nmemb  or  size  is  0, then calloc() returns either NULL, or a unique
// pointer value that can later be successfully passed to free()."
// This means that there are two possible options that calloc will 
//return in this case.
// This is UNDEFINED BEHAVIOUR of a function, because the manual is 
//not specific.
//
// What is malloc(0)
// "malloc(0) returns a pointer to 1 block of the memory with 0 bytes."
// We use malloc(0) because malloc(0) can represent NULL, or a pointer 
// that can be freed.
// We deal with both cases with a single return value.
//
/*#include <stdio.h>

int main()
{
	size_t members = 10;
	size_t n = 5;
	char *ptr;
	size_t i = 0;
	size_t total_size = n * members;
	
	if (!(ptr = ft_calloc(members, n)))
	{
		printf("Allocation failed\n");
		return (1);
	}
	while (i++ < total_size)
	{
		if (ptr[i] != 0)
		{
			printf ("Memory not zeroed at byte %zu\n", i);
			free(ptr);
			return (1);
		}	
	}
	printf("All memory successfully zeroed\n");
	free(ptr);
	return (0);
}*/