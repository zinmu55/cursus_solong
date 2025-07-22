/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skohtake <skohtake@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 11:47:52 by skohtake          #+#    #+#             */
/*   Updated: 2024/05/07 14:34:20 by skohtake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char const c)
{
	int	res;
	int	i;
	int	flag;

	res = 0;
	i = 0;
	flag = 1;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			if (flag == 1)
				res++;
			flag = 0;
		}
		if (s[i] == c)
			flag = 1;
		i++;
	}
	return (res);
}

static int	wordlen(char const *s, char c)
{
	int	res;

	res = 0;
	while (s[res] != c && s[res] != '\0')
		res++;
	return (res);
}

static void	memfree(char ***ptr, int index)
{
	while (index >= 0)
	{
		free((*ptr)[index]);
		index--;
	}
	free(*ptr);
	*ptr = NULL;
}

static void	skip_c(char const **s, char c)
{
	while (**s == '\0' || **s == c)
		(*s)++;
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		cw;
	int		i;

	if (s == NULL)
		return (NULL);
	cw = count_words(s, c);
	i = 0;
	res = (char **)malloc(sizeof(char *) * (cw + 1));
	if (res == NULL)
		return (NULL);
	while (i < cw)
	{
		skip_c(&s, c);
		res[i] = (char *)malloc(sizeof(char) * (wordlen(s, c) + 1));
		if (res[i] == NULL)
		{
			memfree(&res, i);
			return (NULL);
		}
		(void)ft_strlcpy(res[i++], s, wordlen(s, c) + 1);
		s += wordlen(s, c);
	}
	res[i] = NULL;
	return (res);
}

// /* comment out required below */

// int	main(void)
// {
// 	char	*str;
// 	char	c;
// 	int		i;
// 	char	**result;

// 	str = "42Tokyo is my favorite place";
// 	c = ' ';
// 	// c = "\0";
// 	i = 0;
// 	printf("count words	:%d\n", count_words(str, c));
// 	result = ft_split(str, c);
// 	while (result[i])
// 	{
// 		printf("split[%d] output	;%s\n", i, result[i]);
// 		i++;
// 	}
// 	printf("split[%d] output	;%s\n", i, result[i]);
// 	while (result[i])
// 		free(result[i++]);
// 	free(result);
// 	return (0);
// }

// int	main(void)
// {
// 	int		i;
// 	char	**result;

// 	// 	char	*str;
// 	// 	char	c;
// 	// str = "^^^1^^2a,^^^^3^^^^--h^^^^";
// 	// c = '^';
// 	// c = "\0";
// 	i = 0;
// 	// printf("count words	:%d\n", count_words(str, c));
// 	result = ft_split("^^^1^^2a,^^^^3^^^^--h^^^^", '^');
// 	while (result[i])
// 	{
// 		printf("split[%d] output	;%s\n", i, result[i]);
// 		i++;
// 	}
// 	printf("split[%d] output	;%s\n", i, result[i]);
// 	while (result[i])
// 		free(result[i++]);
// 	free(result);
// 	return (0);
// }
