/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skohtake <skohtake@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 10:09:22 by skohtake          #+#    #+#             */
/*   Updated: 2024/05/10 07:42:08 by skohtake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c + 'A' - 'a');
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
// 	printf("After	>>>%c, %c, %c\n", toupper(c1), toupper(c2), toupper(c3));
// 	printf("Actual\n");
// 	printf("Before	>>>%c, %c, %c\n", c1, c2, c3);
// 	printf("After	>>>%c, %c, %c\n", ft_toupper(c1), ft_toupper(c2),
// 			ft_toupper(c3));
// }
