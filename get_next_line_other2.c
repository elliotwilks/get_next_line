#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

/*
THINKING
Lets figure out now, how can I make sure I get everything
till the end of the line in buff instead of just a certain
amount of bytes. Need to also use a static variable.

I need read a chuck to a temporary memory and then keep
adding it to the more perminant memory.

How can I do this?
*/

int		ft_strlen(char *str)
{
	int	i = 0;
	while(str[i])
		i++;
	return(i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	int		len;
	char	*buff;

	if (s1 == NULL)
		len = ft_strlen(s2);
	else
		len = ft_strlen(s1) + ft_strlen(s2);

	buff = malloc (len + 1);
	if (buff == NULL)
		return (NULL);

	i = 0;
	if (s1 != NULL)
	{
		while (s1[i])
		{
			buff[i] = s1[i];
			i++;
		}
	}
	j = 0;
	while (s2[j])
	{
		buff[i] = s2[j];
		i++;
		j++;
	}
	buff[i] = '\0';
	return (buff);
}

int		newline_check(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

void	read_file(int fd)
{
	int			i;
	char		*t_buff;
	char		*buff;
	ssize_t		bytes;
	ssize_t		count;

	t_buff = malloc(10);
	buff = NULL;
	count = 0;
	while ((bytes = read(fd, t_buff, 4)) > 0)
	{
		if (newline_check(t_buff) == 1)
		{
			printf("end of the line\n");
			exit(1) ;
		}
		else
		{
		// t_buff is filled with 4 bytes
		printf("%zd\n", bytes);
		// bytes is added to the count, first round is 4 but then grows each time
		count = count + bytes;
		// buff memory is created based on size of count
		buff = realloc(buff, count);
		// bytes are sent from temporary buff to buff
		buff = ft_strjoin(buff, t_buff);
		// buff is null terminated
		buff[strlen(buff)] = '\0';
		// print out buff
		printf("%s\n", buff);
		}
	}
	free(buff);
}

int		main(void)
{
	int		fd;

	fd = open("file.txt", O_RDONLY);
	read_file(fd);
	close(fd);

	return (0);
}
