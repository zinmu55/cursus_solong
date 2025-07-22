/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skohtake <skohtake@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:03:16 by skohtake          #+#    #+#             */
/*   Updated: 2024/05/07 10:55:02 by skohtake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*d;
	unsigned char	*s;

	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	if (src == NULL && dst == NULL)
		return (NULL);
	if (dst <= src)
	{
		while (len)
		{
			*d++ = *s++;
			len--;
		}
	}
	if (dst > src)
	{
		while (len)
		{
			*(d + len - 1) = *(s + len - 1);
			len--;
		}
	}
	return (dst);
}

// /*Comment out required below*/

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	char	src[40] = "1234567890123456789 123456789 42Tokyo";
// 	char	d1[40] = "abcdefghi abcdefghi abcdefghi";
// 	char	*d2;

// 	d2 = strdup(d1);
// 	memmove(d1, src, 5);
// 	printf("Expected	:%s\n", d1);
// 	ft_memmove(d2, src, 5);
// 	printf("Actual		:%s\n", d2);
// 	printf("\n");
// 	memmove(d1, d1 + 1, 15);
// 	printf("Expected	:%s\n", d1);
// 	ft_memmove(d2, d2 + 1, 15);
// 	printf("Actual		:%s\n", d2);
// 	printf("\n");
// 	memmove(d1 + 2, d1, 15);
// 	printf("Expected	:%s\n", d1);
// 	ft_memmove(d2 + 2, d2, 15);
// 	printf("Actual		:%s\n", d2);
// 	printf("\n");
// 	free(d2);
// 	return (0);
// }
