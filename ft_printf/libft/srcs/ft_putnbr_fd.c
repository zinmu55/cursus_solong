/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skohtake <skohtake@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:03:16 by skohtake          #+#    #+#             */
/*   Updated: 2024/05/10 07:39:53 by skohtake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long long int	lln;

	lln = (long long int)n;
	if (lln < 0)
	{
		ft_putchar_fd('-', fd);
		lln = -lln;
	}
	if (lln >= 10)
		ft_putnbr_fd(lln / 10, fd);
	ft_putchar_fd((lln % 10) + '0', fd);
}

// /* comment out required below */

// #include <limits.h>

// int	main(void)
// {
// 	int	input;

// 	input = INT_MAX;
// 	ft_putnbr_fd(input, 1);
// 	input = INT_MIN;
// 	ft_putnbr_fd(input, 1);
// }
