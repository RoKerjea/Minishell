#include <stdio.h>

int	main (void)
{
	long long int c;
	long long int	c2;
	long long int	c3;

	c = 9223372036854775807;
	c2 = c - 2;
	c3 = c + 2;
	printf("%lld\n", c2);
	if (c2 < c && c > 0)
		printf ("overflow\n");
	if (c2 > c && c < 0)
		printf ("overflow\n");	
	return(0);
}