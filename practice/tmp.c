#include "./solong.h"

// you must comment out below

////////////
////main////
////////////

int	main(void)
{
	int		fd;
	int		fd1;
	int		fd2;
	char	*line;

	printf("\n################################################\n");
	//////////////////////////////////////////////////
	fd1 = open("./map/test.ber", O_RDONLY);
	fd = fd1;
	line = "";
	while (line)
	{
		line = get_next_line(fd);
		if (!line)
		{
			break;
		}
		ft_printf("	fd:%i>>>%s", fd, line);
	}
	close(fd1);
	printf("\n################################################\n");
	//////////////////////////////////////////////////
	// fd1 = open("./tmp1.txt", O_RDONLY);
	// line = "";
	// while (line)
	// {
	// 	fd = fd1;
	// 	line = get_next_line(fd);
	// 	printf("	fd:%i>>>%s", fd, line);
	// }
	// printf("\n################################################\n");
	// close(fd1);
	// //////////////////////////////////////////////////
	return (0);
}