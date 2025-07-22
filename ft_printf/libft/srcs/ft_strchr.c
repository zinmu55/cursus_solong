/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skohtake <skohtake@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 10:49:20 by skohtake          #+#    #+#             */
/*   Updated: 2024/05/06 12:38:09 by skohtake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *s, int c)
{
	char	*res;
	char	target;

	res = (char *)s;
	target = (char)c;
	while (*res)
	{
		if (*res == target)
			return (res);
		res++;
	}
	if (target == '\0')
		return (res);
	return (0);
}

// /*Comment out required below*/

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	char	*s;
// 	int		c;

// 	s = "Hello, World!";
// 	// s = "";
// 	c = 'H';
// 	printf("Expected\n");
// 	printf("input <<< s:%s, c:%c\n", s, c);
// 	printf("result	:%s\n", strchr(s, c + 256));
// 	printf("Actual\n");
// 	printf("input <<< s:%s, c:%c\n", s, c);
// 	printf("result	:%s\n", ft_strchr(s, c + 256));
// 	return (0);
// }
