#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>
#include <unistd.h>

/* Need to look at noth match_space and match_char properly */
int match_space(FILE *f)
{
	int c;

	c = fgetc(f);
	while (c != EOF && isspace(c))
		c = fgetc(f);
	if (c != EOF)
		ungetc(c, f);
	return (0);
}

int match_char(FILE *f, char c)
{
	int got;

	got = fgetc(f);
	if (got == c)
		return (1);
	ungetc(got, f);
	return (0);
}

/* I don't need to worry about memory. Caller is responsible */
int scan_string(FILE *f, va_list ap)
{
	char	*dest;
	char	c;
	int	i;

	dest = va_arg(ap, char *);
	i = 0;
	c = fgetc(f);
	while (c != EOF && (isspace(c) == 0))
	{
		dest[i++] = c;
		c = fgetc(f);
	}
	dest[i] = '\0';
	ungetc(c, f);
    return (1);
}

/* Put the int value from the standard input into the address from ap*/
int scan_int(FILE *f, va_list ap)
{
	int	result;
	int	*dest;
	int	c;
	int	count;

	/* ap is the list and int * is the type it will return */
	dest = va_arg(ap, int *); // addres of variable we want to put data inside
	result = 0;
	count = 0;
	c = fgetc(f);
	while (c != EOF && (isdigit(c) != 0))
	{
		result = (result * 10) + (c - '0');
		c = fgetc(f);
		count++;
	}
	ungetc(c, f);
	if (count == 0)
		return (-1);
	*dest = result;

    return (1);
}

/* puts the character from the stream into the address pointer*/
int scan_char(FILE *f, va_list ap)
{
	char	*dest; // int array, ready for the address

	/* Gets the first address in the argument list */
	dest = va_arg(ap, char *);

	/* fgetc returns the character and puts it dest */
	*dest = fgetc(f);

	return (1);
}

/* match with the correct type if format is the letter d or s or c
then match with correct function */
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

int	ft_vfscanf(FILE *f, const char *format, va_list ap)
{
	int	num_conv;
	int c;

	num_conv = 0;
	c = fgetc(f);

	/* Checks file is not empty*/
	if (c == EOF)
		return (EOF);
	ungetc(c, f);

	/* Checks string by incrementing pointer */
	while (*format != '\0')
	{
		/* If a % sign is reached, increment one then check type */
		if (*format == '%')
		{
			format++;
			if (match_conv(f, &format, ap) != 1)
				break;
			else
				num_conv++;
		}
		/* If theres no % use match_space function */
		else if (isspace(*format))
		{
			/* what does match_space function do? */
			if (match_space(f) == -1)
				break;
		}
		/* what does match_char function do? */
		else if (match_char(f, *format) != 1)
			break;
		format++;
	}

	if (ferror(f))
		return (EOF);
	return (num_conv);
}

int ft_scanf(const char *format, ...)
{
	va_list	ap;
	int		ret;

	va_start(ap, format);
	ret = ft_vfscanf(stdin, format, ap);
	va_end(ap);
	return (ret);
}
/*
int	main(void)
{
	int		x;
	char	str[33] = "hello";

	x = 9;

	printf("\nOld value of x: %d\n", x);
	printf("\nOld value of str: %s\n", str);

	ft_scanf("%d %s", &x, str);

	printf("\nNew value of x: %d\n", x);
	printf("\nNew value of str: %s\n", str);
	return (0);
}
*/

/*
 * Understanding this program 
 *
 * The main things that need to be used and undestood in this program is 
 * the used of variadic functions such as va_start va_list etc and the
 * fgetc and ungetc functions that are used with the FILE * struct in 
 * order to manage the data from the STDIN. Basicly a "stream" is created
 * busing the FILE * stuct. This stream allows us to take the input from
 * stdin and send it to certain aguments. This would be pretty easy if 
 * it was just one argumet and one data type, but for this program we 
 * need to work with multiple arguments and multiple data types. So we
 * need to use this "..." in the ft_scanf() function. These three dots 
 * mean we need to use the variadic macros.
 *
 * Breaking down the functions
 * 
 * 	Scan Functions
 * 		scan_int();
 * 		scan_char();
 * 		scan_string();
 * 	Match Functions
 * 		match_conv();
 * 		match_space();
 * 		match_char();
 *
 *
 *
 */
