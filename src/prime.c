#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <inttypes.h>

#include <e-hal.h>

#define MAX_TESTS = 1000000;

int main(int argc, char *argv[])
{
	unsigned row, col, coreid, i, j;
	e_platform_t platform;
	e_epiphany_t dev;

	uint64_t max_tests = 1000000;

	if(argc > 1)
	{
		max_tests = strtoull(argv[1], NULL, 10);
	}

	// initialize system, read platform params from
	// default HDF. Then, reset the platform and
	// get the actual system parameters.
	e_init(NULL);
	e_reset_system();
	e_get_platform_info(&platform);
	
	e_open(&dev, 0, 0, platform.rows, platform.cols);
	e_reset_group(&dev);

	e_load_group("e_prime.srec", &dev, 0, 0, platform.rows, platform.cols, E_FALSE);

	for(row=0;row<platform.rows;row++)
	{
		for(col=0;col<platform.cols;col++)
		{
			e_write(&dev, row, col, 0x7020, &max_tests, sizeof(uint64_t));
		}
	}
	
	e_start_group(&dev);

	uint64_t sum = 0;
	uint64_t total_primes = 0;
	uint64_t last = 0;

	while(1)
	{
		sum = 0;
		total_primes = 0;
		fprintf(stderr, "Sleeping 5 seconds\n");
		sleep(5);

		for(row=0;row<platform.rows;row++)
		{
			for(col=0;col<platform.cols;col++)
			{
				uint64_t count;
				uint64_t primes;
		
				// Get the number of primality tests from this core
				if(e_read(&dev, row, col, 0x7000, &count, sizeof(uint64_t)) != sizeof(uint64_t))
					fprintf(stderr, "Failed to read\n");

				// Get the number of primes found from this core
				if(e_read(&dev, row, col, 0x7010, &primes, sizeof(uint64_t)) != sizeof(uint64_t))
					fprintf(stderr, "Failed to read\n");

				fprintf(stderr, "Core (%02d,%02d) Tests: %" PRIu64 " Primes: %" PRIu64 "\n", row, col, count, primes);
				sum += count;
				total_primes += primes;
			}
		}
		printf("Total tests: %" PRIu64 " Found primes: %" PRIu64 "\n", sum, total_primes);

		printf("Iterations/sec: %" PRIu64 "\n", (sum - last) / 5);

		last = sum;
	}

	e_finalize();

	return 0;
}

