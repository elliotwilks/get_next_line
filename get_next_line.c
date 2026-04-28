/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elwilks <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 12:03:20 by elwilks           #+#    #+#             */
/*   Updated: 2025/12/02 15:10 b6 elwilks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_cut_line(char *s)
{
	char	*str;
	int		x;
	int		y;

	if (s == NULL)
		return (NULL);
	x = 0;
	y = 0;
	while (s[x] && s[x] != '\n')
		x++;
	if (s[x] == '\n')
		x++;
	str = malloc(sizeof(char) * (ft_strlen(s + x) + 1));
	if (str == NULL)
		return (NULL);
	while (s[x])
		str[y++] = s[x++];
	str[y] = '\0';
	free(s);
	return (str);
}

char	*ft_get_line(char *s)
{
	char	*line;
	int		x;
	int		y;

	if (s == NULL)
		return (NULL);
	x = 0;
	y = 0;
	while (s[x] && s[x] != '\n')
		x++;
	if (s[x] == '\n')
		x++;
	line = malloc(sizeof(char) * (x + 1));
	if (line == NULL)
		return (NULL);
	while (y < x)
	{
		line[y] = s[y];
		y++;
	}
	line[y] = '\0';
	return (line);
}

char	*ft_read_file(int fd, char *s)
{
	char	*buffer;
	int		bytes;

	buffer = ft_calloc(BUFFER_SIZE + 1, 1);
	if (buffer == NULL)
		return (NULL);

	bytes = 1;
	while (bytes > 0 && ft_detect_new_line(s) == 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(buffer);
			return (free_str(s));
		}
		else if (bytes > 0)
		{
			buffer[bytes] = '\0';
			s = ft_strjoin(s, buffer);
		}
	}
	free (buffer);
	if (bytes == 0 && s[0] == '\0')
		return (free_str(s));
	return (s);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (str == NULL)
		str = ft_calloc(1, 1);
	str = ft_read_file(fd, str);
	if (str == NULL)
		return (NULL);
	line = ft_get_line(str);
	if (line == NULL)
		return (NULL);
	str = ft_cut_line(str);
	if (str == NULL)
		return (NULL);
	return (line);
}

int	main(void)
{
	int		fd;
	int		x;
	char	*line;

	fd = open("./test.txt", O_RDONLY);
	while ((line = get_next_line(fd)) != NULL)
	{
		x = ft_strlen(line);
		printf("LINE:%d, %s", x, line);
		free (line);
	}
	x = ft_strlen(line);
	printf("%d\n", x);
	close(fd);
	return (0)
	;
}

