#include "Generate.h"

/*
 * Generate opts.num random numbers
 * numbers are between opts.min and opts.max inclusive
 * Outputted to ostream with a newline after each number
 * Random number generator is seeded with opts.seed if
 * it has been defined
 * Runtime is opts.num
 */
void generate(optionstruct opts, FILE* ostream) {
    srand(opts.seed ? opts.seed : time(NULL));
    for(int i = 0;i < opts.num;i++)
        fprintf(ostream, "%d\n", (rand()%(opts.max-opts.min+1))+opts.min);
}
