/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skohtake <skohtake@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 11:35:11 by skohtake          #+#    #+#             */
/*   Updated: 2024/05/06 12:38:36 by skohtake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	index;
	char			*res;

	index = 0;
	if (s == NULL)
		return (NULL);
	res = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (res == NULL)
		return (NULL);
	while (s[index] != '\0')
	{
		res[index] = f(index, s[index]);
		index++;
	}
	res[index] = '\0';
	return (res);
}

// /* comment out required below */

// char	to_upper(unsigned int index, char c)
// {
// 	(void)index;
// 	if (c >= 'a' && c <= 'z')
// 		return (c - 32);
// 	return (c);
// }

// int	main(void)
// {
// 	char	*str;
// 	char	*result;

// 	str = "hello, world!";
// 	result = ft_strmapi(str, to_upper);
// 	if (result == NULL)
// 	{
// 		printf("Error: ft_strmapi failed\n");
// 		return (1);
// 	}
// 	printf("%s\n", result);
// 	free(result);
// 	return (0);
// }
