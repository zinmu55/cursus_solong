/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skohtake <skohtake@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 09:37:50 by skohtake          #+#    #+#             */
/*   Updated: 2024/05/06 12:38:46 by skohtake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (*needle == '\0')
		return ((char *)haystack);
	if (len == 0)
		return (NULL);
	while (haystack[i] != '\0' && i < len)
	{
		if (haystack[i] == needle[j])
		{
			if (needle[j + 1] == '\0')
				return ((char *)haystack + i - j);
			j++;
		}
		else
		{
			i -= j;
			j -= j;
		}
		i++;
	}
	return (NULL);
}

// /*Comment out required below*/

// #include <stdio.h>
// #include <string.h>

// // int	main(void)
// // {
// // 	char	*haystack;
// // 	char	*needle;
// // 	size_t	len;

// // 	// haystack = "Hello World!";
// // 	haystack = NULL;
// // 	needle = "World";
// // 	// needle = "";
// // 	len = 0;
// // 	printf("Exp	:%s\n", strnstr(haystack, needle, len));
// // 	printf("Act	:%s\n", ft_strnstr(haystack, needle, len));
// // 	return (0);
// // }

// int	main(void)
// {
// 	char	haystack[30] = "aaabcabcd";
// 	char	needle[10] = "aabc";

// 	// haystack = "Hello World!";
// 	// haystack = NULL;
// 	// needle = "World";
// 	// needle = "";
// 	printf("Exp	:%s\n", strnstr(haystack, needle, -1));
// 	printf("Act	:%s\n", ft_strnstr(haystack, needle, -1));
// 	return (0);
// }
