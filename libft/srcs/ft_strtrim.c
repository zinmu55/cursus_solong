/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skohtake <skohtake@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 07:52:59 by skohtake          #+#    #+#             */
/*   Updated: 2024/05/06 12:38:55 by skohtake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_set(char const c, char const *set)
{
	if (c == '\0')
		return (1);
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*res;
	size_t	start;
	size_t	end;

	if (s1 == NULL)
		return (NULL);
	if (set == NULL)
		return (ft_strdup(s1));
	start = 0;
	end = ft_strlen(s1);
	while (is_set(s1[end], set) && end > 0)
		end--;
	while (is_set(s1[start], set) && start < end)
		start++;
	if (end == 0)
		return (ft_strdup(""));
	res = (char *)malloc(sizeof(char) * (end - start + 2));
	if (res == NULL)
		return (NULL);
	(void)ft_strlcpy(res, s1 + start, end - start + 2);
	return (res);
}

// /* commen out required below */

// #include <string.h>

// int	main(void)
// {
// 	// char	*s1;
// 	// char	*set;
// 	// s1 = strdup("+-+Hello+-+");
// 	// set = strdup("-+");
// 	// printf("res	:%s\n", ft_strtrim(s1, set));
// 	// free(s1);
// 	// free(set);
// 	// s1 = strdup("   \t  \n\n \t\t  \n\n\nHello \t  Please\n Trim me !");
// 	// set = strdup(" \n\t");
// 	// printf("res	:%s\n", ft_strtrim(s1, set));
// 	// free(s1);
// 	// free(set);
// 	// s1 = strdup("     ");
// 	// set = strdup(" ");
// 	// printf("res	:%s\n", ft_strtrim(s1, set));
// 	// free(s1);
// 	// free(set);
// 	printf("res	:%s\n", ft_strtrim("abcdba", "acb"));
// 	return (0);
// }
