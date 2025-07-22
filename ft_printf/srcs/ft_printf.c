/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skohtake <skohtake@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 08:10:02 by skohtake          #+#    #+#             */
/*   Updated: 2024/05/26 12:22:49 by skohtake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	my_print_char(char c)
{
	return (write(1, &c, 1));
}

// decide process according identifier
int	my_process_id(char id, va_list *list)
{
	int	res;

	res = 0;
	if (id == 'c')
		res = my_print_char((char)va_arg(*list, int));
	if (id == 's')
		res = my_print_str((char *)va_arg(*list, char *));
	if (id == 'p')
		res = my_print_ptr((void *)va_arg(*list, void *));
	if (id == 'd')
		res = my_print_int((int)va_arg(*list, int));
	if (id == 'i')
		res = my_print_int((int)va_arg(*list, int));
	if (id == 'u')
		res = my_print_uint((unsigned int)va_arg(*list, unsigned int));
	if (id == 'x')
		res = my_print_hex_lower((int)va_arg(*list, int));
	if (id == 'X')
		res = my_print_hex_upper((int)va_arg(*list, int));
	if (id == '%')
		res = my_print_char('%');
	return (res);
}

int	my_count_res(char *format, va_list *list)
{
	int	res;
	int	index;

	res = 0;
	index = 0;
	while (format[index] != '\0')
	{
		if (format[index] == '%')
		{
			index++;
			res += my_process_id(format[index], list);
		}
		else if (format[index] != '\0')
		{
			res += write(1, format + index, 1);
		}
		index++;
	}
	return (res);
}

int	ft_printf(const char *format, ...)
{
	va_list	list;
	char	*dup;
	int		res_len;

	dup = ft_strdup(format);
	if (dup == NULL)
		return (0);
	va_start(list, format);
	res_len = my_count_res(dup, &list);
	va_end(list);
	free(dup);
	return (res_len);
}
