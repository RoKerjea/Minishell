#include <stdio.h>

int	main (void)
{
	int c;
	int	c2;

	c = 2147483647;
	c2 = c * 10;
	printf("%d\n", c2 / 10);
	if ((c2 / 10) != c)
		printf ("overflow\n");
	return(0);
}