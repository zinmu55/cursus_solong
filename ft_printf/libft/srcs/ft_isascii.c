/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skohtake <skohtake@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 09:59:32 by skohtake          #+#    #+#             */
/*   Updated: 2024/05/06 12:37:20 by skohtake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}

// /*Comment out required below*/

// #include <stdio.h>
// #include <ctype.h>

// int	main(void)
// {
// 	char	target;

// 	target = 'a';
// 	printf("target:%c\n", target);
// 	printf("	actual	:%d\n", ft_isascii(target));
// 	printf("	ideal	:%d\n", isascii(target));
// 	target = '5';
// 	printf("target:%c\n", target);
// 	printf("	actual	:%d\n", ft_isascii(target));
// 	printf("	ideal	:%d\n", isascii(target));
// 	target = ' ';
// 	printf("target:%c\n", target);
// 	printf("	actual	:%d\n", ft_isascii(target));
// 	printf("	ideal	:%d\n", isascii(target));
// 	return (0);
// }
