/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skohtake <skohtake@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 13:23:20 by skohtake          #+#    #+#             */
/*   Updated: 2024/05/07 10:54:58 by skohtake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*res;
	char	*input;

	res = (char *)dst;
	input = (char *)src;
	if (src == NULL && dst == NULL)
		return (NULL);
	while (n--)
	{
		*res++ = *input++;
	}
	return (dst);
}

// /*Comment out required below*/

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	char	*d1;
// 	char	*d2;
// 	char	*src;

// 	// d1 = strdup("abcdefghi abcdefghi abcdefghi");
// 	// d2 = strdup(d1);
// 	// src = strdup("1234567890123456789 123456789 42Tokyo");
// 	// printf("Exp	:%s	,%s\n", memcpy(d1, src, 15), d1);
// 	// printf("Act	:%s	,%s\n", ft_memcpy(d2, src, 15), d2);
// 	// printf("\n");
// 	// free(d1);
// 	// free(d2);
// 	// free(src);
// 	////////////////////////////////////////////////////////////////////////
// 	// d1 = NULL;
// 	// d2 = NULL;
// 	// src = strdup("test");
// 	// printf("Exp	:%s	,%s\n", memcpy(d1, src, 15), d1);
// 	// printf("Act	:%s	,%s\n", ft_memcpy(d2, src, 15), d2);
// 	// printf("\n");
// 	// free(d1);
// 	// free(d2);
// 	// free(src);
// 	////////////////////////////////////////////////////////////////////////
// 	d1 = strdup("test1");
// 	d2 = strdup(d1);
// 	src = NULL;
// 	printf("Exp	:%s	,%s\n", memcpy(d1, src, 15), d1);
// 	// printf("Act	:%s	,%s\n", ft_memcpy(d2, src, 15), d2);
// 	printf("\n");
// 	free(d1);
// 	free(d2);
// 	free(src);
// 	////////////////////////////////////////////////////////////////////////
// 	// d1 = NULL;
// 	// d2 = NULL;
// 	// src = NULL;
// 	// printf("Exp	:%s	,%s\n", memcpy(d1, src, 15), d1);
// 	// printf("Act	:%s	,%s\n", ft_memcpy(d2, src, 15), d2);
// 	// printf("\n");
// 	// free(d1);
// 	// free(d2);
// 	// free(src);
// 	////////////////////////////////////////////////////////////////////////
// 	return (0);
// }
