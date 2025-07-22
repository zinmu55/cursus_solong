/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skohtake <skohtake@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 12:09:20 by skohtake          #+#    #+#             */
/*   Updated: 2024/06/11 11:47:13 by skohtake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	my_write_free(char **str)
{
	int	res;

	if (*str == NULL)
		return (write(1, "(null)", 6));
	res = write(1, *str, ft_strlen(*str));
	free(*str);
	return (res);
}

char	*my_uitohex_upper(unsigned int ui, int hex_len)
{
	char	*res;

	res = (char *)ft_calloc(hex_len-- + 1, sizeof(char));
	if (res == NULL)
		return (NULL);
	while (hex_len >= 0)
	{
		if (ui % 16 < 10)
			res[hex_len--] = '0' + ui % 16;
		if (ui % 16 >= 10)
			res[hex_len--] = 'A' + ui % 16 - 10;
		ui /= 16;
	}
	return (res);
}

int	my_print_hex_upper(int i)
{
	long long int	tmp;
	int				hex_len;
	char			*str;

	hex_len = 0;
	tmp = (unsigned int)i;
	if (i == 0)
		return (write(1, "0", 1));
	while (tmp > 0)
	{
		tmp /= 16;
		hex_len++;
	}
	str = my_uitohex_upper((unsigned int)i, hex_len);
	if (str == NULL)
		return (write(1, "(null)", 6));
	tmp = write(1, str, hex_len);
	free(str);
	return (tmp);
}

char	*my_uitohex_lower(unsigned int ui, int hex_len)
{
	char	*res;

	res = (char *)ft_calloc(hex_len-- + 1, sizeof(char));
	if (res == NULL)
		return (NULL);
	while (hex_len >= 0)
	{
		if (ui % 16 < 10)
			res[hex_len--] = '0' + ui % 16;
		if (ui % 16 >= 10)
			res[hex_len--] = 'a' + ui % 16 - 10;
		ui /= 16;
	}
	return (res);
}

int	my_print_hex_lower(int i)
{
	long long int	tmp;
	int				hex_len;
	char			*str;

	hex_len = 0;
	tmp = (unsigned int)i;
	if (i == 0)
		return (write(1, "0", 1));
	while (tmp > 0)
	{
		tmp /= 16;
		hex_len++;
	}
	str = my_uitohex_lower((unsigned int)i, hex_len);
	if (str == NULL)
		return (write(1, "(null)", 6));
	tmp = write(1, str, hex_len);
	free(str);
	return (tmp);
}
