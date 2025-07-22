/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skohtake <skohtake@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 12:11:20 by skohtake          #+#    #+#             */
/*   Updated: 2024/05/29 13:44:57 by skohtake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*sub_ptrtohex(char *res, unsigned long long int ulln, int digits)
{
	res[digits--] = '\0';
	while (ulln != 0)
	{
		if (ulln % 16 >= 10)
			res[digits] = 'a' + (ulln % 16) - 10;
		else
			res[digits] = '0' + (ulln % 16);
		ulln /= 16;
		digits--;
	}
	return (res);
}

char	*my_ptrtohex(void *ptr)
{
	unsigned long long int	ulln;
	int						digits;
	char					*res;

	ulln = (unsigned long long int)ptr;
	digits = 1;
	while (ulln / 16 != 0)
	{
		digits++;
		ulln /= 16;
	}
	ulln = (unsigned long long int)ptr;
	res = (char *)malloc(sizeof(char) * digits + 1);
	if (res == NULL)
		return (NULL);
	res = sub_ptrtohex(res, ulln, digits);
	return (res);
}

int	my_print_ptr(void *ptr)
{
	int		res;
	char	*str;

	res = 0;
	res += write(1, "0x", 2);
	if (ptr == NULL)
		res += write(1, "0", 1);
	else
	{
		str = my_ptrtohex(ptr);
		res += write(1, str, ft_strlen(str));
		free(str);
	}
	return (res);
}
