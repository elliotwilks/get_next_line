#define _GNU_SOURCE
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#define BUFFER_SIZE 5

int	arg_check(int argc, char **argv)
{
	if (argc > 2)
		return (0);
	if (argc < 2)
		return (0);
	if (argv[1][0] == '\0')
		return (0);
	return (1);
}

void	*memmove(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*c_dest;
	char	*c_src;
	char	temp[n];

	c_dest = (char *)dest;
	c_src = (char *)src;
	i = 0;
	while (i < n)
	{
		temp[i] = c_src[i];
		i++;
	}
	i = 0;
	while (i < n)
	{
		c_dest[i] = temp[i];
		i++;
	}
	return (c_dest);
}

void	*memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*s_dest;
	char	*s_src;

	s_dest = (char *)dest;
	s_src= (char *)src;
	i = 0;
	while (i < n)
	{
		s_dest[i] = s_src[i];
		i++;
	}
	return (s_dest);
}

void	to_star(char *str, int len)
{
	int		i;

	i = 0;
	while (i < len)
	{
		str[i] = '*';
		i++;
	}
}

int	main(int argc, char **argv)
{
	char	*buff;
	char	*match;
	ssize_t	total;
	ssize_t r_count;
	char	t_buff[BUFFER_SIZE];

	if (arg_check(argc, argv) == 0)
		return (write(2, "Argument Error\n", 16), 1);

	total = 0;
	buff = malloc(1);
	if (buff == NULL)
		return (1);
	while ((r_count = read(0, t_buff, BUFFER_SIZE)) != 0)
	{
		buff = (char *)realloc(buff, total + r_count + 1);
		if (buff == NULL)
			return (perror("MALLOC"), 1);
		memmove(buff + total, t_buff, r_count);
		total += r_count;
	}
	buff[total] = '\0';
	match = buff;
	while ((match = memmem(buff, strlen(buff), argv[1], strlen(argv[1]))) != NULL)
	{
		to_star(match, strlen(argv[1]));
		match += strlen(argv[1]);
	}
	printf("%s", buff);
	return (0);
}
