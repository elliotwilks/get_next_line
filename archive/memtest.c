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
	void	*ret;
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
		total = total + r_count;
	}
	buff[total] = '\0';
	match = buff;
	while ((match = memmem(buff, strlen(buff), argv[1], strlen(argv[1]))) != NULL)
	{
		to_star(match, strlen(argv[1]));
		match = match + strlen(argv[1]);
	}
	printf("%s", buff);
	return (0);
}

/*
Thinking
I basicly need to move the bytes that have been read from the buffer
size and move them to the large buffer, I also need to reallocate the
memory each time so it is big enough to take the new bytes.
*/

/*
1. Read bytes into temporary buffer
2. Create new memory in buffer based on the size of the amount of bytes
read from read.
3. copy over from temporary buffer to main buffer.

The realloc() function in C is used to change the size of a previously
dynamically allocated memory block. It can be used to either increase
or decrease the size of the memory, and it preserves the existing data
within the block.

@param ptr: A pointer to the memory block previously allocated by
malloc(), calloc(), or realloc(). If it is NULL, realloc() behaves
like malloc().

@param size: The new size for the memory block, in bytes.

void	*realloc(void *ptr, size_t size);

Return Value

Success: On success, realloc() returns a pointer to the new memory block
(which may or may not be the same address as the original). The original
pointer becomes invalid. The contents of the old block are preserved up
to the lesser of the new and old sizes, and any newly allocated memory
is uninitialized.

Failure: On failure to allocate the requested space, realloc() returns a
NULL pointer. Crucially, the original memory block remains valid and
unchanged, so it must still be freed to avoid a memory leak.
Zero Size: If size is zero and ptr is not NULL, the behavior is
implementation-defined, but it generally deallocates the memory block as
if free() were called. It is best practice to use free() for deallocation.


memove()

@param dest:	A pointer to the destination memory area where the content
				will be copied to.
@param src:		A pointer to the source memory area to be copied from. The
				data in the source is treated as an array of unsigned char.
@param n: 		The number of bytes to be copied.

Requirements

- Take only one argument
- Read from stdin and write to stdout
- Replace argument string with '*'

- Example
	- ./filter "cool". Replace with '*'
	- echo "cool program" | ./filter "cool"
	- Result: "**** program"

THINKING
I have the string now in buff. Now I need to search for the substring
once I have found it I need to replace each character with the argv[1][0]
value. Turns out its better to use the function memmem.




DESCRIPTION
This function finds the start of the first occurrence of the
substring needle of length needlelen in the memory area haystack of
length haystacklen. memmem - locate a substring

RETURN VALUE
Returns a pointer to the beginning of the substring, or NULL if the
substring is not found.

@param haystack:		Main string
@param haystacklen:		Length of main string
@param needle:			Substring, string that we want to find
@param needlelen:		Length of substring

void	*memmem(const void *haystack, size_t haystacklen, const void *needle, size_t needlelen);

*/
