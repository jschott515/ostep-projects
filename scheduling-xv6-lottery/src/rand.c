//
// Psuedo-RNG derived from The C Programming Language by Brian W.Kernighan and Dennis M.Ritchie
//

#include "types.h"
#include "defs.h"
#include "param.h"


static long int next = 1;

int
rand(void)
{
    next = next * 1103515243 + 12345;
    return (unsigned int)(next / 65536) % 32768;
}

void
srand(unsigned int seed)
{
    next = seed;
}
