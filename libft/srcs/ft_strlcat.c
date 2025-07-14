/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skohtake <skohtake@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 07:40:27 by skohtake          #+#    #+#             */
/*   Updated: 2024/05/07 10:55:23 by skohtake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;

	dst_len = 0;
	src_len = 0;
	i = 0;
	while (src[src_len] != '\0')
		src_len++;
	if (dstsize == 0)
		return (src_len);
	while (dst[dst_len] != '\0')
		dst_len++;
	if (dst_len > dstsize)
		return (dstsize + src_len);
	while (src[i] != '\0' && dst_len + i < dstsize - 1)
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (dst_len + src_len);
}

// /*Comment out required below*/

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	// char	d1[20] = "Hello,world!";
// 	char	s1[20] = "Hello,42Tokyo!";
// 	size_t	dstsize1;
// 	size_t	r1;
// 	// char	d2[20] = "Hello,world!";
// 	char	s2[20] = "Hello,42Tokyo!";
// 	size_t	dstsize2;
// 	size_t	r2;

// 	dstsize1 = 0; //sizeof(d1);
// 	r1 = strlcat(NULL, s1, dstsize1);
// 	printf("Expected\n");
// 	// printf(">>>d1		:%s\n", d1);
// 	printf(">>>s1		:%s\n", s1);
// 	// printf(">>>dstsize1	:%zu\n", dstsize1);
// 	printf(">>>r1		:%zu\n", r1);
// 	printf("\n");
// 	dstsize2 = 0; // sizeof(d2);
// 	r2 = ft_strlcat(NULL, s2, dstsize2);
// 	printf("Actual\n");
// 	// printf(">>>d2		:%s\n", d2);
// 	printf(">>>s2		:%s\n", s2);
// 	// printf(">>>dstsize2	:%zu\n", dstsize2);
// 	printf(">>>r2		:%zu\n", r2);
// 	printf("\n");
// 	return (0);
// }
