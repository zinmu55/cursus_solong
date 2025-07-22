/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_print_func.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skohtake <skohtake@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 10:26:11 by skohtake          #+#    #+#             */
/*   Updated: 2024/05/26 12:22:56 by skohtake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*sub_uitoa(char *res, long long int lln, int digits)
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

char	*my_uitoa(unsigned int n)
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
	res = sub_uitoa(res, lln, digits);
	return (res);
}

int	my_print_uint(unsigned int ui)
{
	char	*str;
	int		res;

	str = my_uitoa(ui);
	if (str == NULL)
		return (0);
	res = write(1, str, ft_strlen(str));
	free(str);
	return (res);
}

int	my_print_int(int i)
{
	char	*str;
	int		res;

	str = ft_itoa(i);
	if (str == NULL)
		return (0);
	res = write(1, str, ft_strlen(str));
	free(str);
	return (res);
}

int	my_print_str(char *str)
{
	if (str == NULL)
		return (write(1, "(null)", 6));
	return (write(1, str, ft_strlen(str)));
}
