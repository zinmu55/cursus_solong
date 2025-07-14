/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skohtake <skohtake@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 07:47:28 by skohtake          #+#    #+#             */
/*   Updated: 2024/05/07 12:44:51 by skohtake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if (i >= n)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

// /*Comment out required below*/

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	char	*s1;

// 	// char	*s2;
// 	// char	*s3;
// 	s1 = "Hello,world!";
// 	// s2 = "Hello,42Tokyo!";
// 	// s3 = "Hello,world!!!";
// 	printf("Expected:Actual\n");
// 	printf("%d	:", strncmp(s1, NULL, 0));
// 	printf("%d\n", ft_strncmp(s1, NULL, 0));
// 	// printf("%d	:%d\n", strncmp(s1, s2, 5), ft_strncmp(s1, s2, 5));
// 	// printf("%d	:%d\n", strncmp(s1, s2, 6), ft_strncmp(s1, s2, 6));
// 	// printf("%d	:%d\n", strncmp(s1, s2, 7), ft_strncmp(s1, s2, 7));
// 	// printf("%d	:%d\n", strncmp(s1, s2, 100), ft_strncmp(s1, s2, 100));
// 	// printf("%d	:%d\n", strncmp(s1, s3, 100), ft_strncmp(s1, s3, 100));
// 	return (0);
// }
