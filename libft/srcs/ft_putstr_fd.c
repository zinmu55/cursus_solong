/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skohtake <skohtake@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 13:41:39 by skohtake          #+#    #+#             */
/*   Updated: 2024/05/06 12:38:04 by skohtake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (s == NULL)
		return ;
	write(fd, s, ft_strlen(s));
}

// /* comment out required below */

// int	main(void)
// {
// 	char	s[] = "Hello, world!";

// 	ft_putstr_fd(s, 1);
// }
