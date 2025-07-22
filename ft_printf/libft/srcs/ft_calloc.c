/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skohtake <skohtake@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 12:46:07 by skohtake          #+#    #+#             */
/*   Updated: 2024/05/07 12:58:46 by skohtake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	if (size && count > SIZE_MAX / size)
		return (NULL);
	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, count * size);
	return (ptr);
}

// /* Comment out required below */

// int	main(void)
// {
// 	char	*s;

// 	// s = calloc(5, sizeof(char));
// 	s = calloc(0, 0);
// 	// s = calloc((size_t)SIZE_MAX / 10 + (size_t)1, 10);
// 	if (s == NULL)
// 		printf("Failed\n");
// 	else
// 	{
// 		s = "1234";
// 		printf("%s >>> SUCCESS\n", s);
// 	}
// 	if (s)
// 		free(s);
// 	////////////////////////////////////////////////////////////
// 	// s = ft_calloc(5, sizeof(char));
// 	s = ft_calloc(0, 0);
// 	// s = ft_calloc((size_t)SIZE_MAX / 10 + (size_t)1, 10);
// 	if (s == NULL)
// 		printf("Failed\n");
// 	else
// 	{
// 		s = "1234";
// 		printf("%s >>> SUCCESS\n", s);
// 	}
// 	if (s)
// 		free(s);
// 	return (0);
// }
