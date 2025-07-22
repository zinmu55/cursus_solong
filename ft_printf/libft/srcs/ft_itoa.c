/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skohtake <skohtake@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 13:02:27 by skohtake          #+#    #+#             */
/*   Updated: 2024/05/06 12:37:30 by skohtake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*sub_itoa(char *res, long long int lln, int digits)
{
	if (lln < 0)
	{
		res[0] = '-';
		lln = -lln;
	}
	res[digits--] = '\0';
	while (lln != 0)
	{
		res[digits] = (lln % 10) + '0';
		lln /= 10;
		digits--;
	}
	return (res);
}

char	*ft_itoa(int n)
{
	long long int	lln;
	int				digits;
	char			*res;

	if (n == 0)
		return (ft_strdup("0"));
	lln = (long long int)n;
	digits = 1;
	while (lln / 10 != 0)
	{
		digits++;
		lln /= 10;
	}
	lln = (long long int)n;
	if (lln < 0)
		digits++;
	res = (char *)malloc(sizeof(char) * digits + 1);
	if (res == NULL)
		return (NULL);
	res = sub_itoa(res, lln, digits);
	return (res);
}

// /* comment out required below */

// int	main(void)
// {
// 	int	input;

// 	input = 123;
// 	(void)printf("input	:%d\n", input);
// 	(void)printf("res	:%s\n", ft_itoa(input));
// 	return (0);
// }
