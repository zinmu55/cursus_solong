/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skohtake <skohtake@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 09:59:17 by skohtake          #+#    #+#             */
/*   Updated: 2024/05/07 10:55:28 by skohtake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	if (*s == '\0')
		return (0);
	return (ft_strlen(++s) + 1);
}

// /*Comment out required below*/

// #include <stdint.h>
// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	char	*input;

// 	input = "42Tokyo";
// 	printf("input:%s\n", input);
// 	printf("	actual	>>>%zu\n", ft_strlen(input));
// 	printf("	ideal	>>>%zu\n", strlen(input));
// 	/////////////////////////////////////////////////
// 	printf("SIZEMAX = %zu\n", SIZE_MAX);
// 	return (0);
// }
