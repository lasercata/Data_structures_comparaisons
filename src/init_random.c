#include <stdio.h>
#include <stdlib.h>

#include "../include/init_random.h"

void init_random() {
    FILE* urand = fopen("/dev/random", "r");
    uint seed;
    fread(&seed,sizeof(int), 1, urand);
    fclose(urand);
    // fprintf(stderr, "seed : %u\n", seed);
    srand(seed);
}
