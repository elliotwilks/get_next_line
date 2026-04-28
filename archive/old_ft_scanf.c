#include <stdarg.h>
#include <stdio.h>
#include <ctype.h> // isdigit isspace etc
#include <unistd.h>

/*
 *
 * The <stdarg.h> library provides:
 * va_list:		Declares a special variable to hold the argument list
 * va_start(ap, last)	Initialises it — last is the last named parameter
 * va_arg(ap, type)	Pulls the next argument out, cast to type
 * va_end(ap)		Cleans up
 *
 * I want to simply try and put a value from the keyboard
 * into a variable. Not worrying about format or data type.
 *
 * A variadic function needs and ellipsis: ... in the function
 * parameters. Variadic means the number of arguments can be
 * increased or decreased for this function.
 */

int	test(FILE *file)
{
	int	c;
	int	space;

	if (file == NULL)
	{
		printf("Error: Could not open file\n");
		return (1);
	}
	space = 0;
	while ((c = fgetc(file)) != EOF)
	{
		printf("%c", c);
		if (c == ' ')
			space++;

		if (space == 8)
		{
			usleep (200000);
			printf("\n");
			space = 0;
		}
	}

	// feof <-- not zero = success
	//ferror <-- not zero = fail
	/* ferror and feof are checked afer the loop*/
	if (ferror(file) != 0)
	{
		printf("Error: Coudn't read for some reason\n");
		fclose(file);
		return (1);
	}
	if (feof(file) != 0 && ferror(file) == 0)
	{
		printf("\nSucess: End of file reached \n");
		printf("Sucess: File Read\n");
		return (0);
	}


	return (0);
}

int ft_scanf(const char *type, ... )
{
	char		*str;
	const char	*format;

	/* Initialise list*/
	va_list	args;
	va_start(args, type);

	/* Set variables */
	str = va_arg(args, char *);
	format = type;

	/* Print out*/
	printf("%s\n", str);
	printf("%s\n", format);

	if (*format != '%')
	{
		printf("Incorrect format\n");
		return (0);
	}
	if (*format == '%')
		format++;

	if (*format == 's')
		printf("This is string \n");
	if (*format == 'd')
		printf("This is int \n");


	va_end(args);
	return (1);
}

int	scanner(const char *type, ... )
{
	int	*dest;
	const char	*val_type;
	va_list		list;

	va_start(list, type);

	val_type = type; // = %d
	dest = va_arg(list, int *); // = address of variable

	// Send to the variable
	*dest = fgetc(stdin) - '0';

	va_end(list);

	return (0);
}

int	main(void)
{
	int x;
	FILE	*file;

	x = 4;
	printf("Old x value: %d \n", x);
	file = fopen("file.txt", "r");
	scanner("%d", &x);
	printf("New x value: %d \n", x);

	return (0);
}

/*
Helper Functions:

Stream accessors
	fgetc *
	ungetc *

	fgetc
	Returns the character read as an unsigned char cast
	to an int. If the end-of-file is reached or an
	error occurs, it returns EOF.


EOF and error
	ferror <-- returns non-zero if EOF is success
	feof <-- returns non-zero if error occured

Input analyser
	isspace
	isdigit

Keyboard input
	stdin *

Variadic Macros
	va_start *
	va_arg *
	va_copy *
	va_end *


Manage input
	s - string
	d - integer
	c - character

*/

/*
int match_space(FILE *f)
{
        // You may insert code here
    return (0);
}

int match_char(FILE *f, char c)
{
        // You may insert code here
    return (0);
}

int	match_conv(FILE *f, const char **format, va_list ap)
{
	switch (**format)
	{
		case 'c':
			return scan_char(f, ap);
		case 'd':
			match_space(f);
			return scan_int(f, ap);
		case 's':
			match_space(f);
			return scan_string(f, ap);
		case EOF:
			return -1;
		default:
			return -1;
	}
}


int scan_char(FILE *f, va_list ap)
{
        // You may insert code here
    return (0);
}

int scan_int(FILE *f, va_list ap)
{
        // You may insert code here
    return (0);
}

int scan_string(FILE *f, va_list ap)
{
        // You may insert code here
    return (0);
}


int ft_vfscanf(FILE *f, const char *format, va_list ap)
{
	int nconv = 0;

	int c = fgetc(f);
	if (c == EOF)
		return EOF;
	ungetc(c, f);

	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (match_conv(f, &format, ap) != 1)
				break;
			else
				nconv++;
		}
		else if (isspace(*format))
		{
			if (match_space(f) == -1)
				break;
		}
		else if (match_char(f, *format) != 1)
			break;
		format++;
	}

	if (ferror(f))
		return EOF;
	return nconv;
}

// @para: ap = argument pointer

int ft_scanf(const char *format, ...)
{
	// ...
	int ret = ft_vfscanf(stdin, format, ap);
	// ...
	return ret;
}
*/
