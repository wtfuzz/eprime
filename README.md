# Parallella Prime Counter


This is a simple naive primality test on Epiphany multicore CPU. I started this as my first Epiphany/Parallella project to familiarize myself with the platform.


Each core will perform a primality test on odd numbers from [3..(max_tests*16)]. The max_tests parameter is passed as a command line argument to the host code and can be changed in run.sh


The device code in e_prime.c will initialize each core in the workgroup with an odd number starting from 3 in the sequence [3,5,7,9..33]. Each core will then increment the number by (2*workgroup size), so the second iteration the cores will be working on [35,37,39...].


The prime test is in isprime.c and does a naive test of divisors in [3..sqrt(number)] using modulo to check for a remainder.


## Compiling

```sh
./build.sh
```

## Executing

```sh
./run.sh
```


## Sample Output


Stats are read by the host code every 100ms and printed to stderr


#### Per core stats

* Core is the core coordinates in the workgroup
* Tests is the total number of primality tests executed by this core
* Primes is the total count of primes found by this core
* Current is the current (approx) number being tested by the core
* SQ is the (approx) square root of the number being testsed by the core (debugging)


#### Aggregate stats

At the end of printing per-core stats, the total aggreate is displayed, and the number of iterations (primality tests)/second.


```sh
Core (00,00) Tests: 31524 Primes: 4992 Current: 1008771 SQ: 1004
Core (00,01) Tests: 31576 Primes: 4944 Current: 1010437 SQ: 1005
Core (00,02) Tests: 31596 Primes: 4947 Current: 1011079 SQ: 1005
Core (00,03) Tests: 31576 Primes: 4975 Current: 1010441 SQ: 1005
Core (01,00) Tests: 31610 Primes: 4942 Current: 1011531 SQ: 1005
Core (01,01) Tests: 31623 Primes: 4948 Current: 1011949 SQ: 1005
Core (01,02) Tests: 31614 Primes: 4986 Current: 1011695 SQ: 1005
Core (01,03) Tests: 31666 Primes: 4963 Current: 1013329 SQ: 1006
Core (02,00) Tests: 31607 Primes: 4966 Current: 1011443 SQ: 1005
Core (02,01) Tests: 31650 Primes: 4982 Current: 1012853 SQ: 1006
Core (02,02) Tests: 31635 Primes: 4987 Current: 1012343 SQ: 1006
Core (02,03) Tests: 31644 Primes: 5018 Current: 1012633 SQ: 1006
Core (03,00) Tests: 31677 Primes: 4983 Current: 1013691 SQ: 1006
Core (03,01) Tests: 31671 Primes: 4977 Current: 1013501 SQ: 1006
Core (03,02) Tests: 31673 Primes: 4981 Current: 1013567 SQ: 1006
Core (03,03) Tests: 31687 Primes: 5015 Current: 1014017 SQ: 1006
Total tests: 506029 Found primes: 79606
Iterations/sec: 827380.000000
```
