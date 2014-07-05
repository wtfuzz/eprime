#include <math.h>

inline int is_prime(unsigned long number)
{
	unsigned long i;
	unsigned long s = sqrt(number);
	for(i=3;i<s;i+=2)
	{
		if(number % i == 0)
			return 0;
	}
	return 1;
}
