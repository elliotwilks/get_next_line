#include "rip.h"

int	main(int argc, char **argv)
{
	int	i;
	int	br_r_count;
	int	br_l_count;

	// Arg check
	if (argc < 2)
		return (write(1, "NEED ARGUMENT\n", 15));


	/*Go allong the string, check for brackets and count*/
	i = 0;
	br_r_count = 0;
	br_l_count = 0;
	while (argv[1][i])
	{
		if (argv[1][i] == ')')
			br_r_count++;
		if (argv[1][i] == '(')
			br_l_count++;
		i++;
	}
	printf("%d\n", br_r_count);
	printf("%d\n", br_l_count);

	if (br_l_count > br_r_count)
	{
		print_brackets(br_l_count, br_r_count);
		printf("more left brackets\n");
	}
	if (br_l_count < br_r_count)
	{
		printf("more right brackets\n");
	}
	if (br_l_count == br_r_count)
	{
		printf("BRACKETS ARE BALLANCED\n");
		printf("%s\n", argv[1]);
	}
	return (0);
}

/*
Functions:
puts
write

take a string containing only parenthesis.
If the parenthesis are unbalanced

Example argument

./a.out "())"

program needs to remove the minimum number
of parentheses for the expression to be
balanced.

Remove means replace with spaces.

print all possible solutions
order of solutions is not important.

For example this should work:

INPUT
$> ./rip '(()' | cat -e

OUTPUT
()$
( )$

INPUT
$> ./rip        ((()()())())    BEFORE
				((()()())())    AFTER < nothing changed, these are ballanced. Same
								amount eiher side

$> ./rip	()())()  BEFORE
			()() ()	 AFTER
			()( )()  AFTER
			( ())()  AFTER

*/
