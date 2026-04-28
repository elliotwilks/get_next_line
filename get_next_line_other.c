#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>

#define BUFFER_SIZE 42

/*
THINKING
Filling a buffer with words is easy. The hard thing
that needs to be achived is condinuing to read untill
a newline or the EOF is reached. Also getting each
read from the buffer and joining it to the end of
the 'line' string.

So lets break this down. First let me try to join
each buffer read to the line string.


FILE
"here is a file with some \n
 words that can be read fo\n
 r us to look at.EOF"

 buff "       " < empty memory

 buff "here is" < fill with read
 line ""

*/

/*
DESCRIPTION :
Measures the length of the given string str,
excluding the terminating \0 character.

@param str : string to be measured

RETURN VALUE :
The number of bytes in the string str.
*/
size_t	ft_strlen(const char *str)
{
	size_t	count;

	count = 0;
	while (str[count])
		count++;
	return (count);
}

/*
DESCRIPTION
Allocates memory (using malloc(3)) and returns a
new string, which is the result of concatenating
s1 and s2.

@param s1: The string at the start. (PREFIX)
@param s2: The string added to the end. (SUFFIX)

RETURN
The new string. NULL if the allocation fails.
*/
char	*ft_strjoin(char const *s1, char const *s2)
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

/*
DESCRIPTION
Description Write a function that returns a line read
from a file descriptor. External functs. read, malloc,
free. Repeated calls (using loop) to your get_next_line()
function should let you read the text file pointed to
by the file descriptor, one line at a time.

@parm fd: The file descriptor to read from

RETURN VALUE
Return the line that was read.
NULL: nothing to read or an error occurred
*/
char	*get_next_line(int fd)
{
	int			i;
	void		*buff;
	size_t		count;
	ssize_t		bytes;
	static int	val;
	char		*line;

	i = 0;
	count = 4;
	buff = malloc(4);
	if (buff == NULL)
		return (NULL);

	bytes = read(fd, buff, count);
	if (bytes == -1)
	{
		free(buff);
		return (perror("READ"), NULL);
	}

	while (i < 3)
	{
		bu
	}

	return (buff);
}

int	main(void)
{
	int		fd;
	char	*ret;

	fd = open("example.txt", O_RDWR | O_CREAT);
	if (fd == -1)
		return (perror("ERROR OPENING FILE"), 1);

	ret = get_next_line(fd);
	if (ret == NULL)
		return (0);

	write(1, ret, 4);
	free(ret);
	return (0);
}
