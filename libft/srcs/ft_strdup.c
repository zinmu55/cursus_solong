/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skohtake <skohtake@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 13:59:05 by skohtake          #+#    #+#             */
/*   Updated: 2024/05/06 12:38:12 by skohtake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*s2;

	s2 = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (s2 == NULL)
		return (NULL);
	ft_strlcpy(s2, s1, ft_strlen(s1) + 1);
	return (s2);
}

// /* Comment out required below */

// #include <string.h>

// int	main(void)
// {
// 	char	*s1;
// 	char	*s2;

// 	s1 = strdup("abc");
// 	s2 = ft_strdup("abc");
// 	printf("Exp	:%s\n", s1);
// 	printf("Act	:%s\n", s2);
// 	return (0);
// }
