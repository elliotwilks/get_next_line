Helper functions

--- Input and output
read	- reads from stdin 					- USED
write	- write to stdin stdout or stderr	- USED
stdout	- Standard output					- USED
stderr	- Standard error					- USED

--- String Functions
strlen	- length of string
memmem	- locate a substring

--- Memory Functions
memmove	- copy memory n bytes from src to dest
malloc	- creates memory
calloc	- memory with zeros
realloc - adds on extra memory
free	- frees memomry usd in the

printf	- prints
fprintf - prints to file descriptor
perror	- sends message to stderr based on the errno.

--- Requirements

	- Take only one argument
	- Read from stdin and write to stdout
	- Replace argument string with '*'
	- Example
		- ./filter "cool". Replace with '*'
		- echo "cool program" | ./filter "cool"
		- Result: "**** program"

--- Learning

	This program has two inputs
	1. The argument >> what to replace
	2. Standard Input >> the string to do the replaceing in

	Currently I am using a buffer[10] and filling the buffer
	with the standard input using read(0, buffer, 3).
	However this is fixed and wont work for different lengths
	of input. How can I fix this?

Error message
	read  - Write "Error:" + show an error message using stderr + return 1.
	malloc - Write "Error: " + show an error message using stderr + return 1.

Other
	No arguments = return 1.
	empty argument = return 1.
	too many arguments = return 1.

Read Function

@param fildes:	file descriptor, stdin can be used
@param buf:		location bytes wil be put into
@param nbyte:	number of

ssize_t	read(int fildes, void *buf, size_t nbyte)
{

}

Get next line

memmove
memcpy
