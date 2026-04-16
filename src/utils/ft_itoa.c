#include "libft.h"

size_t	ft_nlen(int n)
{
	size_t	len;

	len = 0;
	if (n <= 0)
	{
		len++;
//		n *= -1;
	}
	while (n)
	{
		n /= 10;
		len++;
		
	}
	return len;
}

char	*ft_itoa(int n)
{
	char	*p;
	size_t	len;
	
	if (!n)
		return ft_strdup("0");
	if (n == -2147483648)
	{
		p = NULL;
		p = ft_calloc(12, 1);
		if (!p)
			return (NULL);
		ft_memmove(p, "-2147483648", 11);
		return	p;
	}
//		return ft_strdup("-2147483648");
	p = NULL;
	len = ft_nlen(n);
	p = malloc(len + 1);
	if (!p)
		return NULL;
	p[len] = 0;
	if (n < 0)
	{	
		p[0] = '-';
		n *= -1;
	}
	while (n)
	{
		p[--len] = n % 10 + 48;
		n /= 10;	
	}
	return p;
}
