#include "get_next_line.h"

/*
I now finaly have a version that should pass the exam.
I need to now comment it throughly to show I understand
each part of it and then try to write it on my own as
though it was an exam. Also, when I test this program 
with the exam shell tester it seems to pass. I am guessing
the tests for the exam shell are less thourough so I 
dont need to perfect this code anymore. Just simply 
understand it and memorise it. 
*/

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	custom_print(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(str);
	while (i < len)
	{
		if (str[i] == '\n')
			printf("[\\n]");

		printf("%c", str[i]);
		i++;
	}
	printf("[\\0]\n");
}

char	*ft_strjoin(char *s1, char *s2, size_t s1_len)
{
	size_t		i;
	int			j;
	char		*buff;

	buff = malloc(s1_len + ft_strlen(s2) + 1);
	if (buff == NULL)
		return (NULL);

	i = 0;
	j = 0;
	while (i < s1_len)
	{
		buff[i] = s1[i];
		i++;
	}
	while (j < ft_strlen(s2))
	{
		buff[i] = s2[j];
		i++;
		j++;
	}
	buff[i] = '\0';
	return (buff);
}

char	*ft_strchr(char *str, char c)
{
	int	i;

	i = 0;

	if (str == NULL)
		return (NULL);

	while (str[i])
	{
		if (str[i] == c)
			return (str + i);
		i++;
	}
	return (NULL);
}

char	*ft_strdup(char *str)
{
	int		i;
	char	*buff;

	buff = malloc(ft_strlen(str) + 1);
	if (buff == NULL)
		return (NULL);

	i = 0;
	while (i < ft_strlen(str))
	{
		buff[i] = str[i];
		i++;
	}
	buff[i] = '\0';
	return (buff);
}

char	*ft_read_file(int fd, char *storage)
{
	int		bytes;
	char	*buffer;
	char	*tmp;
	size_t	storage_len;

	/*For first read, create memory in storage*/
	if (storage == NULL)
		storage = ft_strdup("");

	/*if theres a newline already in storage return*/
	if (ft_strchr(storage, '\n') != NULL)
		return (storage);

	/*Get length of storage, why?*/
	storage_len = ft_strlen(storage);

	/*Create memory for buffer. Buffer memory will change
	but for now, just use the BUFFER_SIZE*/
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);

	/*What the hell is storage + storage_len? So we are doing
	pointer arithmatic before parsing the string into ft_strchr?
	Is this to prevent TIMEOUTS? */
	while (ft_strchr(storage + storage_len, '\n') == NULL)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		/*-1 means error has occured*/
		if (bytes == -1)
			return (free(buffer), free(storage), NULL);
		/*0 mean file is empty or EOF*/
		if (bytes == 0)
			break ;
		/*Null terminate*/
		buffer[bytes] = '\0';
		/*why use this tmp variable?*/
		tmp = ft_strjoin(storage, buffer, storage_len);
		free(storage);
		storage = tmp;
		if (!storage)
			return (free(buffer), NULL);
		/* Why are we keepign the storage length?*/
		storage_len += bytes;
	}
	free(buffer);
	return (storage);
}
/*Return only one after the newline*/
char	*extract_line(char *str)
{
	int		i;
	int		len;
	char	*buff;

	/*Counting up till a newline is reached or to
	the end of the string*/
	len = 0;
	while (str[len] && str[len] != '\n')
		len++;
	/*if its a newline, increment one more time*/
	if (str[len] == '\n')
		len++;
	/*Create memory in buff*/
	buff = malloc(len + 1);
	if (buff == NULL)
		return (NULL);

	/*Copy everything across*/
	i = 0;
	while (i < len)
	{
		buff[i] = str[i];
		i++;
	}
	/*Null terminate and return */
	buff[i] = '\0';
	return (buff);
}

char	*update_storage(char *storage)
{
	int		i;
	int		j;
	int		len;
	char	*buff;

	i = 0;
	if (ft_strchr(storage, '\n') == NULL)
	{
		free(storage);
		return (NULL);
	}

	while (storage[i] && storage[i] != '\n')
		i++;

	if (storage[i] == '\n')
		i++;
	len = 0;
	while (storage[i + len])
		len++;
	buff = malloc(len + 1);
	if (buff == NULL)
		return (NULL);

	j = 0;
	while (storage[i])
	{
		buff[j] = storage[i];
		j++;
		i++;
	}
	buff[j] = '\0';

	free(storage);
	return (buff);
}

char	*get_next_line(int fd)
{
	/*Static variable lives in the gnl function*/
	static char	*storage;
	char		*line;

	/*First read the file & check for null*/
	storage = ft_read_file(fd, storage);
	if (storage == NULL)
		return (NULL);

	/*Which case is this important?*/
	if (storage[0] == '\0')
	{
		free(storage);
		storage = NULL;
		return (NULL);
	}
	/*Take only upto the new line then store in line*/
	line = extract_line(storage);
	if (line == NULL)
		return (NULL);

	/*Update storage each time*/
	storage = update_storage(storage);
	return (line);
}
/*
int	main(void)
{
	int		fd;
	char	*line;

	fd = open("file.txt", O_RDONLY);
	line = get_next_line(fd);
	while (line != NULL)
	{
		custom_print(line);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	return (0);
}

*/
