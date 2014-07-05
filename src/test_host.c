#include <stdio.h>
#include <stdlib.h>

int is_prime(unsigned long number);

int main(void)
{
        int row,col;
        int iter = 1000000;
        int i;
	unsigned long pcount = 0;

        for(i=0;i<iter;i++)
        {
                for(row=0;row<4;row++)
                {
                        for(col=0;col<4;col++)
                        {
				int p;
                                int number;
                                number = 2 + ((2*row*4) + (2*col+1));

                                number += i * (2*16);
                                //printf("(%d,%d) %d\n", row,col, number);

				p = is_prime(number);
				if(p)
					pcount++;
                        }
                }
        }

	printf("Primes %lu\n", pcount);
}

