/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skohtake <skohtake@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 11:51:37 by skohtake          #+#    #+#             */
/*   Updated: 2024/05/10 07:39:22 by skohtake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*p;

	p = (unsigned char *)b;
	while (len--)
		*p++ = (unsigned char)c;
	return (b);
}

// /*Comment out required below*/

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	char	*input;
// 	char	*s1;
// 	char	*s2;

// 	input = "123456789 123456789 123456789 42Tokyo";
// 	s1 = strdup(input);
// 	s2 = strdup(input);
// 	printf("original input	:%s\n", input);
// 	ft_memset(s1, 'a', 5);
// 	printf("Actual		:%s\n", s1);
// 	memset(s2, 'a', 5);
// 	printf("Expected	:%s\n", s2);
// 	return (0);
// }
