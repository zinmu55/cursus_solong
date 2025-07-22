/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skohtake <skohtake@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:23:06 by skohtake          #+#    #+#             */
/*   Updated: 2024/04/28 10:17:04 by skohtake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
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
// 	printf("	actual	:%d\n", ft_isdigit(target));
// 	printf("	ideal	:%d\n", isdigit(target));
// 	target = '5';
// 	printf("target:%c\n", target);
// 	printf("	actual	:%d\n", ft_isdigit(target));
// 	printf("	ideal	:%d\n", isdigit(target));
// 	target = ' ';
// 	printf("target:%c\n", target);
// 	printf("	actual	:%d\n", ft_isdigit(target));
// 	printf("	ideal	:%d\n", isdigit(target));
// 	return (0);
// }