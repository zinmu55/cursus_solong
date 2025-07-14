/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skohtake <skohtake@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 08:10:54 by skohtake          #+#    #+#             */
/*   Updated: 2024/05/07 10:54:51 by skohtake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	ch;

	str = (unsigned char *)s;
	ch = (unsigned char)c;
	while (n--)
	{
		if (*str == ch)
			return ((void *)str);
		str++;
	}
	return (NULL);
}

// /*Comment out required below*/

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	unsigned char	*s1;
// 	int				c1;
// 	size_t			n1;

// 	s1 = (unsigned char *)"Hello, 42Tokyo!";
// 	c1 = '4';
// 	n1 = 10;
// 	printf("Expected	:%s\n", (unsigned char *)memchr(s1, c1, n1));
// 	printf("Actual		:%s\n", (unsigned char *)ft_memchr(s1, c1, n1));
// 	printf("\n");
// 	printf("Expected	:%s\n", (unsigned char *)memchr(s1, c1, 5));
// 	printf("Expected	:%s\n", (unsigned char *)ft_memchr(s1, c1, 5));
// 	printf("\n");
// 	return (0);
// }

// int	main(void)
// {
// 	char	*s1;
// 	int		c1;
// 	size_t	n1;

// 	s1 = "Hello, 42Tokyo!";
// 	c1 = '4';
// 	n1 = 10;
// 	printf("Expected	:%s\n", memchr(s1, c1, n1));
// 	printf("Expected	:%s\n", memchr(s1, c1, 5));
// 	return (0);
// }
