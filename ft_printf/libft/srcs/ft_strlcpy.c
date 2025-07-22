/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skohtake <skohtake@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:47:27 by skohtake          #+#    #+#             */
/*   Updated: 2024/05/06 12:38:29 by skohtake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	char	*d;
	char	*s;
	size_t	len_s;

	d = (char *)dst;
	s = (char *)src;
	len_s = ft_strlen(s);
	if (dstsize)
	{
		while (dstsize-- > 1 && *s != '\0')
			*d++ = *s++;
		*d = '\0';
	}
	return (len_s);
}

/*Comment out required below*/

// #include <string.h>

// int	main(void)
// {
// 	char	*dst1;
// 	char	*src1;
// 	char	*dst2;
// 	char	*src2;
// 	size_t	dstsize1;
// 	size_t	dstsize2;

// 	dst1 = strdup("aaaaa");
// 	src1 = strdup("AAAAAAAAAA");
// 	dst2 = strdup("aaaaa");
// 	src2 = strdup("AAAAAAAAAA");
// 	// dstsize = sizeof(char) * 15;
// 	dstsize1 = 25;
// 	dstsize2 = dstsize1;
// 	printf("Expected	:%zu,	%s\n", strlcpy(dst1, src1, dstsize1), dst1);
// 	// printf("Actual		:%zu,	%s\n", ft_strlcpy(dst2, src2, dstsize2),
// 	// dst2);
// 	return (0);
// }
