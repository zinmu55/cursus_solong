/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skohtake <skohtake@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 12:39:30 by skohtake          #+#    #+#             */
/*   Updated: 2025/05/22 13:00:47 by skohtake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

//	define BUFFER_SIZE

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# if BUFFER_SIZE < 42 && BUFFER_SIZE > 0
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# if BUFFER_SIZE > 2000
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 2000
# endif

//	get_next_line.c

char	*my_save(char *save);
char	*my_get_line(char *save);
char	*my_read(int fd, char *save);
char	*get_next_line(int fd);

// get_next_line_utils.c

size_t	my_strlen(const char *s);
char	*my_strchr(const char *s, int c);
char	*my_initialize(char *s1);
char	*my_strjoin(char *s1, char *s2);

#endif
