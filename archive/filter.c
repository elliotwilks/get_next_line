#define _GNU_SOURCE
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#define BUFFER_SIZE 10

/*
DESCRIPTION
Create a program which can take input from the standard
intput (usually via pipe '|') and replace the characters
that are specified in the argument.

EXAMPLE
Input = echo "coolprogram" | ./filter "oo"
Output = c**lprogram
*/

/*
DESCRIPTION
If program is called without arguments or with an
empty argument or with multiple arguments, it must
return 1.

@param argc: number of arguments given to the program
@param argv: content of the arguments

RETURN
Return 1 if arguments are ok, else return 0.
*/
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

/*
THINKING
Need to use strjoin and keep adding on the
new read to the buffer, I also need to add
new memory to the buffer memory each time.

Currently I am reading till read returns 0.
Reterning 0 indicates that the stdin is
empty, there is nothign else to read.

I will put all of the stdin into buff by
using t_buff (temporary buffer). Then I
can do some string manipulation inorder
to replace the argment characters to "*".
*/

int	main(int argc, char **argv)
{
	char	*buff;
	char	t_buff[BUFFER_SIZE];

	if (arg_check(argc, argv) == 0)
		return (write(2, "Argument Error\n", 16), 1);

	while (read(0, t_buff, BUFFER_SIZE) != 0)
	{
		buff =
	}
}


