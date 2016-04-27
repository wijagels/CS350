#include "Market.h"

#include <stdlib.h>
#include <stdio.h>


int main(int argc, char* argv[]) {
    if(argc != 3) {
        fprintf(stderr, "Invalid number of arguments\n");
        exit(1);
    }
    _stocks = atoi(argv[1]);
    _delta = atoi(argv[2]);
    if(_stocks < 1 || _delta < 1 || _delta > 20) {
        fprintf(stderr, "Invalid argument\n");
        exit(1);
    }
    return market();
}
