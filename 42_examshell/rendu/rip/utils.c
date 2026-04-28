#include "rip.h"

void	print_brackets(int left, int right)
{
	int	variations;

	variations = left - right;

	printf("POSSIBLE VARIATIONS: %d\n", variations);
}
