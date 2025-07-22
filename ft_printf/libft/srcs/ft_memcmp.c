/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skohtake <skohtake@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 09:11:11 by skohtake          #+#    #+#             */
/*   Updated: 2024/05/07 10:54:54 by skohtake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*s1_p;
	unsigned char	*s2_p;
	size_t			i;

	s1_p = (unsigned char *)s1;
	s2_p = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (s1_p[i] != s2_p[i])
			return (s1_p[i] - s2_p[i]);
		i++;
	}
	return (0);
}

// /*Comment out required below*/

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	size_t	n;
// 	char	*s1;
// 	char	*s2;
// 	char	*s3;
// 	char	*s4;

// 	s1 = "Tokyo";
// 	s2 = "Tokio";
// 	s3 = "Tokyouuuu";
// 	s4 = strdup(s1);
// 	n = 10;
// 	printf("Exp	:Act\n");
// 	printf("%d	:%d\n", memcmp(s1, s2, n), ft_memcmp(s1, s2, n));
// 	n = 3;
// 	printf("%d	:%d\n", memcmp(s1, s2, n), ft_memcmp(s1, s2, n));
// 	n = 4;
// 	printf("%d	:%d\n", memcmp(s1, s2, n), ft_memcmp(s1, s2, n));
// 	n = 5;
// 	printf("%d	:%d\n", memcmp(s1, s2, n), ft_memcmp(s1, s2, n));
// 	n = 10;
// 	printf("%d	:%d\n", memcmp(s1, s3, n), ft_memcmp(s1, s3, n));
// 	printf("%d	:%d\n", memcmp(s1, s4, n), ft_memcmp(s1, s4, n));
// 	return (0);
// }
