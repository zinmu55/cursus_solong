/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skohtake <skohtake@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 10:36:04 by skohtake          #+#    #+#             */
/*   Updated: 2024/05/06 12:39:04 by skohtake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 'a' - 'A');
	else
		return (c);
}

// /*Comment out required below*/

// #include <ctype.h>
// #include <stdio.h>

// int	main(void)
// {
// 	int	c1;
// 	int	c2;
// 	int	c3;

// 	c1 = 'a';
// 	c2 = 'B';
// 	c3 = '5';
// 	printf("Expected\n");
// 	printf("Before	>>>%c, %c, %c\n", c1, c2, c3);
// 	printf("After	>>>%c, %c, %c\n", tolower(c1), tolower(c2), tolower(c3));
// 	printf("Actual\n");
// 	printf("Before	>>>%c, %c, %c\n", c1, c2, c3);
// 	printf("After	>>>%c, %c, %c\n", ft_tolower(c1), ft_tolower(c2),
// 			ft_tolower(c3));
// 	return (0);
// }
