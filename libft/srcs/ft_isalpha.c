/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skohtake <skohtake@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:35:15 by skohtake          #+#    #+#             */
/*   Updated: 2024/04/28 10:16:58 by skohtake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
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
// 	printf("	actual	:%d\n", ft_isalpha(target));
// 	printf("	ideal	:%d\n", isalpha(target));
// 	target = '5';
// 	printf("target:%c\n", target);
// 	printf("	actual	:%d\n", ft_isalpha(target));
// 	printf("	ideal	:%d\n", isalpha(target));
// 	target = ' ';
// 	printf("target:%c\n", target);
// 	printf("	actual	:%d\n", ft_isalpha(target));
// 	printf("	ideal	:%d\n", isalpha(target));
// 	return (0);
// }
