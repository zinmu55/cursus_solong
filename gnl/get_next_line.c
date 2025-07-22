/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skohtake <skohtake@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 12:34:22 by skohtake          #+#    #+#             */
/*   Updated: 2025/05/22 12:33:41 by skohtake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*my_save(char *save)
{
	int		i;
	int		j;
	char	*new_save;

	if (!save || !*save)
		return (NULL);
	i = 0;
	j = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if ((!save[i]))
		return (free(save), NULL);
	new_save = (char *)malloc(sizeof(char) * (my_strlen(save) - i + 1));
	if (!new_save)
		return (free(save), NULL);
	i++;
	while (save[i])
		new_save[j++] = save[i++];
	new_save[j] = '\0';
	free(save);
	return (new_save);
}

char	*my_get_line(char *save)
{
	char	*line;
	int		i;

	i = 0;
	if (!save)
		return (NULL);
	while (save[i] != '\n' && save[i])
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (save[i] && save[i] != '\n')
	{
		line[i] = save[i];
		i++;
	}
	if (save[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*my_read(int fd, char *save)
{
	char	*tmp;
	char	*new_save;
	int		readbyte;

	tmp = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (tmp == NULL)
		return (save);
	readbyte = 1;
	while (!my_strchr(save, '\n') && readbyte != 0)
	{
		readbyte = read(fd, tmp, BUFFER_SIZE);
		if (readbyte == -1)
		{
			free(tmp);
			return (save);
		}
		tmp[readbyte] = '\0';
		new_save = my_strjoin(save, tmp);
		save = new_save;
	}
	free(tmp);
	return (save);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*save[FOPEN_MAX];

	if (fd < 0 || fd >= FOPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	save[fd] = my_read(fd, save[fd]);
	if (save[fd] == NULL)
		return (NULL);
	if (*save[fd] == 0)
	{
		free(save[fd]);
		save[fd] = NULL;
		line = NULL;
		return (NULL);
	}
	line = my_get_line(save[fd]);
	save[fd] = my_save(save[fd]);
	if (save[fd] != NULL && *save[fd] == 0)
	{
		free(save[fd]);
		save[fd] = NULL;
	}
	return (line);
}

// // you must comment out below

// ////////////
// ////main////
// ////////////

// int	main(void)
// {
// 	int		fd;
// 	int		fd1;
// 	int		fd2;
// 	char	*line;

// 	fd1 = open("./tmp1.txt", O_RDONLY);
// 	fd2 = open("./tmp2.txt", O_RDONLY);
// 	line = "";
// 	while (line)
// 	{
// 		fd = fd1;
// 		line = get_next_line(fd);
// 		printf("	fd:%i>>>%s", fd, line);
// 	}
// 	printf("\n################################################\n");
// 	close(fd1);
// 	close(fd2);
// 	//////////////////////////////////////////////////
// 	fd1 = open("./tmp1.txt", O_RDONLY);
// 	fd2 = open("./tmp2.txt", O_RDONLY);
// 	line = "";
// 	while (line)
// 	{
// 		fd = fd2;
// 		line = get_next_line(fd);
// 		printf("	fd:%i>>>%s", fd, line);
// 	}
// 	printf("\n################################################\n");
// 	close(fd1);
// 	close(fd2);
// 	//////////////////////////////////////////////////
// 	fd1 = open("./tmp1.txt", O_RDONLY);
// 	fd2 = open("./tmp2.txt", O_RDONLY);
// 	line = "";
// 	while (line)
// 	{
// 		fd = fd1;
// 		line = get_next_line(fd);
// 		printf("	fd:%i>>>%s", fd, line);
// 		fd = fd2;
// 		line = get_next_line(fd);
// 		printf("	fd:%i>>>%s", fd, line);
// 	}
// 	printf("\n################################################\n");
// 	close(fd1);
// 	close(fd2);
// 	//////////////////////////////////////////////////
// 	return (0);
// }
