#pragma once
#define DEBUG 0

#include "Normal.h"
#include "Generate.h"
#include "mytimer.h"

int main(int argc, char **argv);


struct options {
    char g; //treated as a boolean
    char nd; //num defined
    int num;
    int min;
    int max;
    unsigned long seed;
    char* input;
    char* output;
    char* countfile;
};
typedef struct options optionstruct;
