/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skohtake <skohtake@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 19:38:13 by skohtake          #+#    #+#             */
/*   Updated: 2025/08/09 14:49:51 by skohtake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./solong.h"

// void	my_print_map(char **mapdata) // you will comment out this function.
// {
// 	int	y;

// 	ft_printf(" --- Current Map State --- \n");
// 	y = 0;
// 	while (mapdata[y])
// 	{
// 		ft_printf("	%s\n", mapdata[y]);
// 		y++;
// 	}
// 	ft_printf(" ------------------------- \n");
// }

size_t	count_double_array_lines(char **double_array)
{
	size_t	line_num;

	line_num = 0;
	while (double_array && double_array[line_num])
	{
		line_num++;
	}
	return (line_num);
}

char	**ft_stradd(char **double_array, char *new_str)
{
	char	**res;
	size_t	i;
	size_t	line_num;

	line_num = count_double_array_lines(double_array);
	if (!new_str)
		return (double_array);
	res = (char **)malloc(sizeof(char *) * (line_num + 2));
	if (!res)
		return (NULL);
	i = 0;
	while (i < line_num)
	{
		res[i] = double_array[i];
		i++;
	}
	res[i++] = new_str;
	res[i] = NULL;
	free(double_array);
	return (res);
}

void	read_map_from_file(const char *file_path, t_game *game)
{
	int		fd;
	int		i;
	char	*tmp_line;

	(void)file_path;
	fd = open(file_path, O_RDONLY);
	if (fd == -1)
	{
		my_clean_error_exit(game, "The file does not exist.");
	}
	game->map.data = NULL;
	i = 0;
	while (1)
	{
		tmp_line = get_next_line(fd);
		game->map.data = ft_stradd(game->map.data, tmp_line);
		if (!tmp_line)
			break ;
		i++;
	}
	close(fd);
	game->map.width = ft_strlen(game->map.data[0]);	//	segv if map is null.
	game->map.height = i;
}

char	**copy_map_data(t_map *map)
{
	char	**copy_grid;
	int		i;

	copy_grid = (char **)malloc(sizeof(char *) * (map->height + 1));
	if (copy_grid)
		NULL;
	i = 0;
	while (i < map->height)
	{
		copy_grid[i] = ft_strdup(map->data[i]);
		if (!copy_grid[i])
		{
			free_double_ptr(copy_grid, i);
			return (NULL);
		}
		i++;
	}
	copy_grid[i] = NULL;
	return (copy_grid);
}
