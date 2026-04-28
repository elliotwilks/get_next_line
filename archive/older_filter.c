#define _GNU_SOURCE
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>

void	ft_putstr(char *str)
{
	int	i = 0;

	while (str[i])
		write(1, &str[i++], 1);
}

int	arg_error(int argc)
{
	if (argc < 2)
		return (ft_putstr("Empty Arguments\n"), 1);
	if (argc > 2)
		return (ft_putstr("Too many arguments\n"), 1);
	return (0);
}

int	main(int argc, char **argv)
{
	ssize_t	ret;
	int		fd;
	char	*buffer;

	/* Check arugment count is correct */
	if (arg_error(argc) == 1)
		return (1);

	/* Set correct buffer size based on stdin*/
	buffer = malloc(strlen(stdin) + 1);
	if (buffer == NULL)
		perror("MALLOC");

	/* Read from standard input */
	ret = read(0, buffer, 3);
	if (ret < 0)
		perror("READ");

	/* Write to standard output */
	write(1, &buffer, 3);
	write(1, "\n", 1);

	return (0);
}
