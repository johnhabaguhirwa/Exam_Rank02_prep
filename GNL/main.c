#include <stdio.h>
#include "gnl.h"

int	main(void)
{
	int		fd;
	int		count_line;
	char	*s;

	count_line = 23;
	fd = open("test.txt", O_RDONLY);
	while (count_line > 0)
	{
		s = get_next_line(fd);
		printf("%s", s);
		free(s);
		count_line--;
	}
	close(fd);
	return (0);
}