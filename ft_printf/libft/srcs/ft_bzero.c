/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skohtake <skohtake@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 12:41:00 by skohtake          #+#    #+#             */
/*   Updated: 2024/05/10 07:42:49 by skohtake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	char	*target;

	target = (char *)s;
	while (n--)
	{
		*target = 0;
		target++;
	}
}

// /*Comment out required below*/

// #include <stdio.h>
// #include <string.h>
// #include <strings.h>

// int	main(void)
// {
// 	char	*input;
// 	char	*s1;
// 	char	*s2;

// 	input = "123456789 123456789 123456789 42Tokyo";
// 	s1 = strdup(input);
// 	s2 = strdup(input);
// 	printf("original input	:%s\n", input);
// 	ft_bzero(s1, sizeof(char)*5);
// 	printf("Actual		:%s\n", s1);
// 	bzero(s2, sizeof(char) * 5);
// 	printf("Expected	:%s\n", s2);
// 	return (0);
// }
