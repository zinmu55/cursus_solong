/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skohtake <skohtake@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 12:25:21 by skohtake          #+#    #+#             */
/*   Updated: 2024/05/26 12:25:25 by skohtake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>

//	ft_printf.c
int		ft_printf(const char *input, ...);
int		my_count_res(char *format, va_list *list);
int		my_process_id(char id, va_list *list);
int		my_print_char(char c);

//	my_print_func.c
char	*sub_uitoa(char *res, long long int lln, int digits);
char	*my_uitoa(unsigned int n);
int		my_print_uint(unsigned int ui);
int		my_print_int(int i);
int		my_print_str(char *str);

//	my_print_hex.c
int		my_write_free(char **str);
char	*my_itohex_upper(int i, int sign, int hex_len);
int		my_print_hex_upper(int i);
char	*my_itohex_lower(int i, int sign, int hex_len);
int		my_print_hex_lower(int i);

//	my_print_ptr.c
char	*sub_ptrtohex(char *res, unsigned long long int ulln, int digits);
char	*my_ptrtohex(void *ptr);
int		my_print_ptr(void *ptr);

#endif